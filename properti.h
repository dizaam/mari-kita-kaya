#ifndef _PROPERTI_H
#define _PROPERTI_H

#include "system.h"


typedef struct properti{
    char name[50];
    int owner;
    int level;
    int price[5];
    int upgradeprice;
}properti;

extern properti property[32];
void ShowHargaBangunan();

#endif