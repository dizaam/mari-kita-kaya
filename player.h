#ifndef _PLAYER_H
#define _PLAYER_H

#include "system.h"



typedef struct{
    bool isbankrupt;
    bool isbot;
    bool isjailed;

    int position; 
    int tourist;
    int money; 
}pplayer;


extern pplayer player[4];
extern int totalplayer;
extern int* turn;
extern int currentturn;
extern int currentplayer;
extern int playerchoose;

void InitPlayer(pplayer* p, int size);
char inputPlayerType();

#endif