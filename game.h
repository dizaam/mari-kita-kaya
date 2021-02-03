#ifndef _GAME_H
#define _GAME_H

#include "system.h"

extern WINDOW*  wactionborder, *wpinfoborder, *wbinfoborder;
extern WINDOW*  waction, *wpinfo, *wbinfo;
extern char actionlist[2][30];

void InitWindow();
int* shakeTurn(int temp[totalplayer][2]);
void TurnSetup();
void SetupNewGame();

void DrawActionBorder();
void DrawPlayerInfoBorder();
void DrawBoardInfoBorder();
void DrawWidget();



void DrawActionList(int* highlight);
void DrawActionUnownedProperty();
void DrawActionRollDice();
void DrawActionEndTurn();

void UpdatePlayerInfo();

void DrawDiceResult();
void DrawDiceSymbol();

void UpdatePosition();
void UpdateBoardInfo();
void ShowPropertyInfo();
void ShowTourismInfo();


#endif