#ifndef _PROPERTY_H
#define _PROPERTY_H

#include "allheader.h"


typedef struct PPROPERTY{
    char name[50];
    int owner;
    int level;
    int price[5];
    int upgradeprice;
    int line;
}PPROPERTY;

extern PPROPERTY property[32];
void SetDefaultAllProperty();
void AutoSellProperty(int moneyneeded);

#endif