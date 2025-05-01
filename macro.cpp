#include "macro.h"

#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <array>
#include <vector>

using namespace std;



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

void CreatMacro(){
    system("cls");
    char quest;
    POINT cursorPos;
    int x;
    int y;

    cout << "coloque o cursor na posicao!\naperte 'ENTER' para adicionar as cordenadas ao macro || 'esc' para sair\n";
    while(true){
        if(_kbhit()){
            quest = _getch();

            if(quest == 13){

                if(GetCursorPos(&cursorPos)){
                    x = cursorPos.x;
                    y = cursorPos.y;
                }
            }

            cout << "Pos do cursor reolocado para o 'Ctrl + c': X = " << x << ", Y = " << y << "\n";
            setclipboard(to_string(x) + " " + to_string(y));
            
            if(quest == 27){
                macro();
            }
        }
    }

}

void macro(){
    vector<string> macros = {"ola"};
    system("cls");
    int quest;
    cout << 
        " M     M   AAAAAA     CCCCCCCC   RRRRR   OOOOOOO \n"
        " MM   MM  A      A   C           R   R   O     O \n"
        " M M M M  AAAAAAAA  C            RRRRR   O     O   \n"
        " M  M  M  A      A   C           R  R    O     O \n"
        " M     M  A      A    CCCCCCCC   R    R  OOOOOOO \n\n\n";


        cout << "\ncreat MACRO = 1\n";
        if(!macros.empty()){
            cout << "executar o macro = 2\n";

        }
        cin >> quest;

        if(quest == 1){
            CreatMacro();
        }
        
}

int main(){
    macro();

    return 0;
}