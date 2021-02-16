#include "allheader.h"

BBOT bot;

char actionlistbotlevel[3][10] = {
    "Mudah",
    "Sedang",
    "Sulit",
};

int randNum(int lower, int upper) { 
    srand(time(0));
    int num = (rand() % (upper - lower + 1)) + lower; 

    return num;
}

void DrawActionListBotLevel(int* highlight){
    if(*highlight > 4){
        *highlight = 4;
    }else if(*highlight < 2){
        *highlight = 2;
    }

    for(int i=2; i<5; i++){
        if(i==*highlight){
            attrset(A_REVERSE);
        }
        mvaddstr(i, 2, actionlistbotlevel[i-2]);
        attroff(A_REVERSE);
    }
}

void DrawActionBotLevel() {
    int keyp = 0;
    int highlight = 0;

    DrawActionListBotLevel(&highlight);
    noecho();
    do{
        keyp = getch();

        switch(keyp){
            case KEY_UP:
                highlight--;
                DrawActionListBotLevel(&highlight);
                playerchoose = highlight;
                break;
            case KEY_DOWN:
                highlight++;
                DrawActionListBotLevel(&highlight);
                playerchoose = highlight;
                break;
        }
        refresh();
    }while(keyp != '\n');
}

void SetupBot() {
    clear();
    addstr("PILIH TINGKAT KESULITAN BOT\n");

    DrawActionBotLevel();
    if(playerchoose == 0 ) {
        bot.level = 0;
    } else if(playerchoose == 0 ) {
        bot.level = 1;
    } else {
        bot.level = 2;
    }
}

void BotLeaveJail() {
    if(player[currentplayer].jailcard) {
        // Jika punya kartu penjara
        playerchoose = 1;
    } else {
        // Jika tidak punya kartu bebas penjara
        if(bot.level == 0) {
            // BOT memilih menyogok
            playerchoose = 2;
        } else if(bot.level == 1) {
            // BOT lempar dadu satu kali kemudian menyogok
            if(player[currentplayer].jailcount == 1) {
                playerchoose = 2;
            } else {
                playerchoose = 0;
            }
        } else if(bot.level == 2) {
            // BOT memilih lempar dadu
            playerchoose = 0;
        }
    }
}

void BotVisitTourism() {
    if(bot.level == 0) {
        // tidak beli
        playerchoose = 1;
    } else if(bot.level == 1) {
        // BOT membeli tempat wisata secara random (1:1)
        int botMedium[2] = {0,1};
        playerchoose = botMedium[randNum(1,2)-1];
    } else if(bot.level == 2) {
        // BOT selalu membeli tempat wisata
        playerchoose = 0;
    }
}

void BotVisitProperty() {
    if(bot.level == 0) {
        // BOT membeli properti secara random (1:4)
        int botEasy[5] = {1,1,1,0,1};
        playerchoose = botEasy[randNum(1,5)-1];
    } else if(bot.level == 1) {
        // BOT membeli properti secara random (1:2)
        int botMedium[3] = {1,0,1};
        playerchoose = botMedium[randNum(1,3)-1];
    } else if(bot.level == 2) {
        if(player[currentplayer].position > 12 && player[currentplayer].position < 24) {
            // BOT selalu membeli properti yang diantara petak 12 s.d. 24
            playerchoose = 0;
        } else if(player[currentplayer].position == 29 || player[currentplayer].position == 31) {
            // BOT selalu membeli petak 29 dan 31
            playerchoose = 0;
        } else {
            // BOT membeli properti secara random (1:1)
            int botHard[2] = {0,1};
            playerchoose = botHard[randNum(1,2)-1];
        }
    }
}

void BotUpgrade() {
    if(bot.level == 0) {
        // BOT tidak pernah upgrade property
        playerchoose = 1;
    } else if(bot.level == 1) {
        // BOT upgrade property sampai level 2
        if(property[player[currentplayer].position].level < 2) {
            playerchoose = 0;
        } else {
            playerchoose = 1;
        }
    } else if(bot.level == 2) {
        // BOT upgrade property sampai level maks
        if(property[player[currentplayer].position].level != 4) {
            playerchoose = 0;
        } else {
            playerchoose = 1;
        }
    }
}

void BotNeedMoney() {
    if(bot.level == 0) {
        // BOT memilih bangkrut daripada menjual properti
        playerchoose = 0;
    } else if(bot.level == 1) {
        // BOT menjual properti terlebih dahulu
        playerchoose = 1;
    } else if(bot.level == 2) {
        // BOT menjual properti terlebih dahulu
        playerchoose = 1;
    }
}