#include "system.h"

WINDOW*  waction, *wpinfo, *wbinfo;

char actionlist[5][30] = {
    "Roll Dadu",
    "Beli Properti",
    "Akhiri Giliran",
    "Test",
    "Test",
};

// modul untuk menginisialisasi window
void InitWindow(){
    wmap = newwin(37,92,0,0);
    waction = newwin(7,91,37,0);
    wpinfo = newwin(25, 40, 0, 92);
    wbinfo = newwin(19, 40, 25, 92);
}


// modul untuk mensortir giliran
int* shakeTurn(int temp[totalplayer][2]){
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
        
        resetDadu(&dd);
        shakeDadu(&dd);
        
        temp[i][0] = dd.totaldd;
        resetDadu(&dd);
        temp[i][1] = i;
        printw("\nDadu yg didapat: %d\n", temp[i][0]);
    }

    printw("\n");
    turn = shakeTurn(temp);

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
    
    InitPlayer(player, totalplayer);

    TurnSetup();
}

// modul untuk menampilkan box pilihan
void DrawActionBox(){
    wclear(waction);
    touchwin(waction);

    wattrset(waction, A_ALTCHARSET);
    box(waction, ACS_VLINE, ACS_HLINE);

    wattroff(waction, A_ALTCHARSET);
    wrefresh(waction);
}

// modul untuk menampilkan box informasi pemain
void DrawPlayerInfoBox(){
    wclear(wpinfo);
    touchwin(wpinfo);

    wattrset(wpinfo, A_ALTCHARSET);
    box(wpinfo, ACS_VLINE, ACS_HLINE);

    wattroff(wpinfo, A_ALTCHARSET);

    wrefresh(wpinfo);
}

// modul untuk menampilkan petak yang diinjak
void DrawBoardInfoBox(){
    wclear(wbinfo);
    touchwin(wbinfo);

    wattrset(wbinfo, A_ALTCHARSET);
    box(wbinfo, ACS_VLINE, ACS_HLINE);

    wattroff(wbinfo, A_ALTCHARSET);

    wrefresh(wbinfo);
}

// modul untuk shorthand memanggil 3 modul 
void DrawWidget(){
    DrawActionBox();

    DrawPlayerInfoBox();

    DrawBoardInfoBox();
}

void DrawActionList(int* highlight){
    if(*highlight > 4){
        *highlight = 4;
    }else if(*highlight < 0){
        *highlight = 0;
    }


    for(int i=0; i<5; i++){
        if(i==*highlight){
            wattrset(waction, A_REVERSE);
        }
        mvwaddstr(waction, 1 + i, 2, actionlist[i]);
        wattroff(waction, A_REVERSE);
    }

    wrefresh(waction);
}

void DrawAction(){
    touchwin(waction);

    int keyp = 0;
    int highlight = 0;
   
    keypad(waction, true);

    DrawActionList(&highlight);
    noecho();
    do{
        keyp = wgetch(waction);

        switch(keyp){
            case KEY_UP:
                highlight--;
                DrawActionList(&highlight);
                break;
            case KEY_DOWN:
                highlight++;
                DrawActionList(&highlight);
                break;
        }
        wrefresh(waction);
    }while(keyp != '\n');

    wrefresh(waction);
}

// modul untuk menampilkan tombol untuk mengocok dadu
void DrawActionRollDice(){
    touchwin(waction);
    int keyp = 0;

    wattrset(waction, A_REVERSE);
    mvwaddstr(waction, 1, 2, "Roll Dice");
    wattroff(waction, A_REVERSE);

    noecho();

    do{
        keyp = wgetch(waction);
    }while(keyp!='\n');

    mvwaddstr(waction, 1, 2, "                        ");
    wrefresh(waction);
}

void DrawActionEndTurn(){
    touchwin(waction);
    int keyp = 0;

    wattrset(waction, A_REVERSE);
    mvwaddstr(waction, 1, 2, "Akhiri Giliran");
    wattroff(waction, A_REVERSE);

    noecho();

    do{
        keyp = wgetch(waction);
    }while(keyp!='\n');

    mvwaddstr(waction, 1, 2, "                        ");
    wrefresh(waction);
}



