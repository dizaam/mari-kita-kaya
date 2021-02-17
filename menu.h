#ifndef _MENU_H
#define _MENU_H

#include "allheader.h"

extern int menuchoose;
extern char logo[8][69];
extern char menu[6][11];

void PrintCenter(WINDOW* win, int row, char* text);
void DrawLogo();
void DrawMenu(int* highlight);
void MainMenu();
void Credits();
void Help();
void DrawLogoDefaultWin();
void DrawLogoLineWin();
void DrawLogoTourismWin();
void ShowHighScore();

#endif