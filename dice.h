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
extern DDICE dice;                              // ini sebenarnnya bisa lokal
extern char dicesymbol[10][10][10];

/*
    Author      : SWA
    Tujuan      : Mereset dadu ke nilai awal
    I.S         : Nilai dadu sudah ada acak
    F.S         : Nilai dadu berubah ke nilai awal
*/
void ResetDice();

/*
    Author      : SWA
    Tujuan      : Mengocok dadu
    I.S         : Dadu bernilai default
    F.S         : Dadu bernilai acak
*/
void ShakeDice();

/*
    Author      : SWA
    Tujuan      : Menggambar simbol dadu
    I.S         : Di layar belum tampil simbol dadu
    F.S         : Di layar belum simbol dadu
*/
void DrawDiceSymbol();

#endif