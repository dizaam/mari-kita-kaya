#include "system.h"

/*
Daftar Kartu Kesempatan:
1. Melaju ke START
2. Kartu Bebas Penjara
3. Kartu Bebas Penjara
4. Mundur 3 Langkah
5. Maju 3 Langkah
6. Masuk Penjara
7. Melaju ke Tangkuban Perahu
8. Kembali ke Antapani
9. Melaju ke Bebas Parkir
10. Semua Pemain Membayar Uang ke Bank
11. Anda Mendapat Hadiah Ulang Tahun dari Teman -> income ( 50 )
12. Tidak Memakai Masker, Denda -> outcome ( 100 )
13. Mendapat Beasiswa -> income ( 150 )
14. Bayar Kartu 100 atau Ambil Kartu Kesempatan
15. Mendapat Warisan Sebesar 200 -> income ( 200 )
16. Bayar SWAB Test -> outcome ( 100 )
17. Menerima Bunga dari Bank -> income ( 100 )
18. Anda Menabrak Mobil Orang, Bayar Ganti Rugi -> outcome ( â€¦ )
19. Anda Mendapat Undian -> income ( â€¦ )
20. Anda Menjadi Calon Camat, Bayar ke Setiap Pemain -> outcome ( â€¦ )
*/

CCARD card;

int deckCard[DECKSIZE];

int rrandom(int low, int high) {
    int diff, val;
 
    diff = high - low;
    if (diff == 0) {
        return low;
    }
 
    val = rand() % diff;
    return val + low;
}
 
void initCard() {
    int i;
    for (i = 0; i < DECKSIZE; i++) {
        deckCard[i] = i + 1;
    }

    card.position = 0;
    shuffleCard();
}
 
void writeCard() {
    int i;

    for (i = 0; i < DECKSIZE; ++i) {
        printf(", %d", deckCard[i]);
    }
}
 
void shuffleCard() {
    int passes = 10;
    int n, cutSize, mp, op, tp, i;
    int *otherHand, *temp;
 
    otherHand = (int *)malloc(DECKSIZE * sizeof(int));
    temp = (int *)malloc(DECKSIZE * sizeof(int));
 
    for (n = 0; n < passes; ++n) {
        mp = 0;
        op = 0;
        tp = 0;
 
        while (mp < DECKSIZE) {
            cutSize = rrandom(0, DECKSIZE / 5) + 1;
 
            for (i = 0; i < cutSize && mp < DECKSIZE; ++i) {
                temp[tp++] = deckCard[mp++];
            }
 
            if (rrandom(0, 10) >= 1) {
                for (i = op - 1; i >= 0; --i) {
                    otherHand[i + tp] = otherHand[i];
                }
 
                memcpy(otherHand, temp, tp * sizeof(int));
                op += tp;
                tp = 0;
            } else {
                for (i = 0; i < tp; ++i, ++op) {
                    otherHand[op] = temp[i];
                }
                tp = 0;
            }
        }
 
        memcpy(deckCard, otherHand, DECKSIZE * sizeof(int));
    }
 
    free(otherHand);
    free(temp);
}

int getCardPosition() {
    return card.position;
}

int getCard() {
    int returnCard;
    if(card.position > 19) {
        card.position = 0;
        returnCard = deckCard[card.position];
    } else {
        returnCard = deckCard[card.position];
    }

    card.position++;
    return returnCard;
}

