#ifndef _GAME_H
#define _GAME_H

#include "system.h"

extern WINDOW*  wactionborder, *wpinfoborder, *wbinfoborder;
extern WINDOW*  waction, *wpinfo, *wbinfo;
extern char actionlistunowned[2][30];
extern char actionlistupgrade[2][30];
extern char actionlistjailed[3][30];

void InitWindow();
int* shakeTurn(int temp[totalplayer][2]);
void TurnSetup();
void SetupNewGame();

void DrawActionBorder();
void DrawPlayerInfoBorder();
void DrawBoardInfoBorder();
void DrawWidget();

void ShowInfoDouble();

void DrawActionListJailed(int* highlight);
void DrawActionJailed();
void ShowJailCardMessage();
void ShowPayJailMessage();
void ShowTaxInfo();
void DrawActionPayTax();

void DrawActionUnownedProperty();
void DrawActionListUpgrade(int* highlight);
void DrawActionUpgradeProperty();
void ShowBuySucces();
void ShowBuyFailed();
void ShowOwnedByself();
void ShowRentInfo();
void ShowPayRentSucces();
void ShowPayRentFailed();
void ShowUpgradeSucces();
void ShowUpgradeFailed(int type);

void DrawActionRollDice();
void DrawActionEndTurn();
void DrawActionPayRent();

void UpdatePlayerInfo();

void DrawDiceResult();
void DrawDiceSymbol();

void UpdatePosition();
void UpdateBoardInfo();
void ShowPropertyInfo();
void ShowTourismInfo();


#endif