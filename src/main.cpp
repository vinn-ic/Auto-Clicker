#include <windows.h>
#include <iostream>
#include <random>

using namespace std;

void click(int amount){
    char tecla;
    bool loop = true;
    cout << "to stop: 'Ctrl' + C\n";

    while(loop){
        

        for(int i=0;i<amount;i++){
            HWND hWnd = FindWindow(NULL, NULL);

            SetForegroundWindow(hWnd);
            random_device rd;
            random_device rd2;

            mt19937 gen(rd());
            mt19937 gen2(rd2());

            uniform_int_distribution<> dist(800,1800);
            uniform_int_distribution<> dist2(250,600);

            int numeber_ale = dist(gen);
            int numeber_ale2 = dist2(gen2);
            system("cls");
            cout << "to stop: 'Ctrl' + C\n";
            cout << "reaction time for each randomly generated click: " << numeber_ale2 << "\n";
            cout << "time per click randomly generated: " << numeber_ale << "\n";
            

            mouse_event(MOUSEEVENTF_LEFTDOWN, 0,0,0,0);
            Sleep(numeber_ale2);
            mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
            Sleep(numeber_ale);
        }
    }
}

void jump(){

    while(true){
        random_device rd;
        random_device rd2;
        mt19937 gen(rd());
        mt19937 gen2(rd2());

        uniform_int_distribution<> dist(800,1800);
        uniform_int_distribution<> dist2(5000,9000);

        int numeber_ale = dist(gen);
        int numeber_ale2 = dist2(gen2);

        system("cls");
        cout << "to stop: 'Ctrl' + C\n"; 
        cout << "randomly generated jump reaction time: " << numeber_ale << "\n";
        cout << "time each jump randomly generated: " << numeber_ale2 << "\n";

        keybd_event(VK_SPACE,0,0,0);
        Sleep(numeber_ale);
        keybd_event(VK_SPACE,0,KEYEVENTF_KEYUP,0);
        Sleep(5000);
    }
}
int main(){


    int click_numb;
    int quest;

    system("cls");
    cout <<       "  AAAAAA    U     U    TTTTTTT   OOOOOOO           CCCCCCCC   L         III    CCCCCCCC  K    K  EEEEEE   RRRRR\n"
                 " A      A   U     U       T      O     O          C           L          I    C          K   K   E        R   R\n"
                 " AAAAAAAA   U     U       T      O     O  ====== C            L          I   C           KKK     EEEEEE   RRRRR\n"
                 " A      A   U     U       T      O     O          C           L          I    C          K   K   E        R  R\n"
                 " A      A    UUUUU        T      OOOOOOO           CCCCCCCC   LLLLL     III     CCCCCCCC K    K  EEEEEE   R    R\n\n\n\n";

    cout << "auto-clicker=1\nauto-jump=2\n";
    cin >> quest;


    if(quest == 1){
        cout << "number of clicks per second(CPS):\n";
        cin >>  click_numb;

        click(click_numb);
    }
    if(quest == 2){
        jump();
    }
    return 0;
}