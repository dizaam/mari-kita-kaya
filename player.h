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
}PPLAYER;


extern PPLAYER player[4];
extern int totalplayer;
extern int* turn;
extern int currentturn;
extern int currentplayer;
extern int playerchoose;

void InitPlayer(PPLAYER* p, int size);
char inputPlayerType();

#endif