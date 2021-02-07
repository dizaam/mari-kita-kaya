#include "system.h"

PPLAYER player[4];
int totalplayer = 0;
int* turn = NULL;
int currentturn = 0;
int currentplayer = 0;
int playerchoose =0;


void InitPlayer(PPLAYER* p, int size){
    for(int i=0; i<size; i++){
        printw("\nPLAYER %d: \n", i+1);

        if (inputPlayerType()=='y'){
            (p+i)->isbot = true;
        }else{
            (p+i)->isbot = false;
        }

        memset((p+i)->propertybought, -1, 32*sizeof(int));
        (p+i)->isbankrupt = false;
        (p+i)->isjailed = false;
        (p+i)->jailcard = false;
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