void CardAction() {
    // Card Action Here
    switch(getCard()){
        case 0:
            // kartu ke-0
            // melaju ke start
            ShowCardInfo("Menuju Ke Start");
            MovePlayer("moveto", 0);
            UpdateBoardInfo();
            Action();
            
            break;
        case 1:
            // kartu ke-1
            // Kartu Bebas Penjara
            ShowCardInfo("Mendapat Kartu Bebas Penjara");
            player[currentplayer].jailcard = true;
            
            break;
        case 2:
            // kartu ke-2
            // Kartu Bebas Penjara
            ShowCardInfo("Mendapat Kartu Bebas Penjara");
            player[currentplayer].jailcard = true;
            
            break;
        case 3:
            // kartu ke-3
            // Mundur 3 Langkah
            ShowCardInfo("Mundur 3 Langkah");
            MovePlayer("goto",-3);
            UpdateBoardInfo();
            Action();
            
            break;
        case 4:
            // kartu ke-4
            // Maju 3 Langkah
            ShowCardInfo("Maju 3 Langkah");
            MovePlayer("goto",3);
            UpdateBoardInfo();
            Action();
            
            break;
        case 5:
            // kartu ke-5
            // Masuk Penjara
            ShowCardInfo("Anda Tersangka Korupsi, Masuk Penjara");
            MovePlayer("moveto", 8);
            player[currentplayer].isjailed = true;
            
            break;
        case 6:
            // kartu ke-6
            // Melaju ke Tangkuban Perahu
            ShowCardInfo("Menuju Ke Tangkuban Perahu");
            MovePlayer("moveto",4);
            UpdateBoardInfo();
            Action();
            
            break;
        case 7:
            // kartu ke-7
            // Kembali ke Antapani
            ShowCardInfo("Menuju Ke Antapani");
            MovePlayer("moveto",21);
            UpdateBoardInfo();
            Action();
            
            break;
        case 8:
            // kartu ke-8
            // Melaju ke Bebas Parkir
            ShowCardInfo("Menuju Ke Bebas Parkir");
            MovePlayer("moveto",16);
            
            break;
        case 9:
            // kartu ke-9
            // Pemain Membayar Utang ke Bank ( outcome $50 )
            ShowCardInfo("Membayar Hutang Ke Bank $200");
            
            if(player[currentplayer].money < 200){
                // player kekurangan uang
                ShowCardNeedMoney();
                playerchoose = 0;

                DrawActionNeedMoney();
                
                ActionNeedMoney(playerchoose, 200);
                
            }else{

                // player tidak kekurangan uang
                cardUpdateMoney("outcome", 200);

            }
            
            
            break;
        case 10:
            // kartu ke-10
            // Anda Mendapat Hadiah Ulang Tahun -> income ( 50 )
            ShowCardInfo("Mendapat Hadiah Ulang Tahun Sebesar $50");
            cardUpdateMoney("income", 50);
            
            break;
        case 11:
            // kartu ke-11
            // Tidak Memakai Masker, Denda -> outcome ( 100 )
            ShowCardInfo("Denda $100 Karena Tidak Memakai Masker");
            cardUpdateMoney("outcome", 100);

            if(player[currentplayer].money < 100){
                // player kekurangan uang
                ShowCardNeedMoney();
                playerchoose = 0;

                DrawActionNeedMoney();
                
                ActionNeedMoney(playerchoose, 100);
                
            }else{

                // player tidak kekurangan uang
                cardUpdateMoney("outcome", 100);

            }
            
            break;
        case 12:
            // kartu ke-12
            // Mendapat Beasiswa -> income ( 150 )
            ShowCardInfo("Mendapat Beasiswa Sebesar $150");
            cardUpdateMoney("income", 150);
            
            break;
        case 13:
            // kartu ke-13
            // Bayar Kartu -> outcome ( 100 )
            ShowCardInfo("Bayar UKT Sebesar $100");
            cardUpdateMoney("outcome", 100);

            if(player[currentplayer].money < 100){
                // player kekurangan uang
                ShowCardNeedMoney();
                playerchoose = 0;

                DrawActionNeedMoney();
                
                ActionNeedMoney(playerchoose, 100);
                
            }else{

                // player tidak kekurangan uang
                cardUpdateMoney("outcome", 100);

            }
            
            break;
        case 14:
            // kartu ke-14
            // Mendapat Warisan Sebesar 200 -> income ( 200 )
            ShowCardInfo("Mendapat Warisan Sebesar $200");
            cardUpdateMoney("income", 200);
            
            break;
        case 15:
            // kartu ke-15
            // Bayar SWAB Test -> outcome ( 100 )
            ShowCardInfo("Bayar SWAB Test Sebesar $100");
            cardUpdateMoney("outcome", 100);

            if(player[currentplayer].money < 100){
                // player kekurangan uang
                ShowCardNeedMoney();
                playerchoose = 0;

                DrawActionNeedMoney();
                
                ActionNeedMoney(playerchoose, 100);
                
            }else{

                // player tidak kekurangan uang
                cardUpdateMoney("outcome", 100);

            }
            
            break;
        case 16:
            // kartu ke-16
            // Menerima Bunga dari Bank -> income ( 100 )
            ShowCardInfo("Menang Giveaway $100 Dari Bank");
            cardUpdateMoney("income", 100);
            
            break;
        case 17:
            // kartu ke-17
            // Anda Menabrak Mobil Orang, Bayar Ganti Rugi -> outcome ( 150 )
            ShowCardInfo("Bayar Ganti Rugi $150");
            cardUpdateMoney("outcome", 150);

            if(player[currentplayer].money < 150){
                // player kekurangan uang
                ShowCardNeedMoney();
                playerchoose = 0;

                DrawActionNeedMoney();
                
                ActionNeedMoney(playerchoose, 150);
                
            }else{

                // player tidak kekurangan uang
                cardUpdateMoney("outcome", 150);

            }
            
            break;
        case 18:
            // kartu ke-18
            // Anda Mendapat Undian -> income ( 200 )
            ShowCardInfo("Mendapat Undian Lotere $200");
            cardUpdateMoney("income", 200);
            
            break;
        case 19:
            // kartu ke-19
            // Anda Menjadi Calon Camat, Bayar ke KPU -> outcome ( 150 )
            ShowCardInfo("Bayar Setiap Pemain $50");
            cardUpdateMoney("outcome", 150);

            if(player[currentplayer].money < 150){
                // player kekurangan uang
                ShowCardNeedMoney();
                playerchoose = 0;

                DrawActionNeedMoney();

                ActionNeedMoney(playerchoose, 150);
                
            }else{
                // player tidak kekurangan uang
                cardUpdateMoney("outcome", 150);
                for(int i=0; i<totalplayer; i++){
                    if(i != currentplayer){
                        player[i].money += 50;
                    }
                }
            }
            break;
        default:
            break;
    }
}

void cardUpdateMoney(char* type, int money) {
    // Proccess of updating money for player
    if(!strcmp(type, "income")) {
        player[currentplayer].money += money;
    } else if(!strcmp(type, "outcome")) {
        player[currentplayer].money -= money;
    }
}

void ShowCardInfo(char* text){
    touchwin(wpinfo);

    mvwaddstr(wpinfo, 15, 0, text);

    wrefresh(wpinfo);
}

void ShowCardNeedMoney(){
    touchwin(wpinfo);

    mvwaddstr(wpinfo, 16, 0, "Uang Tidak Cukup");
    mvwaddstr(wpinfo, 17, 0, "Jual Property Atau Bangkrut");

    wrefresh(wpinfo);
}