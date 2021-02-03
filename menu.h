#ifndef _MENU_H
#define _MENU_H

#include "system.h"

extern int menuchoose;
extern char logo[8][69];
extern char menu[4][11];

void PrintCenter(WINDOW* win, int row, char* text);
void DrawLogo();
void DrawMenu(int* highlight);
void MainMenu();

#endif