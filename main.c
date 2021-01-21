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

    while(currentturn < 4){
        

        // mereset dadu untuk giliran player sekarang
        resetDadu(&dd);
        currentplayer = turn[currentturn];

        
        do{
            clear();
            refresh();
            //printMap();
            
            printw("Giliran Player %d\n", currentplayer+1);
            printw("Posisi Player: %d\n", player[currentplayer].position);
            printw("Ketik Apa Saja Untuk Mengocok Dadu...");
            getch();

           shakeDadu(&dd);
           printw("\nDadu 1: %d\n", dd.dadu1);
           printw("Dadu 2: %d\n", dd.dadu2);
           printw("Total : %d\n", dd.totaldd);
           getch();

           // check jika player sudah 3x double
           if(dd.countdouble>3){
               printw("Double 3x Curang!\n");
               printw("Player Masuk Penjara\n");
                player[currentplayer].position=8;
                player[currentplayer].isjailed=true;
                break;
            }

            // memindahkan posisi player    
            player[currentplayer].position += dd.totaldd;
            // check jika player melewati start
            if(player[currentplayer].position > 31){
                player[currentplayer].position = player[currentplayer].position-32;
                player[currentplayer].money += 200;
                printw("\nPosisi Player: %d\n", player[currentplayer].position);
            }else{
                printw("\nPosisi Player: %d\n", player[currentplayer].position);
            }
            getch();
            

            
            
            switch(board[player[currentplayer].position]){
                case 0:
                    // masuk penjara
                    printw("\nKamu Berada Di Persidangan\n");
                    printf("Kamu Terbukti Melanggar Hukum! Pergi ke Penjara\n");
                    getch();

                    player[currentplayer].position=8;
                    player[currentplayer].isjailed=true;
                    break;

                case 1:
                    // player berada pada petak start
                    printw("\nKamu Berada di Petak START\n");
                    getch();
                    
                    break;
                
                case 2:
                    // player berada pada petak bebas parkir
                    printw("\nBebas Parkir, Kamu Aman Disini\n");
                    getch();

                    break;
                
                case 3:
                    // penjara hanya lewat
                    printw("\nLapas Tempatnya Orang2 Melanggar Hukum\n");
                    getch();

                    break;
                
                case 4:
                    // petak pajak, player membayar pajak
                    printw("\nBayar Pajak Dong!\n");
                    getch();

                    break;

                case 5:
                    // player mendapat kartu kesempatan
                    printw("\nKamu Berada di Petak Property!\n");
                    getch();

                    break;
                
                case 6:
                    // player berada pada petak properti
                    printw("\nKamu Berada di Petak Property!\n");
                    getch();

                    break;
            }
                   
        }while(dd.isdouble);

        
        
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