#ifndef _PLAYER_H
#define _PLAYER_H

#include "system.h"

typedef struct player{
    bool isbankrupt;
    bool isbot;
    bool isjailed;

    int position; 
    int tourist;
    int money; 
}player;

void InitPlayer(player* p, int playersize);
char inputPlayerType();

#endif