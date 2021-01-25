#ifndef _MAP_H
#define _MAP_H

#include "system.h"


extern WINDOW* wmap;
extern char map[40][100];
extern int board[32];

void DrawMap();
void printMap();

#endif