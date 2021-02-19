#ifndef _CARD_H
#define _CARD_H
#include "allheader.h"

typedef struct CCARD{
    int position;
}CCARD;

#define DECKSIZE 20

// variabel global
extern int deckCard[DECKSIZE];                                   // ini sebenarnnya bisa lokal
extern CCARD card;                                              // ini sebenarnnya bisa lokal

/*
    Author      : SWA
    Tujuan      : Mereturn nilai random
*/
int rrandom(int low, int high);

/*
    Author      : SWA
    Tujuan      : Menginisialisasi struktur kartu kesempatan
    I.S         : Kartu kesempatan tidak diketahui
    F.S         : Kartu kesempatan diketahui
*/
void InitCard();

/*
    Author      : SWA
    Tujuan      : Mengacak kartu kesempatan
    I.S         : Kartu kesempatan dalam kondisi terurut
    F.S         : Kartu kesempatan dalam kondisi acak
*/
void ShuffleCard();

/*
    Author      : SWA
    Tujuan      : Mereturn nilai posisi kartu kesempatan [index]
*/
int getCardPosition();

/*
    Author      : SWA
    Tujuan      : Mendapat kartu kesempatan
*/
int getCard();

/*
    Author      : SWA
    Tujuan      : Aksi ke petak kartu kesempatan
    I.S         : Aksi pemain pada kartu kesempatan belum terlaksana
    F.S         : Aksi pemain pada kartu kesempatan terlaksana
*/
void CardAction();

/*
    Author      : SWA
    Tujuan      : Menampilkan kekurangan uang ketika diminta uang oleh kartu kesempatan
    I.S         : Di layar belum tampil status kekurangan uang
    F.S         : Di layar tertampil status kekurangan uang
*/
void ShowCardNeedMoney();

/*
    Author      : SWA
    Tujuan      : Menambah uang pemain dari kartu kesempatan
    I.S         : Uang pemain belum bertambah
    F.S         : Uang pemain bertambah
*/
void CardUpdateMoney(char* type, int money);

/*
    Author      : SWA
    Tujuan      : Menampilkan informasi kartu kesempatan
    I.S         : Di layar belum tampil informasi kartu kesempatan
    F.S         : Di layar tampil informasi kartu kesempatan
*/
void ShowCardInfo(char* text);

#endif