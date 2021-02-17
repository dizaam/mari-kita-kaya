#include "allheader.h"


int main(){
    srand(time(NULL));
    initscr();
    InitColor();

    

    do{
        clear();
        MainMenu();
        switch(menuchoose){
            case 0:
                // new game
                NewGame();
                PlayGame();
                break;

            case 1:
                // load game
                LoadGame();
                PlayGame();
                break;

            case 2:
                // highscores
                ShowHighScore();
                break;

            case 3:
                // help
                Help();

                break;
            case 4:
                // credits
                Credits();

                break;
            case 5:
                // exit
                clear();
                addstr("bye bye\n");

                break;
            default:
                break;

        }
    }while(menuchoose!=5);
    
    free(turn);
    getch();
    endwin();
    return 0;
}