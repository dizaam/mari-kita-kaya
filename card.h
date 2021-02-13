#ifndef _CARD_H
#define _CARD_H
#include "system.h"

typedef struct CCARD{
    int position;
}CCARD;

extern CCARD card;

#define DECKSIZE 20
extern int deckCard[DECKSIZE];

int rrandom(int low, int high);
void initCard();
void writeCard();
void shuffleCard();
int getCardPosition();
int getCard();
void CardAction();
void ShowCardNeedMoney();

void cardUpdateMoney(char* type, int money);

void ShowCardInfo(char* text);

#endif