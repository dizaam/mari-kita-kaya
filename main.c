#include "allheader.h"


int main(){
    srand(time(NULL));
    initscr();
    InitColor();

    MainMenu();
    clear();

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
            addstr("not yet implemented :(\n");
            break;

        case 3:
            // exit
            addstr("bye bye\n");
            break;

        default:
            break;
    }
    
    free(turn);
    getch();
    endwin();
    return 0;
}