#include "allheader.h"

PPLAYER* player = NULL;
int totalplayer = 0;
int* turn = NULL;
int currentturn = 0;
int currentplayer = 0;
int playerchoose = 0;
int remainingplayer = 0;
int playerwinner = 0;

void InitPlayer(){
    player = (PPLAYER*) realloc(player, sizeof(PPLAYER)*totalplayer);
    remainingplayer = totalplayer;

    for(int i=0; i<totalplayer; i++){
        printw("\nPLAYER %d: \n", i+1);

        if (inputPlayerType()=='y'){
            player[i].isbot = true;
            bot.istherebot = true;
        }else{
            player[i].isbot = false;
        }

        player[i].isbankrupt = false;
        player[i].isjailed = false;
        player[i].jailcard = false;
        player[i].position = 0;
        player[i].touristcount = 0;
        memset(player[i].linecount, 0, 3*sizeof(int));
        player[i].money = 2000;


        switch (i){
            case 0: 
                player[i].pawn= '@';
                map[34][83] = '@';
                break;
            case 1:
                player[i].pawn = '!';
                map[34][84] = '!';

                break;
            case 2:
                player[i].pawn = '*';
                map[34][85] = '*';

                break;
            case 3:
                player[i].pawn = '%';
                map[34][86] = '%';

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

void PlayerBankrupt(){
    player[currentplayer].isbankrupt=true;
    --remainingplayer;
    SetDefaultProperty();
    RemovePawn();
}


