#ifndef _MAP_H
#define _MAP_H

#include "allheader.h"

typedef struct MAPPOSITION{
    int row;
    int col;
} MAPPOSITION;


extern WINDOW* wmap;
extern char map[40][100];
extern int board[32];

void DrawMap();
void DrawProperty();
MAPPOSITION getMapPosition(int position);
void DrawPawn();
void RemovePawn();

#endif