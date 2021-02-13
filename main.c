#include "system.h"

void Action(){
    switch(board[player[currentplayer].position]){
        case 0:
            // penjara
            player[currentplayer].position=8;
            player[currentplayer].isjailed=true;
    
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
            ShowTaxInfo();
            
            DrawActionPayTax();
            if(player[currentplayer].money < 100){
                // uang kurang
                ShowFailedTaxInfo();

                playerchoose = 0;
                DrawActionNeedMoney();
                if(playerchoose == 0){
                    // jual properti // not yet implemented
                    AutoSellProperty(100);
                    if(player[currentplayer].money < 100){
                        // uang jual hasil properti TIDAK mencukupi
                        ShowFailedAutoSell(100);
                        player[currentplayer].isbankrupt=true;
                        SetDefaultAllProperty();
                    }else{
                        // uang hasil jual properti mencukupi
                        ShowSuccesAutoSell(100);
                        player[currentplayer].money -= 100;
                    }
                }else if(playerchoose == 1){
                    // bangkrut
                    player[currentplayer].isbankrupt=true;
                    SetDefaultAllProperty();
                }

            }else{
                // sukses bayar pajak
                player[currentplayer].money -= 100;
                ShowSuccesTaxInfo();

            }

            break;
        case 5:
            // kesempatan
            CardAction();

            break;
        case 6:
            // properti
            // belum ada owner
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
                
            // milik sendiri
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

            // milik pemain lain
            }else{
                int rentprice = property[player[currentplayer].position].price[property[player[currentplayer].position].level];
                ShowRentInfo();
                DrawActionPayRent();
                if(player[currentplayer].money < rentprice){
                    // player kekurangan uang
                    ShowPayRentFailed();
                    playerchoose = 0;
                    DrawActionNeedMoney();
                    if(playerchoose == 0){
                        // jual properti
                        AutoSellProperty(rentprice);
                        if(player[currentplayer].money < rentprice){
                            // uang jual hasil properti TIDAK mencukupi
                            ShowFailedAutoSell(rentprice);
                            player[currentplayer].isbankrupt=true;
                            SetDefaultAllProperty();
                        }else{
                            // uang hasil jual properti mencukupi
                            ShowSuccesAutoSell(rentprice);
                            player[currentplayer].money -= rentprice;
                        }
                    }else if(playerchoose == 1){
                        // bangkrut
                        player[currentplayer].isbankrupt=true;
                        SetDefaultAllProperty();
                    }
                    
                }else{
                    // pemain tidak kekurangan uang
                    player[currentplayer].money -= rentprice;
                    player[property[player[currentplayer].position].owner].money += rentprice;

                    ShowPayRentSucces();
                    
                    
                }
            }

            break;
        case 7:
            // tempat wisata
            // belum ada owner
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
                        player[currentplayer].tourist++;
                        // jika memiliki semua tempat wisata menang(not yet impelented)
                    }
                    
                }
                
            // milik sendiri
            }else if(property[player[currentplayer].position].owner == currentplayer){
                ShowOwnedByself();

            // milik pemain lain
            }else{
                int rentprice = property[player[currentplayer].position].price[player[currentplayer].tourist-1];
                ShowRentInfo();
                DrawActionPayRent();
                if(player[currentplayer].money < rentprice){
                    ShowPayRentFailed();
                    playerchoose = 0;

                    DrawActionNeedMoney();
                    if(playerchoose == 0){
                        // jual properti
                        AutoSellProperty(rentprice);
                        if(player[currentplayer].money < rentprice){
                            // uang jual hasil properti TIDAK mencukupi
                            ShowFailedAutoSell(rentprice);
                            player[currentplayer].isbankrupt=true;
                            SetDefaultAllProperty();
                        }else{
                            // uang hasil jual properti mencukupi
                            ShowSuccesAutoSell(rentprice);
                            player[currentplayer].money -= rentprice;
                        }
                    }else if(playerchoose == 1){
                        // bangkrut
                        player[currentplayer].isbankrupt=true;
                        SetDefaultAllProperty();
                    }
                    
                }else{
                    player[currentplayer].money -= rentprice;
                    ShowPayRentSucces();
                    
                }
            }
            break;
        default:
            break;
    }
}

void PlayGame(){
    clear();
    refresh();
    InitWindow();

    while(1){
        // mereset dadu untuk giliran player sekarang
        resetDice();
        currentplayer = turn[currentturn];

        // jika pemain dipenjara
        if(player[currentplayer].isjailed){
            refresh();

            DrawMap();
            
            DrawWidget();

            UpdatePlayerInfo();

            playerchoose = 0;
            DrawActionJailed();

            // player memilih mengocok dadu
            if(playerchoose == 0){
                DrawActionRollDice();

                shakeDice();

                DrawDiceSymbol();

                if(dice.isdouble){
                    player[currentplayer].isjailed=false;
                    UpdatePosition();
                    UpdateBoardInfo();
                    Action();
                }
            
            // player memilih menggunakan kartu bebas penjara
            }else if(playerchoose == 1){
                ShowJailCardMessage();
                if(player[currentplayer].jailcard){
                    // mempunyai kartu bebas penjara
                    player[currentplayer].jailcard = false;
                    player[currentplayer].isjailed = false;

                    DrawActionRollDice();
                    
                    shakeDice();

                    DrawDiceSymbol();

                    UpdatePosition();
                    
                    UpdateBoardInfo();
                    
                    Action();

                }

            // player memilih menyogok petugas
            }else if(playerchoose == 2){
                ShowPayJailMessage();
                if(player[currentplayer].money>=100){
                    // uang cukup
                    player[currentplayer].isjailed = false;
                    player[currentplayer].money -= 100;

                    DrawActionRollDice();

                    shakeDice();

                    DrawDiceSymbol();

                    UpdatePosition();

                    UpdateBoardInfo();

                    Action();

                }
            }

        }else{
            do{
                refresh();

                DrawMap();

                DrawWidget();

                UpdatePlayerInfo();

                DrawActionRollDice();

                shakeDice();

                DrawDiceSymbol();

                UpdatePosition();

                // check jika player sudah 3x double
                if(dice.countdouble>3){
                    printw("Double 3x Curang!\n");
                    printw("Player Masuk Penjara\n");
                    player[currentplayer].position=8;
                    player[currentplayer].isjailed=true;
                    break;
                }

                UpdateBoardInfo();
                Action();


                if(dice.isdouble){
                    ShowInfoDouble();
                    wgetch(wpinfo);
                }
            }while((dice.isdouble) && (!player[currentplayer].isjailed) && (!player[currentplayer].isbankrupt));
        }
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