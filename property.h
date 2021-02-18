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
/*
    Author      : LM 
    Tujuan      : Mereset nilai property ke nilai default
    I.S         : Nilai property berbeda dengan default
    F.S         : Nilai property sama dengan default
*/
void SetDefaultProperty();

/*
    Author      : LM 
    Tujuan      : Mengembalikan pemilik property
    I.S         : Property milik pemain lain
    F.S         : Property tidak ada pemilik
*/
void AutoSellProperty(int moneyneeded);

#endif