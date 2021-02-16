#ifndef _BOT_H
#define _BOT_H

#include "allheader.h"


typedef struct{
    bool istherebot;
    int level;
}BBOT;

extern BBOT bot;
extern char actionlistbotlevel[3][10];

int randNum(int lower, int upper);
void DrawActionListBotLevel(int* highlight);
void DrawActionBotLevel();
void SetupBot();
void BotLeaveJail();
void BotVisitTourism();
void BotVisitProperty();
void BotUpgrade();
void BotNeedMoney();

#endif