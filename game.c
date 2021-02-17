#include "allheader.h"

WINDOW*  wactionborder, *wpinfoborder, *wbinfoborder;
WINDOW*  waction, *wpinfo, *wbinfo;


char actionlistunowned[2][30] = {
    "Beli Properti",
    "Do Nothing",
};

char actionlistupgrade[2][30] = {
    "Upgrade Properti",
    "Do Nothing",
};

char actionlistjailed[3][30] = {
    "Kocok Dadu Sampai Double",
    "Gunakan Kartu Bebas Penjara",
    "Sogok Petugas",
};

char actionlistoptiongame[3][30] = {
    "Lanjutkan Permainan",
    "Simpan Permainan",
    "Exit Game",
};

char actionlistneedmoney[2][30] = {
    "Jual Properti",
    "Bangkrut",
};

int wintype = 0;
SAVESCORE winner;

// menginisialisasi warna
void InitColor(){
    start_color();
    init_pair(PROP0_COLOR, COLOR_WHITE, COLOR_BLACK);
    init_pair(PROP1_COLOR, COLOR_BLUE, COLOR_BLACK);
    init_pair(PROP2_COLOR, COLOR_RED, COLOR_BLACK);
    init_pair(PROP3_COLOR, COLOR_GREEN, COLOR_BLACK);
    init_pair(PROP4_COLOR, COLOR_YELLOW, COLOR_BLACK);
    init_pair(PLAYER1_COLOR, COLOR_BLUE, COLOR_WHITE);
    init_pair(PLAYER2_COLOR, COLOR_RED, COLOR_WHITE);
    init_pair(PLAYER3_COLOR, COLOR_GREEN, COLOR_WHITE);
    init_pair(PLAYER4_COLOR, COLOR_YELLOW, COLOR_WHITE);
}

// modul untuk menginisialisasi window
void InitWindow(){
    wmap = newwin(37,91,0,0);
    wactionborder = newwin(7,91,37,0);
    waction = subwin(wactionborder, 5, 89, 38, 1);

    wpinfoborder = newwin(25, 40, 0, 92);
    wpinfo = subwin(wpinfoborder, 23, 38, 1, 93);

    wbinfoborder = newwin(19, 40, 25, 92);
    wbinfo = subwin(wbinfoborder, 17, 38, 26, 93);
}


// modul untuk mensortir giliran
int* shuffleTurn(int temp[totalplayer][2]){
    int* turn = (int*) calloc(totalplayer, sizeof(int));

    // selection sort
    for(int i=0; i<totalplayer; i++){
        int maxVal=i;

        for(int j=totalplayer-1; j>i; j--){
            if(temp[maxVal][0] < temp[j][0]){
                maxVal = j;
            }
        }

        int tempValue = temp[i][0];
        int tempIndex = temp[i][1];

        temp[i][0] = temp[maxVal][0];
        temp[i][1] = temp[maxVal][1];
        turn[i] = temp[maxVal][1];

        temp[maxVal][0] = tempValue;
        temp[maxVal][1] = tempIndex;    
    }
    
    return turn;
}

// modul untuk menentukan giliran
void TurnSetup(){
    clear();
    printw("PENENTUAN GILIRAN\n");
    int temp[totalplayer][2];
    turn = (int*) realloc(turn, sizeof(int)*totalplayer);

    // masing2 player mengocok dadu untuk menentukan gilirannya
    for(int i=0; i<totalplayer; i++){
        if(player[i].isbot) {
            // Jika BOT maka Auto Turn
            printw("\nBOT %d SILAHKAN MENGOCOK DADU\n", i+1);
            printw("ketik apa saja untuk mengocok...");
            napms(1500);
        } else {
            // Jika PLAYER 
            printw("\nPLAYER %d SILAHKAN MENGOCOK DADU\n", i+1);
            printw("ketik apa saja untuk mengocok...");
            getch();
        }
        
        ResetDice();
        ShakeDice();
        
        temp[i][0] = dice.totaldice;
        ResetDice();
        temp[i][1] = i;
        printw("\nDadu yg didapat: %d\n", temp[i][0]);
    }

    printw("\n");
    turn = shuffleTurn(temp);

    for(int i=0; i<totalplayer; i++){
        printw("Giliran ke-%d: Player %d\n", i+1, turn[i]+1);
    }
    printw("\nKetik apa saja untuk memulai Permainan");
    getch();
    
}

// menginisialisasi awal permainan
void NewGame(){
    clear();
    addstr("SETUP NEW GAME\n");

    // menentukan berapa player
    do{
        addstr("berapa player? (2-4): ");
        scanw("%d", &totalplayer);
        if ((totalplayer<2) || (totalplayer>4)){
            addstr("Minimal 2 Player & Maksimal 4 Player !!!\n");
        }
    }while ((totalplayer<2) || (totalplayer>4));
    InitPlayer();
    if(bot.istherebot) {
        SetupBot();
    }
    InitCard();
    TurnSetup();
}

// modul untuk menampilkan box pilihan
void DrawActionBorder(){
    wclear(wactionborder);
    touchwin(wactionborder);

    wattrset(wactionborder, A_ALTCHARSET);
    box(wactionborder, ACS_VLINE, ACS_HLINE);

    wattroff(wactionborder, A_ALTCHARSET);
    wrefresh(wactionborder);
}

// modul untuk menampilkan box informasi pemain
void DrawPlayerInfoBorder(){
    wclear(wpinfoborder);
    touchwin(wpinfoborder);

    wattrset(wpinfoborder, A_ALTCHARSET);
    box(wpinfoborder, ACS_VLINE, ACS_HLINE);

    wattroff(wpinfoborder, A_ALTCHARSET);

    wrefresh(wpinfoborder);
}

// modul untuk menampilkan petak yang diinjak
void DrawBoardInfoBorder(){
    wclear(wbinfoborder);
    touchwin(wbinfoborder);

    wattrset(wbinfoborder, A_ALTCHARSET);
    box(wbinfoborder, ACS_VLINE, ACS_HLINE);

    wattroff(wbinfoborder, A_ALTCHARSET);

    wrefresh(wbinfoborder);
}

