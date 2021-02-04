#include "system.h"

void Action(){
    switch(board[player[currentplayer].position]){
        case 0:
            // penjara
            break;
        case 1:
            // start

            break;
        case 2:
            // bebas parkir

            break;
        case 3:
            // hanya lewat

            break;
        case 4:
            // kantor pajak

            break;
        case 5:
            // kesempatan
            CardAction();

            break;
        case 6:
            // properti
            if(property[player[currentplayer].position].owner == -1){
                playerchoose = 0;

                DrawActionUnownedProperty();
                if(playerchoose == 0){
                    if(property[player[currentplayer].position].price[0] > player[currentplayer].money){
                        ShowBuyFailed();
                    }else{
                        ShowBuySucces();
                        player[currentplayer].money -= property[player[currentplayer].position].price[0];
                        property[player[currentplayer].position].owner = currentplayer;
                    }
                    
                }
                

            }else if(property[player[currentplayer].position].owner == currentplayer){
                ShowOwnedByself();
                playerchoose = 0;

                while(playerchoose != 1){
                    DrawActionUpgradeProperty();
                    if(playerchoose == 0){
                        // uang kurang
                        if(property[player[currentplayer].position].upgradeprice > player[currentplayer].money){
                            ShowUpgradeFailed(0);
                        }
                        // level max
                        else if(property[player[currentplayer].position].level==4){
                            ShowUpgradeFailed(1);
                        }
                        // sukses
                        else{
                            property[player[currentplayer].position].level++;
                            ShowUpgradeSucces();
                            player[currentplayer].money -= property[player[currentplayer].position].upgradeprice;
                        }

                    }
                }   

            }else{
                ShowRentInfo();
                DrawActionPayRent();
                if(player[currentplayer].money < property[player[currentplayer].position].price[property[player[currentplayer].position].level]){
                    ShowPayRentFailed();
                }else{
                    ShowPayRentSucces();
                    player[currentplayer].money -= property[player[currentplayer].position].price[property[player[currentplayer].position].level];
                }
            }

            break;
        case 7:
            // kantor pajak

            break;
        default:
            break;
    }
}

void PlayGame(){
    clear();
    refresh();
    InitWindow();

    while(currentturn < 4){
        // mereset dadu untuk giliran player sekarang
        resetDadu(&dd);
        currentplayer = turn[currentturn];

        

        if(player[currentplayer].isjailed){

        }

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
            Action();
                   

            if(dd.isdouble){
                ShowInfoDouble();
                wgetch(wpinfo);
            }
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

}

int main(){
    srand(time(NULL));
    initscr();

    MainMenu();
    clear();

    switch(menuchoose){
        case 0:
            // new game
            SetupNewGame();
            PlayGame();
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
    
    free(turn);
    getch();
    endwin();
    return 0;
}