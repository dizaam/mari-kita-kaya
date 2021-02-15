#include "allheader.h"

DDICE dice;

char dicesymbol[10][10][10] = {
    {
        "!-------@",
        "|       |",
        "|   O   |",
        "|       |",
        "#-------$",
    },
    {
        "!-------@",
        "|    O  |",
        "|       |",
        "|  O    |",
        "#-------$",
    },
    {
        "!-------@",
        "|    O  |",
        "|   O   |",
        "|  O    |",
        "#-------$",
    },
    {
        "!-------@",
        "|  O O  |",
        "|       |",
        "|  O O  |",
        "#-------$",
    },
    {
        "!-------@",
        "|  O O  |",
        "|   O   |",
        "|  O O  |",
        "#-------$",
    },
    {
        "!-------@",
        "|  O O  |",
        "|  O O  |",
        "|  O O  |",
        "#-------$",
    },
};

void resetDice(){
    dice.totaldice = 0;
    dice.dice1 = 0;
    dice.dice2 = 0;
    dice.countdouble = 0;
    dice.isdouble = false;
}

void shakeDice(){
    srand(time(NULL));
    dice.isdouble = false;
    dice.totaldice = 0;

    dice.dice2 = rand() % 6 + 1;
    dice.dice1 = rand() % 6 + 1;

    dice.totaldice = dice.dice1 + dice.dice2;

    if(dice.dice1==dice.dice2){
        dice.isdouble = true;
        dice.countdouble++;
    }
}

// modul untuk menampilkan gambar dadu yang dikocok
void DrawDiceSymbol(){
    // start from line 6
    touchwin(wpinfo);
    for(int i=0; i<5; i++){
        for(int j=0; j<9; j++){
            switch(dicesymbol[dice.dice1-1][i][j]){
                case '!':
                    mvwaddch(wpinfo, 6+i, 1+j, ACS_ULCORNER);
                    break;
                case '@':
                    mvwaddch(wpinfo, 6+i, 1+j, ACS_URCORNER);
                    break;
                case '#':
                    mvwaddch(wpinfo, 6+i, 1+j, ACS_LLCORNER);
                    break;
                case '$':
                    mvwaddch(wpinfo, 6+i, 1+j, ACS_LRCORNER);
                    break;
                case '|':
                    mvwaddch(wpinfo, 6+i, 1+j, ACS_VLINE);
                    break;
                case '-':
                    mvwaddch(wpinfo, 6+i, 1+j, ACS_HLINE);
                    break;
                default:
                    mvwaddch(wpinfo, 6+i, 1+j, dicesymbol[dice.dice1-1][i][j]);
                    break;
            }
        }
        //mvwaddstr(wpinfo, 6+i, 1, dicesymbol[dice.dice1-1][i]);
    }

    for(int i=0; i<5; i++){
        for(int j=0; j<9; j++){
            switch(dicesymbol[dice.dice2-1][i][j]){
                case '!':
                    mvwaddch(wpinfo, 6+i, 11+j, ACS_ULCORNER);
                    break;
                case '@':
                    mvwaddch(wpinfo, 6+i, 11+j, ACS_URCORNER);
                    break;
                case '#':
                    mvwaddch(wpinfo, 6+i, 11+j, ACS_LLCORNER);
                    break;
                case '$':
                    mvwaddch(wpinfo, 6+i, 11+j, ACS_LRCORNER);
                    break;
                case '|':
                    mvwaddch(wpinfo, 6+i, 11+j, ACS_VLINE);
                    break;
                case '-':
                    mvwaddch(wpinfo, 6+i, 11+j, ACS_HLINE);
                    break;
                default:
                    mvwaddch(wpinfo, 6+i, 11+j, dicesymbol[dice.dice2-1][i][j]);
                    break;
            }
        }
        //mvwaddstr(wpinfo, 6+i, 11, dicesymbol[dice.dice2-1][i]);
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