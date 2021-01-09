#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "dadu.h"
#include "player.h"
#include "map.h"
#include "properti.h"

#define u unsigned
//#define RAND_MAX 6

void delay(int sec){
    int ms = CLOCKS_PER_SEC*sec;

    clock_t start = clock();

    while(clock() < start + ms);

}

int main(){
    int totalplayer;
    dadu dadu;

    u int pos=0;
    int i = 1;
    int p = 0;

    printMap();

    printf("properti: %s\n", property[3].name);

    /*
    printf("berapa player? ");
    scanf("%d", &totalplayer);
    player player[totalplayer];
    initPlayer(player, totalplayer);

    setNamaPlayer(player, totalplayer);
    int temparr[totalplayer];
    int giliran[totalplayer];
    for(int counter=0; counter < totalplayer; counter++){
        resetDadu(&dadu);
        kocokDadu(&dadu);
        temparr[counter] = dadu.totaldd;
    }
    */


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
    getchar();
    return 0;
}