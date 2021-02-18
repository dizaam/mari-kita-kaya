#ifndef _BOT_H
#define _BOT_H

#include "allheader.h"


typedef struct{
    bool istherebot;
    int level;
}BBOT;

// variabel global
extern BBOT bot;
extern char actionlistbotlevel[3][10];

/*
    Author      : SWA
    Tujuan      : Mereturn nilai random
*/
int randNum(int lower, int upper);

/*
    Author      : SWA
    Tujuan      : Menampilkan pilihan kesusahan bot
    I.S         : Di layar belum tampil pilihan difficulty bot
    F.S         : Di layar tertampil pilihan difficulty bot
*/
void DrawActionListBotLevel(int* highlight);

/*
    Author      : SWA
    Tujuan      : Mendapatkan pilihan aksi
    I.S         : Aksi pilihan tidak diketahui
    F.S         : Aksi pilihan diketahui
*/
void DrawActionBotLevel();

/*
    Author      : SWA
    Tujuan      : Mengatur tingkat kesulitan bot
    I.S         : Kesulitan bot tidak diketahui
    F.S         : Kesulitan bot diketahui
*/
void SetupBot();

/*
    Author      : SWA
    Tujuan      : Aksi bot untuk keluar penjara
    I.S         : Bot diam
    F.S         : Bot beraksi mencari cara keluar penjara
*/
void BotLeaveJail();

/*
    Author      : SWA
    Tujuan      : Aksi bot ke petak pariwisata
    I.S         : Bot diam
    F.S         : Bot beraksi 
*/
void BotVisitTourism();

/*
    Author      : SWA
    Tujuan      : Aksi bot ke petak property perumahan
    I.S         : Bot diam
    F.S         : Bot beraksi 
*/
void BotVisitProperty();

/*
    Author      : SWA
    Tujuan      : Aksi bot ke petak property perumahan untuk upgrade
    I.S         : Bot diam
    F.S         : Bot beraksi 
*/
void BotUpgrade();

/*
    Author      : SWA
    Tujuan      : Aksi bot ketika kekurangan uang
    I.S         : Bot diam
    F.S         : Bot beraksi 
*/
void BotNeedMoney();

#endif