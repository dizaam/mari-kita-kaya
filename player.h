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
extern int totalplayer;                                     // ini sebenarnnya bisa lokal
extern int* turn;
extern int currentturn;                                      // ini sebenarnnya bisa lokal
extern int currentplayer;                                    // ini sebenarnnya bisa lokal
extern int playerchoose;                                       // ini sebenarnnya bisa lokal
extern int playerwinner;                                        // ini sebenarnnya bisa lokal

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