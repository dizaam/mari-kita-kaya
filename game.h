#ifndef _GAME_H
#define _GAME_H

#include "allheader.h"

#define PROP0_COLOR 0
#define PROP1_COLOR 1
#define PROP2_COLOR 2
#define PROP3_COLOR 3
#define PROP4_COLOR 4
#define PLAYER1_COLOR 5
#define PLAYER2_COLOR 6
#define PLAYER3_COLOR 7
#define PLAYER4_COLOR 8

typedef struct SAVEDATA{
    PPLAYER player[4];
    int turn[4];
    int totalplayer;
    int currentturn;

    CCARD card;
    int deckCard[20];

    PPROPERTY property[32];

    char map[40][100];
}SAVEDATA;

typedef struct SAVESCORE{
    char name[30];
    int score;
}SAVESCORE;


// deklarasi variabel global
extern WINDOW*  wactionborder, *wpinfoborder, *wbinfoborder;
extern WINDOW*  waction, *wpinfo, *wbinfo;
extern char actionlistunowned[2][30];
extern char actionlistupgrade[2][30];
extern char actionlistjailed[3][30];
extern char actionlistoptiongame[3][30];
extern int wintype;                                             // ini sebenarnnya bisa lokal
extern SAVESCORE winner;                                        // ini sebenarnnya bisa lokal

/*
    Author      : LM
    Tujuan      : Menginisialisasi window (layar)
    I.S         : Layar belum ada niali
    F.S         : Layar sudah ada nilai
*/
void InitWindow();

/*
    Author      : LM
    Tujuan      : Menginisialisasi nilai warna
    I.S         : Warna belum ada/bernilai
    F.S         : Warna bernilai
*/
void InitColor();

/*
    Author      : LM
    Tujuan      : Mengocok giliran
    I.S         : Giliran dalam kondisi terurut
    F.S         : Giliran dalam kondisi acak
*/
void ShuffleTurn(int temp[totalplayer][2]);

/*
    Author      : LM
    Tujuan      : Menginisialisasi giliran
    I.S         : Giliran belum terinisialisasi
    F.S         : Giliran terinisialisasi
*/
void TurnSetup();

/*
    Author      : LM
    Tujuan      : Mengatur permainan baru
    I.S         : Permainan belum mulai
    F.S         : Permainan mulai
*/
void NewGame();

/*
    Author      : LM
    Tujuan      : Menggambar border aksi
    I.S         : Di layar belum ada border aksi
    F.S         : Di layar ada border aksi
*/
void DrawActionBorder();

/*
    Author      : LM
    Tujuan      : Menggambar border informasi pemain
    I.S         : Di layar belum ada border informasi pemain
    F.S         : Di layar ada border informasi pemain
*/
void DrawPlayerInfoBorder();

/*
    Author      : LM
    Tujuan      : Menggambar border informasi petak
    I.S         : Di layar belum ada border informasi petak
    F.S         : Di layar ada border informasi petak
*/
void DrawBoardInfoBorder();

/*
    Author      : LM
    Tujuan      : Menggambar layar layar pendukung
    I.S         : Di layar belum ada layar pendukung
    F.S         : Di layar ada layar pendukung
*/
void DrawWidget();

/*
    Author      : LM
    Tujuan      : Aksi pemain ke tiap petak
    I.S         : Pemain belum beraksi
    F.S         : Pemain beraksi
*/
void Action();

/*
    Author      : LM
    Tujuan      : Memainkan monopoli
    I.S         : Permainan belum mulai
    F.S         : Permainan mulai
*/
void PlayGame();

/*
    Author      : SWA
    Tujuan      : Memindahkan pemain
    I.S         : Pemain berada di x
    F.S         : Pemain berada di y
*/
void MovePlayer(char* typeMove, int stepMove);

/*
    Author      : LM
    Tujuan      : Mengganti giliran
    I.S         : Giliran pemain x
    F.S         : Giliran pemain y
*/
void ChangeTurn();

/*
    Author      : LM
    Tujuan      : Aksi membutuhkan uang
    I.S         : Pemain kekurangan uang
    F.S         : Pemain mendapatkan uang / pemain bangkrut
*/
void ActionNeedMoney(int playerchoose, int moneyneeded);

/*
    Author      : LM
    Tujuan      : Mengecek kemenangan default
*/
bool isDefaultWin();

/*
    Author      : LM
    Tujuan      : Mengecek kemenangan tempat pariwisata
*/
bool isTourismWin();

/*
    Author      : LM
    Tujuan      : Mengecek kemenangan satu garis
*/
bool isLineWin();

/*
    Author      : LM
    Tujuan      : Menampilkan skor pemain
    I.S         : Di layar belum tampil skor pemain
    F.S         : Di layar tampil skor pemain
*/
void ShowScore();

/*
    Author      : LM
    Tujuan      : Mendapatkan nilai asset
*/
int getAsset(int thisplayer);

/*
    Author      : LM
    Tujuan      : Mendapatkan nilai skor
*/
int getScore(int wintype, int asset);

/*
    Author      : SWA
    Tujuan      : Mengesave permainan
    I.S         : Data save belum ada
    F.S         : Data save ada
*/
void SaveGame();

/*
    Author      : SWA
    Tujuan      : Meload permainan
    I.S         : Data permainan belum ada
    F.S         : Data permainan ada
*/
void LoadGame();

/*
    Author      : LM
    Tujuan      : Menginput nama pemain
    I.S         : Nama pemain belum ada
    F.S         : Nama pemain ada
*/
void InputName();

/*
    Author      : SWA
    Tujuan      : Mengesave skor
    I.S         : Data skor belum tersave
    F.S         : Data skor tersave
*/
void SaveScore(SAVESCORE hs);

/*
    Author      : LM
    Tujuan      : Memfree heap memory
    I.S         : Heap memory masih ada
    F.S         : Heap memory sudah tidak ada
*/
void FreeAll();

void DrawActionListJailed(int* highlight);
void DrawActionListNeedMoney(int* highlight);
void DrawActionListOptionGame(int* highlight);
void DrawActionListUpgrade(int* highlight);
void DrawActionJailed();
void DrawActionNeedMoney();
void DrawActionPayTax();
void DrawActionUnownedProperty();
void DrawActionUpgradeProperty();
void DrawActionRollDice();
void DrawActionEndTurn();
void DrawActionOptionGame();
void DrawActionPayRent();


void ShowPlayerInfo();
void ShowBoardInfo();
void ShowPropertyInfo();
void ShowTourismInfo();
void ShowInfoDouble();
void ShowJailCardMessage();
void ShowPayJailMessage();
void ShowSuccesAutoSell(int price);
void ShowFailedAutoSell(int price);
void ShowTaxInfo();
void ShowFailedTaxInfo();
void ShowSuccesTaxInfo();
void ShowBuySucces();
void ShowBuyFailed();
void ShowOwnedByself();
void ShowRentInfo(int rentprice);
void ShowPayRentSucces();
void ShowPayRentFailed();
void ShowUpgradeSucces();
void ShowUpgradeFailed(int type);

#endif