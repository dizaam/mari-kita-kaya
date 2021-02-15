#ifndef _GAME_H
#define _GAME_H

#include "allheader.h"

#define PROP0_COLOR 0
#define PROP1_COLOR 1
#define PROP2_COLOR 2
#define PROP3_COLOR 3
#define PROP4_COLOR 4
#define PLAYER1_COLOR 5
#define PLAYER2_COLOR 6
#define PLAYER3_COLOR 7
#define PLAYER4_COLOR 8

typedef struct savedgame{
    PPLAYER player[4];
    int turn[4];
    int totalplayer;
    int currentturn;

    CCARD card;
    int deckCard[20];

    PPROPERTY property[32];

    char map[40][100];
}savedgame;

extern WINDOW*  wactionborder, *wpinfoborder, *wbinfoborder;
extern WINDOW*  waction, *wpinfo, *wbinfo;
extern char actionlistunowned[2][30];
extern char actionlistupgrade[2][30];
extern char actionlistjailed[3][30];
extern char actionlistoptiongame[3][30];

extern int wintype;

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
void DrawActionListOptionGame(int* highlight);
void DrawActionOptionGame();
void DrawActionPayRent();

void ShowBoardInfo();
void ShowPropertyInfo();
void ShowTourismInfo();

bool isDefaultWin();
bool isTourismWin();
bool isLineWin();
void ShowScore();
int getAsset(int thisplayer);
int getScore(int wintype, int asset);
void SaveGame();
void LoadGame();


#endif