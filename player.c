#include <stdio.h>
#include "player.h"
#include <ctype.h>





void InitPlayer(player* p, int arrsize){
    for(int i=0; i<arrsize; i++){
        printw("\nPLAYER %d: \n", i+1);
        if (inputPlayerType()=='y'){
            (p+i)->isbot = true;
        }else{
            (p+i)->isbot = false;
        }

        (p+i)->isbangkrut = false;
        (p+i)->isnapi = false;
        (p+i)->posisi = 0;
        (p+i)->totalrumah = 0;
        (p+i)->uang = 2000;
    
    }
}

char inputPlayerType(){
    char buffer;
    
    printw("Apakah Seorang Robot ? \n");
    printw("(y/n): ");

    scanw("%c", &buffer);

    return tolower(buffer);
}
