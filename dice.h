#ifndef _DICE_H
#define _DICE_H

#include "allheader.h"


// membuat tipe data dadu 
typedef struct DDICE{
    int dice1;
    int dice2;
    int totaldice;
    int countdouble;
    bool isdouble;
}DDICE;

// variabel global
extern DDICE dice;
extern char dicesymbol[10][10][10];

// prosedur untuk mereset nilai dadu
void resetDice();

// prosedur untuk mengocok dadu
void shakeDice();

void DrawDiceSymbol();

#endif