// modul untuk shorthand memanggil 3 modul 
void DrawWidget(){
    DrawMap();

    DrawActionBorder();

    DrawPlayerInfoBorder();

    DrawBoardInfoBorder();
}

// modul game utama (game loop)
void PlayGame(){
    clear();
    refresh();
    InitWindow();

    while(1){
        // mereset dadu untuk giliran player sekarang
        ResetDice();
        currentplayer = turn[currentturn];

        if(player[currentplayer].isjailed){
        // jika pemain dipenjara
            refresh();
            DrawMap();
            DrawWidget();
            ShowPlayerInfo();

            playerchoose = 0;
            if(player[currentplayer].jailcount > 2) {
                playerchoose = 2;
                player[currentplayer].jailcount = 0;
            } else {
                if(player[currentplayer].isbot) {
                    // Jika BOT maka Auto Turn
                    napms(1500);
                    BotLeaveJail();
                } else {
                    // Jika PLAYER maka memilih opsi keluar penjara
                    DrawActionJailed();
                }
            }

            if(playerchoose == 0){
            // player memilih mengocok dadu
                if(player[currentplayer].isbot) {
                    // Jika BOT maka Auto Turn
                    napms(1500);
                } else {
                    // Jika PLAYER maka diberi opsi melempar dadu
                    DrawActionRollDice();
                }
                ShakeDice();
                DrawDiceSymbol();
                player[currentplayer].jailcount += 1;
                if(dice.isdouble){
                    // dadu berhasil double
                    player[currentplayer].isjailed=false;
                    MovePlayer("goto", dice.totaldice);
                    ShowBoardInfo();
                    Action();
                }
            }else if(playerchoose == 1){
            // player memilih menggunakan kartu bebas penjara
                ShowJailCardMessage();
                if(player[currentplayer].jailcard){
                    // mempunyai kartu bebas penjara
                    player[currentplayer].jailcard = false;
                    player[currentplayer].isjailed = false;
                    player[currentplayer].jailcount = 0;

                    if(player[currentplayer].isbot) {
                        // Jika BOT maka Auto Turn
                        napms(1500);
                    } else {
                        // Jika PLAYER maka diberi opsi melempar dadu
                        DrawActionRollDice();
                    }
                    ShakeDice();
                    DrawDiceSymbol();
                    MovePlayer("goto", dice.totaldice);
                    ShowBoardInfo();
                    Action();

                }
            }else if(playerchoose == 2){
            // player memilih menyogok petugas
                ShowPayJailMessage();
                if(player[currentplayer].money>=100){
                    // uang cukup
                    player[currentplayer].isjailed = false;
                    player[currentplayer].money -= 100;
                    player[currentplayer].jailcount = 0;

                    if(player[currentplayer].isbot) {
                        // Jika BOT maka Auto Turn
                        napms(1500);
                    } else {
                        // Jika PLAYER maka diberi opsi melempar dadu
                        DrawActionRollDice();
                    }
                    ShakeDice();
                    DrawDiceSymbol();
                    MovePlayer("goto", dice.totaldice);
                    ShowBoardInfo();
                    Action();
                }
            }

        }else{
        // pemain tidak dipenjara
            do{
                refresh();
                DrawWidget();
                ShowPlayerInfo();
                if(player[currentplayer].isbot) {
                    // Jika BOT maka Auto Turn
                    napms(1500);
                } else {
                    // Jika PLAYER maka diberi opsi melempar dadu
                    DrawActionRollDice();
                }
                ShakeDice();
                DrawDiceSymbol();
                
                // check jika player sudah 3x double
                if(dice.countdouble>=3){
                    mvwaddstr(wpinfo, 18, 0, "Double 3x Curang!                           ");
                    mvwaddstr(wpinfo, 18, 0, "Player Masuk Penjara                        ");
                    MovePlayer("moveto", 8);
                    player[currentplayer].isjailed=true;
                    break;
                }else{
                    MovePlayer("goto", dice.totaldice);
                }
                
                ShowBoardInfo();
                Action();

                if(dice.isdouble){
                    ShowInfoDouble();
                    if(player[currentplayer].isbot) {
                        // Jika BOT maka Auto Turn
                        napms(1500);
                    } else {
                        // Jika PLAYER maka diberi opsi input
                        wgetch(wpinfo);
                    }
                }
            }while((dice.isdouble) && (!player[currentplayer].isjailed) && (!player[currentplayer].isbankrupt));
        }
        if(player[currentplayer].isbot) {
            // Jika BOT maka Auto Turn
            napms(1500);
        } else {
            // Jika PLAYER maka diberi opsi akhiri giliran
            DrawActionEndTurn();
        }


        if(isDefaultWin()){
            // default win
            clear();
            touchwin(stdscr);
            DrawLogoDefaultWin();
            ShowScore();
            InputName();
            SaveScore(winner);
            refresh();
            break;
        
        }else if(isTourismWin()){
            // tourism win
            clear();
            touchwin(stdscr);
            DrawLogoTourismWin();
            ShowScore();
            InputName();
            SaveScore(winner);
            refresh();
            break;
            
        }else if(isLineWin()){
            // line win
            clear();
            touchwin(stdscr);
            DrawLogoLineWin();
            ShowScore();
            InputName();
            SaveScore(winner);
            refresh();
            break;
            
        }else{
            ChangeTurn();
        
            do{
                playerchoose = 0;
                if(player[currentplayer].isbot) {
                    // Jika BOT maka Auto Turn
                    napms(1500);
                    playerchoose = 0;
                } else {
                    // Jika PLAYER maka diberi opsi memilih
                    DrawActionOptionGame();
                }
                if(playerchoose == 0) {
                    // continue game
                } else if(playerchoose == 1) {
                    // save game
                    SaveGame();
                } else if(playerchoose == 2) {
                    // exit game
                }
            }while(playerchoose == 1);  
        }
    }

}

