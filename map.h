#ifndef _MAP_H
#define _MAP_H

#include "allheader.h"

typedef struct MAPPOSITION{
    int row;
    int col;
} MAPPOSITION;

// variabel global
extern WINDOW* wmap;
extern char map[40][100];
extern int board[32];

/*
    Author      : LM
    Tujuan      : Menggambar peta permainan
    I.S         : Di layar belum tampil peta permainan
    F.S         : Di layar tampil peta permainan
*/
void DrawMap();

/*
    Author      : LM
    Tujuan      : Menggambar warna property
    I.S         : Di layar warna property belum ada
    F.S         : Di layar warna property sudah ada
*/
void DrawProperty();

/*
    Author      : LM
    Tujuan      : Mereturn posisi koordinat map
*/
MAPPOSITION getMapPosition(int position);

/*
    Author      : LM
    Tujuan      : Menggambar bidak pemain
    I.S         : Di layar bidak pemain di posisi x1,y1
    F.S         : Di layar bidak pemain di posisi x2,y2
*/
void DrawPawn();

/*
    Author      : LM
    Tujuan      : Menghapus bidak pemain
    I.S         : Di layar tampil bidak pemain
    F.S         : Di layar tidak tampil bidak pemain
*/
void RemovePawn();

#endif