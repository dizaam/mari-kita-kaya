#ifndef _PLAYER_H
#define _PLAYER_H

#include "system.h"

typedef struct player{
    bool isbangkrut;
    bool isbot;
    bool isnapi;

    int posisi; 
    int totalrumah;
    int uang; 
}player;

void InitPlayer(player* p, int arrsize);
char inputPlayerType();

#endif