// modul interaksi dengan tiap2 petak
void Action(){
    switch(board[player[currentplayer].position]){
        case 0:
            // penjara
            MovePlayer("moveto", 8);
            player[currentplayer].isjailed=true;
    
            break;
        case 1:
            // start

            break;
        case 2:
            // bebas parkir

            break;
        case 3:
            // hanya lewat

            break;
        case 4:
            // kantor pajak
            ShowTaxInfo();
            
            if(player[currentplayer].isbot) {
                napms(1500);
            } else {
                DrawActionPayTax();
            }
            if(player[currentplayer].money < 100){
                // uang kurang
                ShowFailedTaxInfo();
                playerchoose = 0;
                if(player[currentplayer].isbot) {
                    // Jika BOT maka Auto Turn
                    napms(1500);
                    BotNeedMoney();
                } else {
                    // Jika PLAYER 
                    DrawActionNeedMoney();
                }
                ActionNeedMoney(playerchoose, 100);

            }else{
                // sukses bayar pajak
                player[currentplayer].money -= 100;
                ShowSuccesTaxInfo();
            }

            break;
        case 5:
            // kesempatan
            CardAction();

            break;
        case 6:
            // properti
            // belum ada owner
            if(property[player[currentplayer].position].owner == -1){
                playerchoose = 0;

                if(player[currentplayer].isbot) {
                    // Jika BOT maka Auto Turn
                    napms(1500);
                    BotVisitProperty();
                } else {
                    // Jika PLAYER 
                    DrawActionUnownedProperty();
                }
                if(playerchoose == 0){
                    if(property[player[currentplayer].position].price[0] > player[currentplayer].money){
                        ShowBuyFailed();
                    }else{
                        ShowBuySucces();
                        player[currentplayer].money -= property[player[currentplayer].position].price[0];
                        property[player[currentplayer].position].owner = currentplayer;
                        player[currentplayer].linecount[property[player[currentplayer].position].line]++;
                        DrawMap();
                    }
                    
                }
                
            // milik sendiri
            }else if(property[player[currentplayer].position].owner == currentplayer){
                ShowOwnedByself();
                playerchoose = 0;

                while(playerchoose != 1){
                    if(player[currentplayer].isbot) {
                        // Jika BOT maka Auto Turn
                        napms(1500);
                        BotUpgrade();
                    } else {
                        // Jika PLAYER 
                        DrawActionUpgradeProperty();
                    }
                    if(playerchoose == 0){
                        // uang kurang
                        if(property[player[currentplayer].position].upgradeprice > player[currentplayer].money){
                            ShowUpgradeFailed(0);
                        }
                        // level max
                        else if(property[player[currentplayer].position].level==4){
                            ShowUpgradeFailed(1);
                        }
                        // sukses
                        else{
                            property[player[currentplayer].position].level++;
                            ShowUpgradeSucces();
                            player[currentplayer].money -= property[player[currentplayer].position].upgradeprice;
                        }

                    }
                }   

            // milik pemain lain
            }else{
                int rentprice = property[player[currentplayer].position].price[property[player[currentplayer].position].level];
                ShowRentInfo(rentprice);
                if(player[currentplayer].isbot) {
                    // Jika BOT maka Auto Turn
                    napms(1500);
                } else {
                    // Jika PLAYER 
                    DrawActionPayRent();
                }
                if(player[currentplayer].money < rentprice){
                    // player kekurangan uang
                    ShowPayRentFailed();
                    playerchoose = 0;
                    if(player[currentplayer].isbot) {
                        // Jika BOT maka Auto Turn
                        napms(1500);
                        BotNeedMoney();
                    } else {
                        // Jika PLAYER 
                        DrawActionNeedMoney();
                    }
                    ActionNeedMoney(playerchoose, rentprice);
                    
                }else{
                    // pemain tidak kekurangan uang
                    player[currentplayer].money -= rentprice;
                    player[property[player[currentplayer].position].owner].money += rentprice;
                    ShowPayRentSucces(rentprice);
                }
            }

            break;
        case 7:
        // tempat wisata
            // belum ada owner
            if(property[player[currentplayer].position].owner == -1){
                playerchoose = 0;
                if(player[currentplayer].isbot) {
                    // Jika BOT maka Auto Turn
                    napms(1500);
                    BotVisitTourism();
                } else {
                    // Jika PLAYER 
                    DrawActionUnownedProperty();
                }
                if(playerchoose == 0){
                    if(property[player[currentplayer].position].price[0] > player[currentplayer].money){
                        ShowBuyFailed();
                    }else{
                        ShowBuySucces();
                        player[currentplayer].money -= property[player[currentplayer].position].price[0];
                        property[player[currentplayer].position].owner = currentplayer;
                        player[currentplayer].touristcount++;
                        player[currentplayer].linecount[property[player[currentplayer].position].line]++;
                        DrawMap();
                    }
                    
                }
                
            // milik sendiri
            }else if(property[player[currentplayer].position].owner == currentplayer){
                ShowOwnedByself();

            // milik pemain lain
            }else{
                int rentprice = property[player[currentplayer].position].price[player[property[player[currentplayer].position].owner].touristcount-1];
                ShowRentInfo(rentprice);
                if(player[currentplayer].isbot) {
                    // Jika BOT maka Auto Turn
                    napms(1500);
                } else {
                    // Jika PLAYER 
                    DrawActionPayRent();
                }
                if(player[currentplayer].money < rentprice){
                    ShowPayRentFailed();
                    playerchoose = 0;

                    if(player[currentplayer].isbot) {
                        // Jika BOT maka Auto Turn
                        napms(1500);
                        BotNeedMoney();
                    } else {
                        // Jika PLAYER 
                        DrawActionNeedMoney();
                    }
                    ActionNeedMoney(playerchoose, rentprice);
                    
                }else{
                    player[currentplayer].money -= rentprice;
                    ShowPayRentSucces(rentprice);
                    
                }
            }
            break;
        default:
            break;
    }
}

// modul untuk mengganti giliran
void ChangeTurn(){
    do{
        currentturn++;
        if(currentturn==totalplayer){
            currentturn=0;
        } 
    }while(player[turn[currentturn]].isbankrupt);
}


