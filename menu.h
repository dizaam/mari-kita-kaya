#ifndef _MENU_H
#define _MENU_H

#include "allheader.h"

extern int menuchoose;      // ini sebenarnnya bisa lokal
extern char logo[8][69];
extern char menu[6][11];

/*
    Author      : LM
    Tujuan      : Menggambar text di tengah layar
    I.S         : Di layar belum tampil teks
    F.S         : Di layar tampil teks
*/
void PrintCenter(WINDOW* win, int row, char* text);

/*
    Author      : LM
    Tujuan      : Menggambar logo
    I.S         : Di layar belum tampil logo
    F.S         : Di layar tampil logo
*/
void DrawLogo();

/*
    Author      : LM
    Tujuan      : Menggambar main menu
    I.S         : Di layar belum tampil pilihan menu
    F.S         : Di layar tampil pilihan menu
*/
void DrawMenu(int* highlight);

/*
    Author      : LM
    Tujuan      : Menggambar main menu
    I.S         : Di layar belum tampil pilihan menu
    F.S         : Di layar tampil pilihan menu
*/
void MainMenu();

/*
    Author      : LM
    Tujuan      : Menampilkan menu credits
    I.S         : Di layar belum tampil menu credits
    F.S         : Di layar tampil menu credits
*/
void Credits();

/*
    Author      : LM
    Tujuan      : Menampilkan menu help
    I.S         : Di layar belum tampil menu help
    F.S         : Di layar tampil menu help
*/
void Help();

/*
    Author      : LM
    Tujuan      : Menampilkan menu exit
    I.S         : Di layar belum tampil menu exit
    F.S         : Di layar tampil menu exit
*/
void Exit();

/*
    Author      : LM
    Tujuan      : Menggambar logo kemenangan default
    I.S         : Di layar belum tampil logo kemenangan default
    F.S         : Di layar tampil kemenangan default
*/
void DrawLogoDefaultWin();

/*
    Author      : LM
    Tujuan      : Menggambar logo kemenangan garis
    I.S         : Di layar belum tampil logo kemenangan garis
    F.S         : Di layar tampil kemenangan garis
*/
void DrawLogoLineWin();

/*
    Author      : LM
    Tujuan      : Menggambar logo kemenangan tempat pariwisata
    I.S         : Di layar belum tampil logo kemenangan tempat pariwisata
    F.S         : Di layar tampil kemenangan tempat pariwisata
*/
void DrawLogoTourismWin();

/*
    Author      : SWA
    Tujuan      : Menampilkan menu highscore
    I.S         : Di layar belum tampil menu highscore
    F.S         : Di layar tampil menu highscore
*/
void HighScore();


#endif