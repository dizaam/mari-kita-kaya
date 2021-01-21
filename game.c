#include "system.h"


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