// modul untuk mengubah posisi pemain
void MovePlayer(char* typeMove, int stepMove){
    touchwin(wpinfo);
    RemovePawn();

    // Proccess of Moving Player to some place
    if(!strcmp(typeMove, "moveto")) {
        player[currentplayer].position = stepMove;
    } else if(!strcmp(typeMove, "goto")) {
        player[currentplayer].position += stepMove;

        if(player[currentplayer].position > 31){
            player[currentplayer].position = player[currentplayer].position-32;
            player[currentplayer].money += 200;
        }

        if(player[currentplayer].position < 0){
            player[currentplayer].position = 32+player[currentplayer].position;
        }
    }

    if(!player[currentplayer].isbankrupt){
        DrawPawn();
    }
    
    wrefresh(wpinfo);
}

void ShowInfoDouble(){
    touchwin(wpinfo);

    mvwaddstr(wpinfo, 22, 9, "Double! Mengocok Lagi");

    wrefresh(wpinfo);
}


// action list sedang dipenjara
void DrawActionListJailed(int* highlight){
    touchwin(waction);

    if(*highlight > 2){
        *highlight = 2;
    }else if(*highlight < 0){
        *highlight = 0;
    }

    for(int i=0; i<3; i++){
        if(i==*highlight){
            wattrset(waction, A_REVERSE);
        }
        mvwaddstr(waction, i, 2, actionlistjailed[i]);
        wattroff(waction, A_REVERSE);
    }

    wrefresh(waction);
}

void DrawActionJailed(){
    touchwin(waction);

    int keyp = 0;
    int highlight = 0;
   
    keypad(waction, true);

    DrawActionListJailed(&highlight);
    noecho();
    do{
        keyp = wgetch(waction);

        switch(keyp){
            case KEY_UP:
                highlight--;
                DrawActionListJailed(&highlight);
                playerchoose = highlight;
                break;
            case KEY_DOWN:
                highlight++;
                DrawActionListJailed(&highlight);
                playerchoose = highlight;
                break;
        }
        wrefresh(waction);
    }while(keyp != '\n');

    for(int i=0; i<5; i++){
        mvwaddstr(waction, i, 0, "                                                 ");
    }
    

    wrefresh(waction);   
}

// informasi menggunakan kartu bebas penjara
void ShowJailCardMessage(){
    touchwin(wpinfo);
    if(player[currentplayer].jailcard){
        mvwaddstr(wpinfo, 5, 0, "Menggunakan Kartu Bebas Penjara");
    }else{
        mvwaddstr(wpinfo, 5, 0, "Tidak Memiliki Kartu Bebas Penjara");
    }

    wrefresh(wpinfo);
}

// informasi status pembayaran suap petugas penajara
void ShowPayJailMessage(){
    touchwin(wpinfo);

    if(player[currentplayer].money>=100){
        mvwaddstr(wpinfo, 5, 0, "Membayar Petugas Sebesar 100");
    }else{
        mvwaddstr(wpinfo, 5, 0, "Uang Tidak Mencukupi");
    }

    wrefresh(wpinfo);
}

// pilihan ketika pemain kekurangan uang
void DrawActionListNeedMoney(int* highlight){
    touchwin(waction);

    if(*highlight > 1){
        *highlight = 1;
    }else if(*highlight < 0){
        *highlight = 0;
    }

    for(int i=0; i<2; i++){
        if(i==*highlight){
            wattrset(waction, A_REVERSE);
        }
        mvwaddstr(waction, i, 2, actionlistneedmoney[i]);
        wattroff(waction, A_REVERSE);
    }
    wrefresh(waction);
}

void DrawActionNeedMoney(){
    touchwin(waction);
    int keyp = 0;
    int highlight = 0;
   
    keypad(waction, true);

    DrawActionListNeedMoney(&highlight);
    noecho();
    do{
        keyp = wgetch(waction);

        switch(keyp){
            case KEY_UP:
                highlight--;
                DrawActionListNeedMoney(&highlight);
                playerchoose = highlight;
                break;
            case KEY_DOWN:
                highlight++;
                DrawActionListNeedMoney(&highlight);
                playerchoose = highlight;
                break;
        }
        wrefresh(waction);
    }while(keyp != '\n');

    for(int i=0; i<5; i++){
        mvwaddstr(waction, i, 0, "                                                 ");
    }

    wrefresh(waction);   
}


// aksi kekurangan uang
void ActionNeedMoney(int playerchoose, int moneyneeded){
    if(playerchoose == 0){
        // auto jual properti 
        AutoSellProperty(moneyneeded);
        if(player[currentplayer].money < moneyneeded){
            // uang jual hasil properti TIDAK mencukupi
            // player bangkrut
            ShowFailedAutoSell(moneyneeded);
            PlayerBankrupt();
        }else{
            // uang hasil jual properti mencukupi
            ShowSuccesAutoSell(moneyneeded);
            player[currentplayer].money -= moneyneeded;
        }
    }else if(playerchoose == 1){
        // player memilih bangkrut
        PlayerBankrupt();
    }
    DrawMap();
}

void ShowSuccesAutoSell(int price){
    touchwin(wpinfo);

    mvwaddstr(wpinfo, 15, 0, "Menjual Beberapa Property                                       ");
    mvwprintw(wpinfo, 16, 0, "Uang Didapat: %d                                                ", player[currentplayer].money);

    mvwprintw(wpinfo, 18, 0, "Uang Dibutuhkan   : %d                                          ", price);
    mvwprintw(wpinfo, 19, 0, "Uang Tersisa      : %d                                          ", player[currentplayer].money-price);
    mvwaddstr(wpinfo, 20, 0, "Sukses Membayar Sewa                                            ");
    

    wrefresh(wpinfo);
}

