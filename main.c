#include "system.h"

#define u unsigned
//#define RAND_MAX 6

void delay(int sec){
    int ms = CLOCKS_PER_SEC*sec;

    clock_t start = clock();

    while(clock() < start + ms);

}

int main(){
    srand(time(NULL));
    initscr();
    refresh();
    char trash;
    int totalplayer;
    //dadu dadu;
    //int petak;
    
    //int i = 1;
    //int p = 0;

    printw("SETUP NEW GAME\n");
    printw("berapa player? (2-4): ");
    scanw("%d", &totalplayer);
    player player[totalplayer];
    InitPlayer(player, totalplayer);

    
    clear();
    printw("PENENTUAN GILIRAN\n");
    int temp[totalplayer][2];
    int turn[totalplayer];
    int currentturn;

    for(int i=0; i<totalplayer; i++){
        printw("\nPLAYER %d SILAHKAN MENGOCOK DADU\n", i+1);
        printw("ketik apa saja untuk mengocok...");
        getch();
        
        temp[i][0] = rand() % 12 +1;
        temp[i][1] = i;
        printw("\nDadu yg didapat: %d\n", temp[i][0] = rand() % 12 +1);
    }

    printw("\n");

    for(int i=0; i<totalplayer; i++){
        int maxVal=i;

        for(int j=totalplayer-1; j>i; j--){
            if(temp[maxVal][0] < temp[j][0]){
                maxVal = j;
            }
        }

        int tempValue = temp[i][0];
        int tempIndex = temp[i][1];

        temp[i][0] = temp[maxVal][0];
        temp[i][1] = temp[maxVal][1];
        turn[i] = temp[maxVal][1];

        temp[maxVal][0] = tempValue;
        temp[maxVal][1] = tempIndex;    
    }

    for(int i=0; i<totalplayer; i++){
        printw("Giliran ke-%d: Player %d\n", i+1, turn[i]+1);
    }
    printw("\nKetik apa saja untuk memulai Permainan");
    getch();

    clear();
    refresh();
    printMap();

    
    





    



    
    


    /*
    while(1){
        resetDadu(&dadu);
        printf("\nturn ke: %d\n", i);
        printf("giliran: %s\n", player[p].nama);

        do{
            kocokDadu(&dadu);

            player[p].posisi += dadu.totaldd;

            if(player[p].posisi>39){
                player[p].posisi-=40;
            }

            printf("dadu1: %d\n", dadu.dadu1);
            printf("dadu2: %d\n", dadu.dadu2);
            printf("posisi sekarang: %d\n", player[p].posisi);
            delay(2);

            if(dadu.countdouble==3) break;

        }while(dadu.isdouble);

        
        i++;
        if(p){
            p=0;
        }else{
            p=1;
        }
    }

    */
    getch();
    endwin();
    return 0;
}