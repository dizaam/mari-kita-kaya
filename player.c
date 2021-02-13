#include "system.h"

PPLAYER* player = NULL;
int totalplayer = 0;
int* turn = NULL;
int currentturn = 0;
int currentplayer = 0;
int playerchoose =0;


void InitPlayer(){
    player = (PPLAYER*) realloc(player, sizeof(PPLAYER)*totalplayer);

    for(int i=0; i<totalplayer; i++){
        printw("\nPLAYER %d: \n", i+1);

        if (inputPlayerType()=='y'){
            player[i].isbot = true;
        }else{
            player[i].isbot = false;
        }
        memset(player[i].propertybought, -1, 32*sizeof(int));
        player[i].isbankrupt = false;
        player[i].isjailed = false;
        player[i].jailcard = false;
        player[i].position = 0;
        player[i].tourist = 0;
        player[i].money = 2000;

        switch (i){
            case 0: 
                player[i].pawn= '@';

                break;
            case 1:
                player[i].pawn = '!';

                break;
            case 2:
                player[i].pawn = '*';

                break;
            case 3:
                player[i].pawn = '%';

                break;
            default:
                break;
        } 
    }

}

char inputPlayerType(){
    char buffer;
    
    printw("Apakah Seorang Robot ? \n");
    printw("(y/n): ");

    scanw("%c", &buffer);

    return tolower(buffer);
}


