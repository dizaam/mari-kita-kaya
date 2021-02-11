#ifndef _DADU_H
#define _DADU_H

#include "system.h"


// membuat tipe data dadu 
typedef struct DDICE{
    int dice1;
    int dice2;
    int totaldice;
    int countdouble;
    bool isdouble;

}DDICE;

//dadu dadu;
extern DDICE dice;
extern char dicesymbol[10][10][10];

// prosedur untuk mereset nilai dadu
void resetDice();

// prosedur untuk mengocok dadu
void shakeDice();

#endif