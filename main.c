#include "system.h"

int main(){
    srand(time(NULL));
    initscr();

    MainMenu();
    clear();

    switch(menuchoose){
        case 0:
            // new game
            SetupNewGame();
            break;

        case 1:
            // load game
            addstr("not yet implemented :(\n");
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
    
    clear();
    refresh();
    InitWindow();

    while(currentturn < 4){
        // mereset dadu untuk giliran player sekarang
        resetDadu(&dd);
        currentplayer = turn[currentturn];
   
        do{
            //clear();
            refresh();

            DrawMap();

            DrawWidget();

            UpdatePlayerInfo();

            DrawActionRollDice();

            //DrawAction();

            shakeDadu(&dd);

            DrawDiceSymbol();

            UpdatePosition();
              
            // check jika player sudah 3x double
            if(dd.countdouble>3){
                printw("Double 3x Curang!\n");
                printw("Player Masuk Penjara\n");
                player[currentplayer].position=8;
                player[currentplayer].isjailed=true;
                break;
            }
            
            UpdateBoardInfo();
                   
        }while(dd.isdouble);

        DrawActionEndTurn();

        // penggantian giliran
        do{
            currentturn++;
            if(currentturn==totalplayer){
                currentturn=0;
            } 
        }while(player[turn[currentturn]].isbankrupt);    
    }
    
    free(turn);
    getch();
    endwin();
    return 0;
}