#ifndef _GAME_H
#define _GAME_H

#include "system.h"

#define PLAYER1_COLOR 1
#define PLAYER2_COLOR 2
#define PLAYER3_COLOR 3
#define PLAYER4_COLOR 4

extern WINDOW*  wactionborder, *wpinfoborder, *wbinfoborder;
extern WINDOW*  waction, *wpinfo, *wbinfo;
extern char actionlistunowned[2][30];
extern char actionlistupgrade[2][30];
extern char actionlistjailed[3][30];

void InitWindow();
void InitColor();
int* shuffleTurn(int temp[totalplayer][2]);
void TurnSetup();
void SetupNewGame();
void DrawActionBorder();
void DrawPlayerInfoBorder();
void DrawBoardInfoBorder();
void DrawWidget();

void Action();
void PlayGame();
void MovePlayer(char* typeMove, int stepMove);

void ShowPlayerInfo();
void ShowInfoDouble();
void DrawActionListJailed(int* highlight);
void DrawActionJailed();
void ShowJailCardMessage();
void ShowPayJailMessage();
void DrawActionListNeedMoney(int* highlight);
void DrawActionNeedMoney();
void ActionNeedMoney(int playerchoose, int moneyneeded);
void ShowSuccesAutoSell(int price);
void ShowFailedAutoSell(int price);
void ShowTaxInfo();
void ShowFailedTaxInfo();
void ShowSuccesTaxInfo();
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
void DrawDiceResult();
void DrawDiceSymbol();
void UpdateBoardInfo();
void ShowPropertyInfo();
void ShowTourismInfo();


#endif