void ShowFailedAutoSell(int price){
    touchwin(wpinfo);

    mvwaddstr(wpinfo, 15, 0, "Menjual Beberapa Property                                       ");
    mvwprintw(wpinfo, 16, 0, "Uang Didapat: %d                                                ", player[currentplayer].money);

    mvwprintw(wpinfo, 18, 0, "Uang Dibutuhkan   : %d                                          ", price);
    mvwprintw(wpinfo, 19, 0, "Uang Tidak Mencukupi                                            ");
    mvwaddstr(wpinfo, 20, 0, "Kamu Dinyatakan Bangkrut                                        ");

    wrefresh(wpinfo);
}


// modul untuk informasi pembayaran pajak
void ShowTaxInfo(){
    touchwin(wpinfo);

    mvwaddstr(wpinfo, 15, 0, "Bayar Pajak Sebesar 100");
    
    wrefresh(wpinfo);

}

// pesan gagal bayar pajak
void ShowFailedTaxInfo(){
    touchwin(wpinfo);

    mvwaddstr(wpinfo, 18, 0, "Gagal Bayar Pajak                     ");
    mvwaddstr(wpinfo, 19, 0, "Uang Tidak Mencukupi");
    
    wrefresh(wpinfo);

}

// pesan sukses membayar pajak
void ShowSuccesTaxInfo(){
    touchwin(wpinfo);

    mvwaddstr(wpinfo, 18, 0, "Sukses Membayar Pajak                  ");
    mvwprintw(wpinfo, 19, 0, "Uangmu Berkurang 100 Menjadi %d", player[currentplayer].money);
    
    wrefresh(wpinfo);

}

// moudul untuk menampilkan aksi pembayaran pajak
void DrawActionPayTax(){
    touchwin(waction);
    int keyp = 0;

    wattrset(waction, A_REVERSE);
    mvwaddstr(waction, 0, 2, "Bayar Pajak");
    wattroff(waction, A_REVERSE);

    noecho();

    do{
        keyp = wgetch(waction);
    }while(keyp!='\n');

    for(int i=0; i<5; i++){
        mvwaddstr(waction, i, 0, "                        ");
    }
    wrefresh(waction);
}


void DrawActionListUnowned(int* highlight){
    touchwin(waction);
    if(*highlight > 1){
        *highlight = 1;
    }else if(*highlight < 0){
        *highlight = 0;
    }


    for(int i=0; i<2; i++){
        if(i==*highlight){
            wattrset(waction, A_REVERSE);
        }
        mvwaddstr(waction, i, 2, actionlistunowned[i]);
        wattroff(waction, A_REVERSE);
    }

    wrefresh(waction);
}

// opsi ketika properti belum mempunyai pemilik
void DrawActionUnownedProperty(){
    touchwin(waction);

    int keyp = 0;
    int highlight = 0;
   
    keypad(waction, true);

    DrawActionListUnowned(&highlight);
    noecho();
    do{
        keyp = wgetch(waction);

        switch(keyp){
            case KEY_UP:
                highlight--;
                DrawActionListUnowned(&highlight);
                playerchoose = highlight;
                break;
            case KEY_DOWN:
                highlight++;
                DrawActionListUnowned(&highlight);
                playerchoose = highlight;
                break;
        }
        wrefresh(waction);
    }while(keyp != '\n');

    for(int i=0; i<5; i++){
        mvwaddstr(waction, i, 0, "                        ");
    }
    

    wrefresh(waction);
}

// notifikasi sukses membeli properti
void ShowBuySucces(){
    touchwin(wpinfo);

    mvwaddstr(wpinfo, 15, 0, "Sukses Membeli Property!");
    mvwprintw(wpinfo, 16, 0, "Property %s Menjadi Milikmu!", property[player[currentplayer].position].name);
    mvwprintw(wpinfo, 17, 0, "Uangmu Berkurang %d Menjadi %d", property[player[currentplayer].position].price[0], player[currentplayer].money-property[player[currentplayer].position].price[0]);


    wrefresh(wpinfo);
}

// notifikasi gagal membeli properti
void ShowBuyFailed(){
    touchwin(wpinfo);

    mvwaddstr(wpinfo, 15, 0, "Gagal Membeli Property!");
    mvwaddstr(wpinfo, 16, 0, "Uangmu Tidak Mencukupi :(");

    wrefresh(wpinfo); 
}

void ShowOwnedByself(){
    touchwin(wpinfo);

    mvwaddstr(wpinfo, 15, 0, "Properti Ini Milikmu");
    mvwaddstr(wpinfo, 16, 0, "Upgrade Atau Akhiri Giliran");

    wrefresh(wpinfo); 
}

void DrawActionListUpgrade(int* highlight){
    touchwin(waction);
    if(*highlight > 1){
        *highlight = 1;
    }else if(*highlight < 0){
        *highlight = 0;
    }


    for(int i=0; i<2; i++){
        if(i==*highlight){
            wattrset(waction, A_REVERSE);
        }
        mvwaddstr(waction, i, 2, actionlistupgrade[i]);
        wattroff(waction, A_REVERSE);
    }

    wrefresh(waction);
}

void DrawActionUpgradeProperty(){
    touchwin(waction);

    int keyp = 0;
    int highlight = 0;
   
    keypad(waction, true);

    DrawActionListUpgrade(&highlight);
    noecho();
    do{
        keyp = wgetch(waction);

        switch(keyp){
            case KEY_UP:
                highlight--;
                DrawActionListUpgrade(&highlight);
                playerchoose = highlight;
                break;
            case KEY_DOWN:
                highlight++;
                DrawActionListUpgrade(&highlight);
                playerchoose = highlight;
                break;
        }
        wrefresh(waction);
    }while(keyp != '\n');

    for(int i=0; i<5; i++){
        mvwaddstr(waction, i, 0, "                        ");
    }
    

    wrefresh(waction);  
}

// notifikasi sukses upgrade properti
void ShowUpgradeSucces(){
    touchwin(wpinfo);

    mvwaddstr(wpinfo, 18, 0, "Sukses Melakukan Upgrade");
    mvwprintw(wpinfo, 19, 0, "Properti Menjadi Level %d", property[player[currentplayer].position].level);
    mvwprintw(wpinfo, 20, 0, "Uangmu Berkurang %d Menjadi %d", property[player[currentplayer].position].upgradeprice, player[currentplayer].money-property[player[currentplayer].position].upgradeprice);

    wrefresh(wpinfo);
}

