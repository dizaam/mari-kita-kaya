#include "system.h"

int menuchoose;

char logo[8][69]= {
    "___  ___           _    _   ___ _           _   __                  ",        
    "|  \\/  |          (_)  | | / (_) |         | | / /                  ",
    "| .  . | __ _ _ __ _   | |/ / _| |_ __ _   | |/ /  __ _ _   _  __ _ ",
    "| |\\/| |/ _` | '__| |  |    \\| | __/ _` |  |    \\ / _` | | | |/ _` |",
    "| |  | | (_| | |  | |  | |\\  \\ | || (_| |  | |\\  \\ (_| | |_| | (_| |",
    "\\_|  |_/\\__,_|_|  |_|  \\_| \\_/_|\\__\\__,_|  \\_| \\_/\\__,_|\\__, |\\__,_|",
    "                                                         __/ |      ",
    "                                                        |___/       ",
};

char menu[4][11] = {
    {"New Game"},
    {"Load Game"},
    {"Highscores"},
    {"Exit"},
};

// modul untuk memprint teks di tengah
void PrintCenter(int row, char* text){
    int len, indent, x;
    getmaxyx(stdscr, indent, x);

    // menentukan titik tengah
    len  = strlen(text);
    indent = x - len;
    indent /= 2;

    mvaddstr(row+1, indent, text);
    addstr("\n");
}

// modul untuk menampilkan logo
void DrawLogo(){
    for(int i=0; i<8; i++){
        PrintCenter(2+i,logo[i]);
    }
    addstr("\n\n");
}

// modul untuk menampilkan main menu
void DrawMenu(int* highlight){
    // check jika keluar batas menu
    if (*highlight<0){
        *highlight = 0;
    }else if (*highlight>3){
        *highlight = 3;
    }

    // menghighlight menu dipilih
    for(int cnt = 0; cnt < 4; cnt++){
        if (cnt==*highlight){
            attrset(A_REVERSE);
        }
        PrintCenter(15+(cnt*2), menu[cnt]);
        attroff(A_REVERSE);
    }
    PrintCenter(24, "Use Arrow Key To Move...");
    refresh();
}

// menampilkan main menu
void MainMenu(){
    int highlight = 0;
    int choose = 0;

    DrawLogo();

    DrawMenu(&highlight);

    // mengaktifkan routine keypad input
    keypad(stdscr, true);
    noecho();

    // menunggu keypad input
    do{
        choose = getch();
        switch(choose){
            case KEY_UP:
                highlight--;
                DrawMenu(&highlight);
                menuchoose = highlight;
                break;

            case KEY_DOWN:
                highlight++;
                DrawMenu(&highlight);
                menuchoose = highlight;
                break;

            default :
                break;
        }
    }while(choose != '\n');
    echo();
}

