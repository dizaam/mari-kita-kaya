#ifndef _GAME_H
#define _GAME_H

#include "system.h"

extern WINDOW*  waction, *wpinfo, *wbinfo;
extern char actionlist[5][30];

void InitWindow();
int* shakeTurn(int temp[totalplayer][2]);
void TurnSetup();
void SetupNewGame();

void DrawActionBox();
void DrawPlayerInfoBox();
void DrawBoardInfoBox();
void DrawWidget();



void DrawActionList(int* highlight);
void DrawAction();
void DrawActionRollDice();
void DrawActionEndTurn();

void UpdatePlayerInfo();

void DrawDiceResult();
void DrawDiceSymbol();

void UpdatePosition();
void UpdateBoardInfo();


#endif