//notifikasi gagal upgrade properti
void ShowUpgradeFailed(int type){
    touchwin(wpinfo);

    mvwaddstr(wpinfo, 18, 0, "                                            ");
    mvwaddstr(wpinfo, 19, 0, "                                            ");
    mvwaddstr(wpinfo, 20, 0, "                                            ");

    if(type==0){
        mvwaddstr(wpinfo, 18, 0, "Gagal Melakukan Upgrade");
        mvwaddstr(wpinfo, 19, 0, "Uang Tidak Mencukupi");
    }else if(type==1){
        mvwaddstr(wpinfo, 18, 0, "Gagal Melakukan Upgrade");
        mvwaddstr(wpinfo, 19, 0, "Level Sudah Mencapai Maks");
    }

    wrefresh(wpinfo);
}

// notifikasi harga sewa
void ShowRentInfo(int rentprice){
    touchwin(wpinfo);

    mvwprintw(wpinfo, 15, 0, "Properti Ini Milik Player %d", property[player[currentplayer].position].owner+1);
    mvwprintw(wpinfo, 16, 0, "Harga Sewa Sebesar %d", rentprice);

    wrefresh(wpinfo);
}

// sukses membayar sewa
void ShowPayRentSucces(int rentprice){
    touchwin(wpinfo);

    mvwprintw(wpinfo, 18, 0, "Sukses Membayar Sewa");
    mvwprintw(wpinfo, 19, 0, "Uangmu Berkurang %d Menjadi %d", rentprice, player[currentplayer].money);

    wrefresh(wpinfo);
}

// uang pembayaran sewa tidak mencukupi
void ShowPayRentFailed(){
    touchwin(wpinfo);

    mvwprintw(wpinfo, 18, 0, "Gagal Membayar Sewa");
    mvwprintw(wpinfo, 19, 0, "Uang Tidak Mencukupi");
    mvwprintw(wpinfo, 20, 0, "Silahkan Jual Properti Atau Bangkrut");

    wrefresh(wpinfo);
}

// opsi pilihan player membayar sewa
void DrawActionPayRent(){
    touchwin(waction);
    int keyp = 0;

    wattrset(waction, A_REVERSE);
    mvwaddstr(waction, 0, 2, "Bayar Sewa");
    wattroff(waction, A_REVERSE);

    noecho();

    do{
        keyp = wgetch(waction);
    }while(keyp!='\n');

    for(int i=0; i<5; i++){
        mvwaddstr(waction, i, 0, "                        ");
    }
    wrefresh(waction);
}

// modul untuk menampilkan tombol untuk mengocok dadu
void DrawActionRollDice(){
    touchwin(waction);
    int keyp = 0;

    wattrset(waction, A_REVERSE);
    mvwaddstr(waction, 0, 2, "Lempar Dadu");
    wattroff(waction, A_REVERSE);

    noecho();

    do{
        keyp = wgetch(waction);
    }while(keyp!='\n');

    for(int i=0; i<5; i++){
        mvwaddstr(waction, i, 0, "                        ");
    }
    wrefresh(waction);
}

void DrawActionEndTurn(){
    touchwin(waction);
    int keyp = 0;

    wattrset(waction, A_REVERSE);
    mvwaddstr(waction, 0, 2, "Akhiri Giliran");
    wattroff(waction, A_REVERSE);

    noecho();

    do{
        keyp = wgetch(waction);
    }while(keyp!='\n');

    for(int i=0; i<5; i++){
        mvwaddstr(waction, i, 0, "                        ");
    }

    wrefresh(waction);
}

void DrawActionListOptionGame(int* highlight){
    touchwin(waction);

    if(*highlight > 2){
        *highlight = 2;
    }else if(*highlight < 0){
        *highlight = 0;
    }

    for(int i=0; i<3; i++){
        if(i==*highlight){
            wattrset(waction, A_REVERSE);
        }
        mvwaddstr(waction, i, 2, actionlistoptiongame[i]);
        wattroff(waction, A_REVERSE);
    }

    wrefresh(waction);
}

void DrawActionOptionGame(){
    touchwin(waction);

    int keyp = 0;
    int highlight = 0;
   
    keypad(waction, true);

    DrawActionListOptionGame(&highlight);
    noecho();
    do{
        keyp = wgetch(waction);

        switch(keyp){
            case KEY_UP:
                highlight--;
                DrawActionListOptionGame(&highlight);
                playerchoose = highlight;
                break;
            case KEY_DOWN:
                highlight++;
                DrawActionListOptionGame(&highlight);
                playerchoose = highlight;
                break;
        }
        wrefresh(waction);
    }while(keyp != '\n');

    for(int i=0; i<5; i++){
        mvwaddstr(waction, i, 0, "                                                 ");
    }

    wrefresh(waction);   
}

// mengupdate box info player
void ShowPlayerInfo(){
    touchwin(wpinfo);
    
    char buff[20];
    if(player[currentplayer].isbot){
        sprintf(buff, "%s %d %s", "PLAYER", currentplayer+1, "(BOT)");
    }else{
        sprintf(buff, "%s %d", "PLAYER", currentplayer+1);
    }
    
    switch(currentplayer){
        case 0:
            wattrset(wpinfo, COLOR_PAIR(PLAYER1_COLOR) | A_REVERSE);
            break;
        case 1:
            wattrset(wpinfo, COLOR_PAIR(PLAYER2_COLOR) | A_REVERSE);
            break;
        case 2:
            wattrset(wpinfo, COLOR_PAIR(PLAYER3_COLOR) | A_REVERSE);
            break;
        case 3:
            wattrset(wpinfo, COLOR_PAIR(PLAYER4_COLOR) | A_REVERSE);
            break;
        default:
            break;
    }
    PrintCenter(wpinfo, -1, buff);
    wattrset(wpinfo, A_NORMAL);

    mvwprintw(wpinfo, 1,1,"Uang     : %d", player[currentplayer].money);
    mvwprintw(wpinfo, 2,1,"Posisi   : %d", player[currentplayer].position);
    if(player[currentplayer].isjailed){
        mvwprintw(wpinfo, 3,1,"Kamu Dipenjara...");
    }else{
        mvwprintw(wpinfo, 3,1,"Silahkan Mengocok Dadu...");
    }
    

    wrefresh(wpinfo);
}






