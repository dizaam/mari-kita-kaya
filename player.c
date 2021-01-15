#include <stdio.h>
#include "player.h"
#include <ctype.h>





void InitPlayer(player* p, int playersize){
    for(int i=0; i<playersize; i++){
        printw("\nPLAYER %d: \n", i+1);

        if (inputPlayerType()=='y'){
            (p+i)->isbot = true;
        }else{
            (p+i)->isbot = false;
        }

        (p+i)->isbankrupt = false;
        (p+i)->isjailed = false;
        (p+i)->position = 0;
        (p+i)->tourist = 0;
        (p+i)->money = 2000;
    
    }
}

char inputPlayerType(){
    char buffer;
    
    printw("Apakah Seorang Robot ? \n");
    printw("(y/n): ");

    scanw("%c", &buffer);

    return tolower(buffer);
}
