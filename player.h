#ifndef _PLAYER_H
#define _PLAYER_H

#include "system.h"



typedef struct{
    bool isbankrupt;
    bool isbot;
    bool isjailed;
    bool jailcard;

    int propertybought[32];
    int position; 
    int tourist;
    int money; 

    char pawn;
}PPLAYER;



extern PPLAYER* player;
extern int totalplayer;
extern int* turn;
extern int currentturn;
extern int currentplayer;
extern int playerchoose;

void InitPlayer();
char inputPlayerType();

#endif