// modul untuk mengupdate petak yang diinjak
void ShowBoardInfo(){
    touchwin(wbinfo);
    wclear(wbinfo);

    if(player[currentplayer].isbot) {
        // Jika BOT maka Auto Turn
        napms(1500);
    } else {
        // Jika PLAYER maka meminta input
        wgetch(wbinfo);
    }

    char petak[10];
    sprintf(petak, "%s %d", "PETAK", player[currentplayer].position);

    

    PrintCenter(wbinfo, -1, petak);

    switch(board[player[currentplayer].position]){
        case 0:
            // masuk penjara
            mvwprintw(wbinfo, 2, 1, "Kamu Berada Di Persidangan");
            mvwprintw(wbinfo, 3, 1, "Kamu Terbukti Melanggar Hukum! Pergi ke Penjara");
            if(player[currentplayer].isbot) {
                // Jika BOT maka Auto Turn
                napms(1500);
            } else {
                // Jika PLAYER maka meminta input
                wgetch(wpinfo);
            }
            break;

        case 1:
            // player berada pada petak start
            mvwprintw(wbinfo, 2, 1, "START");
           
            if(player[currentplayer].isbot) {
                // Jika BOT maka Auto Turn
                napms(1500);
            } else {
                // Jika PLAYER maka meminta input
                wgetch(wpinfo);
            }        
            break;
                
        case 2:
            // player berada pada petak bebas parkir
            mvwprintw(wbinfo, 2, 1, "Bebas Parkir");
          
            if(player[currentplayer].isbot) {
                // Jika BOT maka Auto Turn
                napms(1500);
            } else {
                // Jika PLAYER maka meminta input
                wgetch(wpinfo);
            }
            break;
                
        case 3:
            // penjara hanya lewat
            mvwprintw(wbinfo, 2, 1, "Hanya Lewat");
         
            if(player[currentplayer].isbot) {
                // Jika BOT maka Auto Turn
                napms(1500);
            } else {
                // Jika PLAYER maka meminta input
                wgetch(wpinfo);
            }
            break;
                
        case 4:
            // petak pajak, player membayar pajak
            mvwprintw(wbinfo, 2, 1, "Kantor Pajak");
         
            if(player[currentplayer].isbot) {
                // Jika BOT maka Auto Turn
                napms(1500);
            } else {
                // Jika PLAYER maka meminta input
                wgetch(wpinfo);
            }
            break;

        case 5:
            // player mendapat kartu kesempatan
            mvwprintw(wbinfo, 2, 1, "Kartu Kesempatan");
           
            if(player[currentplayer].isbot) {
                // Jika BOT maka Auto Turn
                napms(1500);
            } else {
                // Jika PLAYER maka meminta input
                wgetch(wpinfo);
            }
            break;
                
        case 6:
            // player berada pada petak properti

            PrintCenter(wbinfo, 1, property[player[currentplayer].position].name);
            ShowPropertyInfo();

          
            if(player[currentplayer].isbot) {
                // Jika BOT maka Auto Turn
                napms(1500);
            } else {
                // Jika PLAYER maka meminta input
                wgetch(wpinfo);
            }
            break;

        case 7:
            // player berada pada petak pariwisata
            PrintCenter(wbinfo, 1, property[player[currentplayer].position].name);
            ShowTourismInfo();

            if(player[currentplayer].isbot) {
                // Jika BOT maka Auto Turn
                napms(1500);
            } else {
                // Jika PLAYER maka meminta input
                wgetch(wpinfo);
            }
            break;
        }


    wrefresh(wbinfo);
}

// menampilkan informasi petak property 
void ShowPropertyInfo(){
    touchwin(wbinfo);
    char buff[8];

    sprintf(buff, "%s %d", "LEVEL", property[player[currentplayer].position].level);
    PrintCenter(wbinfo, 2, buff);

    mvwprintw(wbinfo,5, 1, "       Harga Beli   :\t%d", property[player[currentplayer].position].price[0]);
    mvwprintw(wbinfo,6, 1, "       Harga Upgrade:\t%d", property[player[currentplayer].position].upgradeprice);

    PrintCenter(wbinfo, 7, "Harga Sewa");
    mvwprintw(wbinfo,10, 1, "       Level  0 :\t%d", property[player[currentplayer].position].price[0]);
    mvwprintw(wbinfo,11, 1, "       Level  1 :\t%d", property[player[currentplayer].position].price[1]);
    mvwprintw(wbinfo,12, 1, "       Level  2 :\t%d", property[player[currentplayer].position].price[2]);
    mvwprintw(wbinfo,13, 1, "       Level  3 :\t%d", property[player[currentplayer].position].price[3]);
    mvwprintw(wbinfo,14, 1, "       Level MAX:\t%d", property[player[currentplayer].position].price[4]);

    wrefresh(wbinfo);
}

// menampilkan informasi petak property 
void ShowTourismInfo(){
    touchwin(wbinfo);

    mvwprintw(wbinfo,5, 2, "    Harga Beli:\t       %d", property[player[currentplayer].position].price[0]);

    PrintCenter(wbinfo, 6, "Harga Sewa");
    mvwprintw(wbinfo,8, 2, "   Memiliki 1 :\t       %d", property[player[currentplayer].position].price[0]);
    mvwprintw(wbinfo,9, 2, "   Memiliki 2 :\t      %d", property[player[currentplayer].position].price[1]);
    mvwprintw(wbinfo,10, 2, "   Memiliki 3 :\t      %d", property[player[currentplayer].position].price[3]);
    mvwprintw(wbinfo,11, 2, "   Memiliki 4 :\t   MENANG");

    wrefresh(wbinfo);
}

