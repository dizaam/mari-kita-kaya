#ifndef _PLAYER_H
#define _PLAYER_H

#include "system.h"



typedef struct{
    bool isbankrupt;
    bool isbot;
    bool isjailed;
    bool jailcard;

    int position; 
    int touristcount;
    int linecount[3];
    int money;

    char pawn;
}PPLAYER;



extern PPLAYER* player;
extern int totalplayer;
extern int* turn;
extern int currentturn;
extern int currentplayer;
extern int playerchoose;
extern int remainingplayer;
extern int playerwinner;

void InitPlayer();
char inputPlayerType();
void PlayerBankrupt();

#endif