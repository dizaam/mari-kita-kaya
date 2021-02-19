#include "allheader.h"

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

char logodefaultwin[6][62]={
" _   _  _____  _____  _____  _____ ______ __   __    _  _  _ ",
"| | | ||_   _|/  __ \\|_   _||  _  || ___ \\\\ \\ / /   | || || |",
"| | | |  | |  | /  \\/  | |  | | | || |_/ / \\ V /    | || || |",
"| | | |  | |  | |      | |  | | | ||    /   \\ /     | || || |",
"\\ \\_/ / _| |_ | \\__/\\  | |  \\ \\_/ /| |\\ \\   | |     |_||_||_|",
" \\___/  \\___/  \\____/  \\_/   \\___/ \\_| \\_|  \\_/     (_)(_)(_)",                                                                                                                         
};

char logolinewin[6][93]={
" _      _____  _   _  _____     _   _  _____  _____  _____  _____ ______ __   __    _  _  _ ",
"| |    |_   _|| \\ | ||  ___|   | | | ||_   _|/  __ \\|_   _||  _  || ___ \\\\ \\ / /   | || || |",
"| |      | |  |  \\| || |__     | | | |  | |  | /  \\/  | |  | | | || |_/ / \\ V /    | || || |",
"| |      | |  | . ` ||  __|    | | | |  | |  | |      | |  | | | ||    /   \\ /     | || || |",
"| |____ _| |_ | |\\  || |___    \\ \\_/ / _| |_ | \\__/\\  | |  \\ \\_/ /| |\\ \\   | |     |_||_||_|",
"\\_____/ \\___/ \\_| \\_/\\____/     \\___/  \\___/  \\____/  \\_/   \\___/ \\_| \\_|  \\_/     (_)(_)(_)",                                                                                                                                                                                    
};

char logotourismwin[6][115]={
" _____  _____  _   _ ______  _____  _____ ___  ___    _   _  _____  _____  _____  _____ ______ __   __    _  _  _ ",
"|_   _||  _  || | | || ___ \\|_   _|/  ___||  \\/  |   | | | ||_   _|/  __ \\|_   _||  _  || ___ \\\\ \\ / /   | || || |",
"  | |  | | | || | | || |_/ /  | |  \\ `--. | .  . |   | | | |  | |  | /  \\/  | |  | | | || |_/ / \\ V /    | || || |",
"  | |  | | | || | | ||    /   | |   `--. \\| |\\/| |   | | | |  | |  | |      | |  | | | ||    /   \\ /     | || || |",
"  | |  \\ \\_/ /| |_| || |\\ \\  _| |_ /\\__/ /| |  | |   \\ \\_/ / _| |_ | \\__/\\  | |  \\ \\_/ /| |\\ \\   | |     |_||_||_|",
"  \\_/   \\___/  \\___/ \\_| \\_| \\___/ \\____/ \\_|  |_/    \\___/  \\___/  \\____/  \\_/   \\___/ \\_| \\_|  \\_/     (_)(_)(_)",                                                                                                                                                                                                                            
};

char menu[6][11] = {
    {"New Game"},
    {"Load Game"},
    {"Highscores"},
    {"Help"},
    {"Credits"},
    {"Exit"},
};

// modul untuk memprint teks di tengah
void PrintCenter(WINDOW* win, int row, char* text){
    touchwin(win);
    int len, indent, x;
    getmaxyx(win, indent, x);

    // menentukan titik tengah
    len  = strlen(text);
    indent = x - len;
    indent /= 2;

    mvwprintw(win, row+1, indent, text);
    //mvaddstr(row+1, indent, text);
    addstr("\n");
    wrefresh(win);
}

// modul untuk menampilkan logo judul permainan
void DrawLogo(){
    for(int i=0; i<8; i++){
        PrintCenter(stdscr, 2+i,logo[i]);
    }
    addstr("\n\n");
}