// modul untuk mengecek default win
bool isDefaultWin(){
    for(int i=0; i<totalplayer; i++){
        if(!player[i].isbankrupt){
            playerwinner = i;
        }
    }
    wintype = 0;
    return (remainingplayer==1) ? true:false;
}

// modul untuk mengecek line win
bool isLineWin(){
    bool ret = false;

    if(player[currentplayer].linecount[0]==6){
        ret = true;
    }
    
    if(player[currentplayer].linecount[1]==5){
        ret = true;
    }
    
    if(player[currentplayer].linecount[2]==6){
        ret = true;
    }
    
    if(player[currentplayer].linecount[3]==5){
        ret = true;
    }
    

    wintype = 1;
    playerwinner = currentplayer;
    return ret;
}

// modul untuk mengecek tourism win
bool isTourismWin(){
    bool ret = false;

    for(int i=0; i<totalplayer; i++){
        if(player[i].touristcount==4){

            ret = true;
        }
    }
    
    wintype = 2;
    playerwinner = currentplayer;
    return ret;
}



// modul untuk menampilkan score
void ShowScore(){
    char moneytext[100];
    char assettext[100];
    char scoretext[100];
    char playertext[100];

    int asset = getAsset(playerwinner);
    int score = getScore(wintype, asset);
    winner.score = score;

    sprintf(playertext,"Player %d Menang !", playerwinner+1);
    sprintf(moneytext, "Total Uang  : %d", player[playerwinner].money);
    sprintf(assettext, "Total Asset : %d", asset);
    sprintf(scoretext, "Score       : %d", score);

    PrintCenter(stdscr, 13, playertext);
    PrintCenter(stdscr, 15, moneytext);
    PrintCenter(stdscr, 17, assettext);
    PrintCenter(stdscr, 19, scoretext);
    

}

// modul untuk mengetahui asset pemain
int getAsset(int thisplayer){
    int asset = player[thisplayer].money;

    for(int i=0; i<32; i++){
        if (property[i].owner == thisplayer){
            asset += property[i].upgradeprice * property[i].level + property[i].price[0];
        }
    }

    return asset;
}


// modul untuk mengetahui score
int getScore(int wintype, int asset){
    int score = 0;

    switch (wintype){
        case 0:
            score = asset;
            break;
        case 1:
            score = asset*3;
            break;
        case 2:
            score = asset*5;
            break;
        default:
            break;
    }   

    return score;
}

// modul untuk save game
void SaveGame() {
    FILE *savefile;	
    savefile = fopen("savegame.dat","w");
    
    if(savefile==NULL) {
        // show error message "system error while saving"
    }

    SAVEDATA savegame;
    // Saving Player & Turn Player
    savegame.totalplayer = totalplayer;
    for(int loop=0; loop<totalplayer; loop++) {
        savegame.player[loop] = player[loop];
        savegame.turn[loop] = turn[loop];
    }
    savegame.currentturn = currentturn;

    // Saving Chance Card
    savegame.card = card;
    memcpy(savegame.deckCard, deckCard, sizeof(deckCard));

    // Saving Property
    for(int loop=0; loop<32; loop++) {
        savegame.property[loop] = property[loop];
    }

    // Saving Map
    memcpy(savegame.map, map, sizeof(map));

    fwrite(&savegame,sizeof(SAVEDATA),1,savefile);
    
    fclose(savefile);
}

// modul untuk meload game
void LoadGame(){
	FILE *savefile;
	savefile = fopen("savegame.dat","r");
	SAVEDATA savegame;
	
	if(savefile==NULL) {
		fprintf(stderr,"Failed to open file");
		exit(1);
	}
	
	fread(&savegame,sizeof(SAVEDATA),1,savefile);
    totalplayer = savegame.totalplayer;
    player = (PPLAYER*) realloc(player, sizeof(PPLAYER)*totalplayer);
    turn = (int*) realloc(turn, sizeof(int)*totalplayer);

    for(int i=0; i<totalplayer; i++){
        player[i] = savegame.player[i];
        turn[i] = savegame.turn[i];
    }
    
    currentturn = savegame.currentturn;
    card = savegame.card;
    memcpy(deckCard, &savegame.deckCard, sizeof(savegame.deckCard));
    memcpy(property, &savegame.property, sizeof(savegame.property));
    memcpy(map, &savegame.map, sizeof(savegame.map));


	fclose(savefile);
	
}

void InputName(){
    echo();
    //mvwgetnstr(stdscr, winner.name, 30);
    mvaddstr(21, 0, "Masukkan Nama : ");
    mvwgetnstr(stdscr, 21, 16, winner.name, 30);
}


// save score
void SaveScore(SAVESCORE hs) {
    FILE *fs1, *fs2;
	int i,j;
    SAVESCORE savescore1; // Menampung struct score pada file highscore.dat
    SAVESCORE savescore2; // Struct Score yang akan ditambah
    SAVESCORE sortscore[12]; /// Menampung struct score pada file dan yang akan ditambah untuk di sorting

    //char winnername[32] = "Player";
    strcpy(savescore2.name, hs.name);
    savescore2.score = hs.score;

    fs1 = fopen("highscore.dat","r+");
	fs2 = fopen("copyscore.dat","a+");
    
    if(fs1==NULL) {
        // show error message "system error while saving"
    }

    i = 0;
    while(fread(&savescore1,sizeof(SAVESCORE),1,fs1)) {
		sortscore[i] = savescore1;
        i++;
	}

    sortscore[10] = savescore2;

    for(i=0; i<10; i++) {
        int max = i;
        for(j=i+1; j<11; j++) {
            if(sortscore[max].score < sortscore[j].score) {
                max = j;
            }
        }
        if(max != i) {
            sortscore[11] = sortscore[i];
            sortscore[i] = sortscore[max];
            sortscore[max] = sortscore[11];
        }
    }

    for(i=0; i<10; i++) {
        fwrite(&sortscore[i],sizeof(SAVESCORE),1,fs2);
    }

    fclose(fs1);
    fclose(fs2);

    remove("highscore.dat");
    rename("copyscore.dat","highscore.dat");
}