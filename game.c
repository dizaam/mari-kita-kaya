#include "system.h"

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

char actionlistneedmoney[2][30] = {
    "Jual Properti",
    "Bangkrut",
};

int wintype = 0;

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
        printw("\nPLAYER %d SILAHKAN MENGOCOK DADU\n", i+1);
        printw("ketik apa saja untuk mengocok...");
        getch();
        
        resetDice();
        shakeDice();
        
        temp[i][0] = dice.totaldice;
        resetDice();
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
void SetupNewGame(){
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
    initCard();
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
        resetDice();
        currentplayer = turn[currentturn];

        if(player[currentplayer].isjailed){
        // jika pemain dipenjara
            refresh();
            DrawMap();
            DrawWidget();
            ShowPlayerInfo();

            playerchoose = 0;
            DrawActionJailed();

            if(playerchoose == 0){
            // player memilih mengocok dadu
                DrawActionRollDice();
                shakeDice();
                DrawDiceSymbol();
                if(dice.isdouble){
                    // dadu berhasil double
                    player[currentplayer].isjailed=false;
                    MovePlayer("goto", dice.totaldice);
                    UpdateBoardInfo();
                    Action();
                }
            }else if(playerchoose == 1){
            // player memilih menggunakan kartu bebas penjara
                ShowJailCardMessage();
                if(player[currentplayer].jailcard){
                    // mempunyai kartu bebas penjara
                    player[currentplayer].jailcard = false;
                    player[currentplayer].isjailed = false;

                    DrawActionRollDice();
                    shakeDice();
                    DrawDiceSymbol();
                    MovePlayer("goto", dice.totaldice);
                    UpdateBoardInfo();
                    Action();

                }
            }else if(playerchoose == 2){
            // player memilih menyogok petugas
                ShowPayJailMessage();
                if(player[currentplayer].money>=100){
                    // uang cukup
                    player[currentplayer].isjailed = false;
                    player[currentplayer].money -= 100;

                    DrawActionRollDice();
                    shakeDice();
                    DrawDiceSymbol();
                    MovePlayer("goto", dice.totaldice);
                    UpdateBoardInfo();
                    Action();
                }
            }

        }else{
        // pemain tidak dipenjara
            do{
                refresh();
                DrawWidget();
                ShowPlayerInfo();
                DrawActionRollDice();
                shakeDice();
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
                
                UpdateBoardInfo();
                Action();

                if(dice.isdouble){
                    ShowInfoDouble();
                    wgetch(wpinfo);
                }
            }while((dice.isdouble) && (!player[currentplayer].isjailed) && (!player[currentplayer].isbankrupt));
        }
        DrawActionEndTurn();


        if(isDefaultWin()){
            // default win
            clear();
            touchwin(stdscr);
            DrawLogoDefaultWin();
            ShowScore();
            refresh();
            getch();
            break;
        
        }else if(isTourismWin()){
            // tourism win
            clear();
            touchwin(stdscr);
            DrawLogoTourismWin();
            ShowScore();
            refresh();
            getch();
            break;
            
        }else if(isLineWin()){
            // line win
            clear();
            touchwin(stdscr);
            DrawLogoLineWin();
            ShowScore();
            refresh();
            getch();
            break;
            
        }else{
            // penggantian giliran
            do{
                currentturn++;
                if(currentturn==totalplayer){
                    currentturn=0;
                } 
            }while(player[turn[currentturn]].isbankrupt);    
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
            
            DrawActionPayTax();
            if(player[currentplayer].money < 100){
                // uang kurang
                ShowFailedTaxInfo();
                playerchoose = 0;
                DrawActionNeedMoney();
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

                DrawActionUnownedProperty();
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
                    DrawActionUpgradeProperty();
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
                DrawActionPayRent();
                if(player[currentplayer].money < rentprice){
                    // player kekurangan uang
                    ShowPayRentFailed();
                    playerchoose = 0;
                    DrawActionNeedMoney();
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
                DrawActionUnownedProperty();
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
                DrawActionPayRent();
                if(player[currentplayer].money < rentprice){
                    ShowPayRentFailed();
                    playerchoose = 0;

                    DrawActionNeedMoney();
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

// jailed message
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

// mengupdate box info player
void ShowPlayerInfo(){
    touchwin(wpinfo);
    
    char buff[10];
    sprintf(buff, "%s %d", "PLAYER", currentplayer+1);
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

// modul untuk menampilkan dadu yang didapat
void DrawDiceResult(){
    touchwin(wpinfo);
    
    mvwprintw(wpinfo, 8,1,"Dadu 2: %d", dice.dice2);
    mvwprintw(wpinfo, 7,1,"Dadu 1: %d", dice.dice1);
    mvwprintw(wpinfo, 9,1,"Total: %d", dice.totaldice);

    wrefresh(wpinfo);

}

// modul untuk menampilkan gambar dadu yang dikocok
void DrawDiceSymbol(){
    // start from line 6
    touchwin(wpinfo);
    for(int i=0; i<10; i++){
        mvwaddstr(wpinfo, 6+i, 1, dicesymbol[dice.dice1-1][i]);
    }

    for(int i=0; i<10; i++){
        mvwaddstr(wpinfo, 6+i, 11, dicesymbol[dice.dice2-1][i]);
    }

    mvwprintw(wpinfo, 8,21,"= %d", dice.totaldice);

    if((player[currentplayer].isjailed) && (!dice.isdouble)){
        mvwprintw(wpinfo, 12, 1, "Gagal Mendapat Double");
    }else if ((player[currentplayer].isjailed) && (dice.isdouble)){
        mvwprintw(wpinfo, 12, 1, "Double! Keluar Dari Penjara");
    }else{
        mvwprintw(wpinfo, 12, 1, "Melaju %d Langkah", dice.totaldice);
    }
    
    
    wrefresh(wpinfo);
}



// modul untuk mengupdate petak yang diinjak
void UpdateBoardInfo(){
    touchwin(wbinfo);
    wclear(wbinfo);

    wgetch(wbinfo);

    char petak[10];
    sprintf(petak, "%s %d", "PETAK", player[currentplayer].position);

    

    PrintCenter(wbinfo, -1, petak);

    switch(board[player[currentplayer].position]){
        case 0:
            // masuk penjara
            mvwprintw(wbinfo, 2, 1, "Kamu Berada Di Persidangan");
            mvwprintw(wbinfo, 3, 1, "Kamu Terbukti Melanggar Hukum! Pergi ke Penjara");
            wgetch(wbinfo);
            break;

        case 1:
            // player berada pada petak start
            mvwprintw(wbinfo, 2, 1, "START");
           
            wgetch(wbinfo);      
            break;
                
        case 2:
            // player berada pada petak bebas parkir
            mvwprintw(wbinfo, 2, 1, "Bebas Parkir");
          
            wgetch(wbinfo);
            break;
                
        case 3:
            // penjara hanya lewat
            mvwprintw(wbinfo, 2, 1, "Hanya Lewat");
         
            wgetch(wbinfo);
            break;
                
        case 4:
            // petak pajak, player membayar pajak
            mvwprintw(wbinfo, 2, 1, "Kantor Pajak");
         
            wgetch(wbinfo);
            break;

        case 5:
            // player mendapat kartu kesempatan
            mvwprintw(wbinfo, 2, 1, "Kartu Kesempatan");
           
            wgetch(wbinfo);
            break;
                
        case 6:
            // player berada pada petak properti

            PrintCenter(wbinfo, 1, property[player[currentplayer].position].name);
            ShowPropertyInfo();

          
            wgetch(wbinfo);
            break;

        case 7:
            // player berada pada petak pariwisata
            PrintCenter(wbinfo, 1, property[player[currentplayer].position].name);
            ShowTourismInfo();

            wgetch(wbinfo);
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

    for(int i=0; i<totalplayer; i++){
        if(player[i].linecount[0]==6){
            ret = true;
        }else if(player[i].linecount[1]==5){
            ret = true;
        }else if(player[i].linecount[2]==6){
            ret = true;
        }else if(player[i].linecount[3]==5){
            ret = true;
        }
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

    int asset = getAsset(currentplayer);
    int score = getScore(wintype, asset);

    sprintf(playertext,"Player %d Menang !", playerwinner+1);
    sprintf(moneytext, "Total Uang  : %d", player[currentplayer].money);
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