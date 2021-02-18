#ifndef _PLAYER_H
#define _PLAYER_H

#include "allheader.h"



typedef struct PPLAYER{
    bool isbankrupt;
    bool isbot;
    bool isjailed;
    bool jailcard;

    int position; 
    int touristcount;
    int linecount[4];
    int money;
    int jailcount;

    char pawn;
}PPLAYER;



extern PPLAYER* player;
extern int totalplayer;
extern int* turn;
extern int currentturn;
extern int currentplayer;
extern int playerchoose;
extern int remainingplayer;
extern int playerwinner;

/*
    Author      : LM 
    Tujuan      : Menginisialisasi data pemain
    I.S         : Data pemain belum ada
    F.S         : Data pemain sudah ada
*/
void InitPlayer();

/*
    Author      : LM 
    Tujuan      : Menginput tipe main
*/
char inputPlayerType();

/*
    Author      : LM 
    Tujuan      : Mengubah status pemain menjadi bangkrut
    I.S         : Pemain aktif
    F.S         : Pemain tidak aktif / bangkrut
*/
void PlayerBankrupt();

#endif