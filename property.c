#include "allheader.h"

PPROPERTY property[32] = {
    /*
        nama tempat, pemilik, level, harga sesuai level, harga upgrade, line/baris mana
    */

    {{"0"}, -1, 0, {0,0,0,0,0},0, 0},                                      // Start
    {{"Cidadap"}, -1, 0, {20, 30, 40, 50, 60}, 20, 0},   
    {{"0"}, -1, 0, {0,0,0,0,0},0, 0},                                      // Kartu Kesempatan
    {{"Gedebage"}, -1, 0, {20, 35, 45, 55, 65}, 20, 0},
    {{"Gunung Tangkubang Perahu"}, -1, 0, {50, 100, 200, 200, 200},0, 0},      // tempat wisata 1
    {{"Cibiru"}, -1, 0, {45, 60, 75, 90, 105}, 30, 0},
    {{"Bojongloa"}, -1, 0, {50, 65, 80, 95, 110}, 30, 0},
    {{"Buahbatu"}, -1, 0, {55, 70, 85, 100, 115}, 30, 0},
    {{"0"}, -1, 0, {0,0,0,0,0},0, 1},                                      // Penjara
    {{"0"}, -1, 0, {0,0,0,0,0},0, 1},                                      // Kantor Pajak
    {{"Cicendo"}, -1, 0, {70, 95, 120, 145, 170}, 50, 1},
    {{"Arcamanik"}, -1, 0, {75, 100, 125, 150, 175}, 50, 1},
    {{"0"}, -1, 0, {0,0,0,0,0},0, 1},                                      // Kartu Kesempatan
    {{"Lengkong"}, -1, 0, {95, 125, 155, 185, 215}, 60, 1},
    {{"Trans Studio Mall"}, -1, 0, {50, 100, 200, 200, 200},0, 1},             // tempat wisata 2
    {{"Regol"}, -1, 0, {100, 130, 160, 190, 220}, 60, 1},
    {{"0"}, -1, 0, {0,0,0,0,0},0, 2},                                      // Free Parking
    {{"Cibeunying"}, -1, 0, {120, 155, 185, 220, 255}, 70, 2},
    {{"0"}, -1, 0, {0,0,0,0,0},0, 2},                                      // Kartu Kesempatan
    {{"Batununggal"}, -1, 0, {125, 160, 190, 225, 260}, 70, 2},
    {{"Maribaya"}, -1, 0, {50, 100, 200, 200, 200},0, 2},                      // tempat wisata 3
    {{"Antapani"}, -1, 0, {140, 180, 220, 260, 300}, 80, 2},
    {{"Andir"}, -1, 0, {145, 185, 225, 265, 305}, 80, 2},
    {{"Sumur Bandung"}, -1, 0, {150, 190, 230, 270, 310}, 80, 2},
    {{"0"}, -1, 0, {0,0,0,0,0},0, 3},                                      // GO TO JAIL
    {{"Dago Dream Park"}, -1, 0, {50, 100, 200, 200, 200},0, 3},               // tempat wisata 4
    {{"Kiaracondong"}, -1, 0, {165, 210, 255, 300, 345}, 90, 3},
    {{"Sukajadi"}, -1, 0, {170, 215, 260, 305, 350}, 90, 3},
    {{"0"}, -1, 0, {0,0,0,0,0},0, 3},                                      // Kartu Kesempatan
    {{"Coblong"}, -1, 0, {190, 240, 290, 340, 390}, 100, 3},
    {{"0"}, -1, 0, {0,0,0,0,0},0, 3},                                      // Kantor Pajak
    {{"Bandung Wetan"}, -1, 0, {200, 245, 295, 345, 395}, 100, 3},

};

void SetDefaultAllProperty(){
    for(int i=0; i<32; i++){
        if(property[i].owner == currentplayer){
            property[i].owner = -1;
            property[i].level = 0;
        }
    }
}

void AutoSellProperty(int moneyneeded){
    for(int i=0; i<32 && player[currentplayer].money <= moneyneeded; i++){
        if(property[i].owner == currentplayer){
            player[currentplayer].money += property[i].upgradeprice * property[i].level + property[i].price[0];
            
            property[i].owner = -1;
            property[i].level = 0;
            player[currentplayer].linecount[property[i].line]--;
            if((i==4) || (i==14) || (i==20) || (i==25)){
                player[currentplayer].touristcount--;
            }
            
        }
    }

    
}
