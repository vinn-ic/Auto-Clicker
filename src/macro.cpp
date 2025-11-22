#include "macro.h"

#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <array>
#include <vector>
#include <random>
#include <sstream>

using namespace std;

vector<string> split(const string& str, char delimiter){
    vector<string> arraySplit;

    stringstream ss(str);
    string item;

    while(getline(ss, item, delimiter)){
        arraySplit.push_back(item);
    }
    return arraySplit;
}


void setclipboard(const string& texto){
    if(OpenClipboard(nullptr)){
        EmptyClipboard();

        HGLOBAL hmen = GlobalAlloc(GMEM_MOVEABLE, texto.size()+1);
        if(hmen){

            memcpy(GlobalLock(hmen), texto.c_str(), texto.size()+1);
            GlobalUnlock(hmen);

            SetClipboardData(CF_TEXT, hmen);
        }
        CloseClipboard();
    };
}

void insertText(string text){
    for(char t : text){
       SHORT vk = VkKeyScan(t);
        
       BYTE vkcode = vk & 0xff;
       
        INPUT down = {0};
        down.type = INPUT_KEYBOARD;
        down.ki.wVk = vkcode;

        //soltar tecla;
        INPUT up = down;
        up.ki.dwFlags = KEYEVENTF_KEYUP;

        INPUT inputs[2] = { down, up };
        SendInput(2, inputs, sizeof(INPUT));

        Sleep(30); // pequena pausa entre caracteres
       
    }

}

void executeMacro(vector<string> arrayMacros, int lengthArray){
    

    string comandoAcao;
    
    string text; 
    int x;
    int y;

    string stringX;
    string stringY;
    bool loopMacro = true;
    while(loopMacro){

        for(int i = 0;i<lengthArray;i++){
            random_device rd;
            random_device rd2;
            
            mt19937 gen(rd());
            mt19937 gen2(rd2());
            
            uniform_int_distribution<> dist(1000,2000);
            uniform_int_distribution<> dist2(300,600);
            
            int randomDiferencaAcao = dist(gen);
            int randomDiferencaClick = dist2(gen2);
            
            
            vector<string> arraySplit = split(arrayMacros[i], ' ');
            
            if(arraySplit[0] == "ENTER"){//primeiro comando é um click
                stringX = arraySplit[1];
                stringY = arraySplit[3];
                
                x = stoi(stringX);
                y = stoi(stringY);
                
                SetCursorPos(x,y);
                
                Sleep(randomDiferencaClick);
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0,0,0,0);//CLICAR
                Sleep(randomDiferencaClick);
                mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);//SOLTAR O CLICK
                
            }
            if(arraySplit[0] == "TAB"){
                string text = arraySplit[2];
                Sleep(randomDiferencaClick);
                insertText(text);
            }
            Sleep(randomDiferencaAcao);
        }
    }
}



void CreatMacro(vector<string>& arrayMacro){
    system("cls");
    char key;
    POINT cursorPos;
    int x;
    int y;
    cout << "\ncriar um macro, todos os comandos realizados serão salvos no macro\n";
    cout << "coloque o cursor na posicao!\naperte 'ENTER' para adicionar as cordenadas do cursor ao macro \n'TAB' para apertar uma tecla\n'ESC' para sair e salvar as ações ao macro";
    bool loopCreat = true;
    while(loopCreat){
        if(_kbhit()){
            key = _getch();

            if(key == 13){

                if(GetCursorPos(&cursorPos)){
                    x = cursorPos.x;
                    y = cursorPos.y;
                }
                arrayMacro.push_back("ENTER "+to_string(x) +" : "+ to_string(y));
                cout << "Pos do cursor reolocado para o macro: X = " << x << ", Y = " << y << "\n";
            }

            
            
            //setclipboard(to_string(x) + " " + to_string(y));
            if(key == 9){
                //tab, aperta tecla!
                string text;

                cout << "text>>";
                cin >> text;
                arrayMacro.push_back("TAB : "+ text);

            }

            if(key == 27){
                loopCreat = false;
            }
        }
    }

}

void macro(){
    vector<string> macros = {};
    bool loop = true;
    system("cls");
    while(loop){
        int choice;

        cout << 
        " M     M   AAAAAA     CCCCCCCC   RRRRR   OOOOOOO \n"
        " MM   MM  A      A   C           R   R   O     O \n"
        " M M M M  AAAAAAAA  C            RRRRR   O     O   \n"
        " M  M  M  A      A   C           R  R    O     O \n"
        " M     M  A      A    CCCCCCCC   R    R  OOOOOOO \n\n\n";
        
        


        cout << "\ncreat MACRO = 1\n";
        if(!macros.empty()){
            for(string i : macros){
                cout << i << " ";
            }
            cout << "\nexecutar o macro = 2\n";

        }
        
        cin >> choice;
        
        if(choice == 1){
            CreatMacro(macros);
        }if(choice == 2){
            executeMacro(macros, macros.size());
        }
        
    }
}