void UpdatePlayerInfo(){
    touchwin(wpinfo);
    
    mvwprintw(wpinfo, 1,2,"Giliran Player %d", currentplayer+1);

    mvwprintw(wpinfo, 2,2,"Uang Player: %d", player[currentplayer].money);
    mvwprintw(wpinfo, 3,2,"Posisi Player: %d", player[currentplayer].position);
    
    mvwprintw(wpinfo, 4,2,"Silahkan Mengocok Dadu");

    
    wrefresh(wpinfo);

}

// modul untuk menampilkan dadu yang didapat
void DrawDiceResult(){
    touchwin(wpinfo);
    
    mvwprintw(wpinfo, 7,2,"Dadu 1: %d", dd.dadu1);
    mvwprintw(wpinfo, 8,2,"Dadu 2: %d", dd.dadu2);
    mvwprintw(wpinfo, 9,2,"Total: %d", dd.totaldd);
    
    wrefresh(wpinfo);

}

// modul untuk menampilkan gambar dadu yang dikocok
void DrawDiceSymbol(){
    // start from line 6
    touchwin(wpinfo);
    for(int i=0; i<10; i++){
        mvwaddstr(wpinfo, 6+i, 2, dicesymbol[dd.dadu1-1][i]);
    }

    for(int i=0; i<10; i++){
        mvwaddstr(wpinfo, 6+i, 12, dicesymbol[dd.dadu2-1][i]);
    }

    mvwprintw(wpinfo, 8,22,"= %d", dd.totaldd);

    mvwprintw(wpinfo, 12, 2, "Melaju %d Langkah", dd.totaldd);
    
    wrefresh(wpinfo);
}

// modul untuk mengupdate posisi pemain
void UpdatePosition(){
    touchwin(wpinfo);

    player[currentplayer].position += dd.totaldd;

    if(player[currentplayer].position > 31){
        player[currentplayer].position = player[currentplayer].position-32;
        player[currentplayer].money += 200;
    }

    wrefresh(wpinfo);
}

// modul untuk mengupdate petak yang diinjak
void UpdateBoardInfo(){
    touchwin(wbinfo);

    wgetch(wbinfo);

    mvwprintw(wbinfo, 1, 13, "Petak : %d", player[currentplayer].position);

    switch(board[player[currentplayer].position]){
        case 0:
            // masuk penjara
            mvwprintw(wbinfo, 2, 2, "Kamu Berada Di Persidangan");
            mvwprintw(wbinfo, 3, 2, "Kamu Terbukti Melanggar Hukum! Pergi ke Penjara");
            wgetch(wbinfo);

            player[currentplayer].position=8;
            player[currentplayer].isjailed=true;
            break;

        case 1:
            // player berada pada petak start
            mvwprintw(wbinfo, 2, 2, "Kamu Berada di Petak START");
            wgetch(wbinfo);
                    
            break;
                
        case 2:
            // player berada pada petak bebas parkir
            mvwprintw(wbinfo, 2, 2, "Bebas Parkir, Kamu Aman Disini");
            wgetch(wbinfo);

            break;
                
        case 3:
            // penjara hanya lewat
            mvwprintw(wbinfo, 2, 2, "Lapas Tempatnya Orang2 Melanggar Hukum");
            wgetch(wbinfo);

            break;
                
        case 4:
            // petak pajak, player membayar pajak
            mvwprintw(wbinfo, 2, 2, "Bayar Pajak Dong!");
            wgetch(wbinfo);

            break;

        case 5:
            // player mendapat kartu kesempatan
            mvwprintw(wbinfo, 2, 2, "Kamu Berada di Petak Property!");
            wgetch(wbinfo);

            break;
                
        case 6:
            // player berada pada petak properti
            mvwprintw(wbinfo, 2, 2, "Kamu Berada di Petak Property!");
            wgetch(wbinfo);

            break;
        }


    wrefresh(wbinfo);
}