// modul untuk menampilkan main menu
void DrawMenu(int* highlight){
    // check jika keluar batas menu
    if (*highlight<0){
        *highlight = 0;
    }else if (*highlight>5){
        *highlight = 5;
    }

    // menghighlight menu dipilih
    for(int cnt = 0; cnt < 6; cnt++){
        if (cnt==*highlight){
            attrset(A_REVERSE);
        }
        PrintCenter(stdscr, 15+(cnt*2), menu[cnt]);
        attroff(A_REVERSE);
    }
    PrintCenter(stdscr, 28, "Use Arrow Key To Move...");
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
    menuchoose = 0;
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
    mvprintw(20, 0, "menu choose: %d", menuchoose);
    echo();
}


// modul untuk menampilkan logo default win
void DrawLogoDefaultWin(){
    for(int i=0; i<6; i++){
        PrintCenter(stdscr, 2+i,logodefaultwin[i]);
    }
    addstr("\n\n");
}

// modul untuk menampilkan logo line win
void DrawLogoLineWin(){
    for(int i=0; i<6; i++){
        PrintCenter(stdscr, 2+i,logolinewin[i]);
    }
    addstr("\n");
    PrintCenter(stdscr, 10, "Score x3 !");
}

// modul untuk menampilkan logo tourism win
void DrawLogoTourismWin(){
    for(int i=0; i<6; i++){
        PrintCenter(stdscr, 2+i,logotourismwin[i]);
    }
    addstr("\n");
    PrintCenter(stdscr, 10, "Score x5 !");
}

// menampilkan highscore
void HighScore() {
    clear();
    FILE *fp;
	fp = fopen("highscore.dat","r");
	
	SAVESCORE s1;
	
	if(fp==NULL) {
		// error open file
	}
	
	int rank = 1;
	printw("Rank\tNama\tScore\n");
	while(fread(&s1,sizeof(SAVESCORE),1,fp)) {
		printw("%d\t%s\t%d\n",rank,s1.name,s1.score);
		rank++;
	}
	
	fclose(fp);

    printw("ketik apa saja untuk kembali...");
    getch();
    clear();
}

// menu help
void Help(){
    clear();
    FILE *fp; 
  
    char c; 
  
    // membuka file 
    fp = fopen("help.txt", "r"); 
    if (fp == NULL) {
        mvprintw(0,0, "Selamat datang di mari kita kaya!");
        mvprintw(1,0, "Gunakan tombol arrow pada keyboard untuk navigasi");
        mvprintw(2,0, "Peraturan sama seperti monopoli klasik");
        mvprintw(3,0, "Akan tetapi ada rules tambahan, seperti:");
        mvprintw(5,0, "1. Ada tambahan 2 kondisi menang");
        mvprintw(6,0, "2. Meski hanya memiliki 1 block property, bisa diupgrade");
    } 
  
    // membaca isi teks
    c = fgetc(fp); 
    while (c != EOF) { 
        printw("%c", c);
        c = fgetc(fp); 
    } 
  
    fclose(fp); 

    getch();
}

// menu credits
void Credits(){
    clear();
    DrawLogo();
    
    PrintCenter(stdscr, 18, "Copyright(c) 2021 Mari Kita Kaya.");
    PrintCenter(stdscr, 19, "All rights reserved.");

    PrintCenter(stdscr, 22, "--- Author ---");
    PrintCenter(stdscr, 23, "Luthfi Maajid (201524050)");
    PrintCenter(stdscr, 24, "Sobri Waskito Aji (201524060)");

    PrintCenter(stdscr, 26, "JTK Polban 2020");
    PrintCenter(stdscr, 27, "D-IV Teknik Informatika");

    PrintCenter(stdscr, 31, "--- Supported by ---");
    PrintCenter(stdscr, 32, "Dosen DDP Praktek Polban");
    PrintCenter(stdscr, 33, "Ani Rahmani");
    PrintCenter(stdscr, 34, "Asri Maspupah");
    PrintCenter(stdscr, 35, "Lukmannul Hakim");
    getch();
}

// menu keluar permainan
void Exit(){
    clear();
    PrintCenter(stdscr, 10, "Terima Kasih Telah Bermain");
    PrintCenter(stdscr, 11, "Sampai Ketemu Lagi...");
    FreeAll();
    refresh();
    getch();
    endwin();
}