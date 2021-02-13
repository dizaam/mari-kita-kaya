#include "system.h"

WINDOW* wmap = NULL;

char map[40][100] = {
	"#---------|---------------------------------------------------------------------|---------",
	"|  BEBAS  |CIBENYING|  KESEM  |BATUNUNG.| MARIBAYA| ANTAPANI|  ANDIR  |SUMUR BDG|  MASUK  ",
	"|         |         |         |         |         |         |         |         |         ",
	"|  PARKIR |  $120   |  PATAN  |  $125   |   $50   |  $140   |  $145   |  $150   | PENJARA ",
	"#-----------------------------------------------------------------------------------------",
	"|  REGOL  |                                                                     | DAGO DP ",
	"|         |                                                                     |         ",
	"|  $100   |                                                                     |   $50   ",
	"<---------|                                                                     |---------",
	"|   TSM   |                                                                     | KIRCON  ",
	"|         |                                                                     |         ",
	"|   $50   |                                                                     |  $165   ",
	"<---------|                                                                     |---------",
	"|LENGKONG |                                                                     |SUKAJADI ",
	"|         |                                                                     |         ",
	"|   $95   |                                                                     |  $170   ",
	"<---------|                                                                     |---------",
	"|  KESEM  |                                                                     |  KESEM  ",
	"|         |                                                                     |         ",
	"|  PATAN  |                                                                     |  PATAN  ",
	"<---------|                                                                     |---------",
	"|ARCAMANIK|                     |------------------------|                      | COBLONG ",
	"|         |                     |                        |                      |         ",
	"|   $75   |                     |          KARTU         |                      |  $190   ",
	"<---------|                     |                        |                      |---------",
	"| CICENDO |                     |       KESEMPATAN       |                      |PJK MASUK",
	"|         |                     |                        |                      |         ",
	"|   $70   |                     |------------------------|                      |  $ 100  ",
	"<---------|                                                                     |---------",
	"|PJK MASUK|                                                                     |BDG WETAN",
	"|         |                                                                     |         ",
	"|  $ 100  |                                                                     |  $200   ",
	"#-----------------------------------------------------------------------------------------",
	"|  HANYA  |BUAHBATU |BOJONGLOA| CIBIRU  |  GN. TP | GEDEBAGE|  KESEM  | CIDADAP |  START  ",
	"|         |         |         |         |         |         |         |         |  @!*%   ",
	"|  LEWAT  |   $55   |   $50   |   $45   |   $50   |   $20   |  PATAN  |   $20   |  +$200  ",
	"#---------|---------------------------------------------------------------------|---------"
	};

int board[32] = {
	1,	// start
	6,	// properti
	5,	// kesempatan
	6,	// properti
	7,	// properti wisata
	6,	// properti
	6,	// properti
	6,	// properti
	3,	// hanya lewat
	4,	// pajak
	6,	// properti
	6,	// properti
	5,	// kesempatan
	6,	// properti
	7,	// properti wisata
	6,	// properti
	2,	// bebas parkir / pintu kemana saja
	6,	// properti
	5,	// kesempatan
	6,	// properti
	7,	// properti wisata
	6,	// properti
	6,	// properti
	6,	// properti
	0,	// masuk penjara
	7,	// properti wisata
	6,	// properti
	6,	// properti 
	5,	// kesempatan
	6,	// properti
	4,	// pajak
	6,	// properti
};

// modul untuk menampilkan papan monopoly
void DrawMap(){
	touchwin(wmap);

	for(int i=0; i<37; i++){
		for(int j=0; j<90; j++){
			if(map[i][j] == '|'){
				mvwaddch(wmap, i, j, ACS_VLINE);
			}else if(map[i][j] == '-'){
				mvwaddch(wmap, i, j, ACS_HLINE);
			}else if(map[i][j] == '@'){
				wattrset(wmap, COLOR_PAIR(PLAYER1_COLOR) | A_REVERSE);
				mvwaddch(wmap, i, j, map[i][j]);
				wattrset(wmap, A_NORMAL);
			}else if (map[i][j] == '!'){
				wattrset(wmap, COLOR_PAIR(PLAYER2_COLOR) | A_REVERSE);
				mvwaddch(wmap, i, j, map[i][j]);
				wattrset(wmap, A_NORMAL);
			}else if (map[i][j] == '*'){
				wattrset(wmap, COLOR_PAIR(PLAYER3_COLOR) | A_REVERSE);
				mvwaddch(wmap, i, j, map[i][j]);
				wattrset(wmap, A_NORMAL);
			}else if (map[i][j] == '%'){
				wattrset(wmap, COLOR_PAIR(PLAYER4_COLOR) | A_REVERSE);
				mvwaddch(wmap, i, j, map[i][j]);
				wattrset(wmap, A_NORMAL);
			}else{
				mvwaddch(wmap, i, j, map[i][j]);
			}
		}
        //waddstr(wmap, map[i]);
        waddch(wmap,'\n');
    }

	box(wmap, ACS_VLINE, ACS_HLINE);

	wrefresh(wmap);
}

MAPPOSITION getMapPosition(int position){
	MAPPOSITION result;
	switch (position){
		case 0:
			result.row = 34;
			result.col = 83+currentplayer;
			break;
		case 1:
			result.row = 34;
			result.col = 73+currentplayer;
			break;
		case 2:
			result.row = 34;
			result.col = 63+currentplayer;
			break;
		case 3:
			result.row = 34;
			result.col = 53+currentplayer;
			break;
		case 4:
			result.row = 34;
			result.col = 43+currentplayer;
			break;
		case 5:
			result.row = 34;
			result.col = 33+currentplayer;
			break;
		case 6:
			result.row = 34;
			result.col = 23+currentplayer;
			break;
		case 7:
			result.row = 34;
			result.col = 13+currentplayer;
			break;
		case 8:
			result.row = 34;
			result.col = 3+currentplayer;
			break;
		case 9:
			result.row = 30;
			result.col = 3+currentplayer;
			break;
		case 10:
			result.row = 26;
			result.col = 3+currentplayer;
			break;
		case 11:
			result.row = 22;
			result.col = 3+currentplayer;
			break;
		case 12:
			result.row = 18;
			result.col = 3+currentplayer;
			break;
		case 13:
			result.row = 14;
			result.col = 3+currentplayer;
			break;
		case 14:
			result.row = 10;
			result.col = 3+currentplayer;
			break;
		case 15:
			result.row = 6;
			result.col = 3+currentplayer;
			break;
		case 16:
			result.row = 2;
			result.col = 3+currentplayer;
			break;
		case 17:
			result.row = 2;
			result.col = 13+currentplayer;
			break;
		case 18:
			result.row = 2;
			result.col = 23+currentplayer;
			break;
		case 19:
			result.row = 2;
			result.col = 33+currentplayer;
			break;
		case 20:
			result.row = 2;
			result.col = 43+currentplayer;
			break;
		case 21:
			result.row = 2;
			result.col = 53+currentplayer;
			break;
		case 22:
			result.row = 2;
			result.col = 63+currentplayer;
			break;
		case 23:
			result.row = 2;
			result.col = 73+currentplayer;
			break;
		case 24:
			result.row = 2;
			result.col = 83+currentplayer;
			break;
		case 25:
			result.row = 6;
			result.col = 83+currentplayer;
			break;
		case 26:
			result.row = 10;
			result.col = 83+currentplayer;
			break;
		case 27:
			result.row = 14;
			result.col = 83+currentplayer;
			break;
		case 28:
			result.row = 18;
			result.col = 83+currentplayer;
			break;
		case 29:
			result.row = 22;
			result.col = 83+currentplayer;
			break;
		case 30:
			result.row = 26;
			result.col = 83+currentplayer;
			break;
		case 31:
			result.row = 30;
			result.col = 83+currentplayer;
			break;
		default:
			break;
	}

	return result;
}

void RemovePawn(){
	touchwin(wmap);
	MAPPOSITION currentpos = getMapPosition(player[currentplayer].position);
	switch(currentplayer){
		case 0:
			map[currentpos.row][currentpos.col]=' ';
			DrawMap();
			break;
		case 1:
			map[currentpos.row][currentpos.col]=' ';
			DrawMap();
			break;
		case 2:
			map[currentpos.row][currentpos.col]=' ';
			DrawMap();
			break;
		case 3:
			map[currentpos.row][currentpos.col]=' ';
			DrawMap();
			break;
		default:
			break;	
	}
	wrefresh(wmap);
}

void DrawPawn(){
	touchwin(wmap);
	MAPPOSITION currentpos = getMapPosition(player[currentplayer].position);
	switch(currentplayer){
		case 0:
			map[currentpos.row][currentpos.col]='@';
			DrawMap();
			break;
		case 1:
			map[currentpos.row][currentpos.col]='!';
			DrawMap();
			break;
		case 2:
			map[currentpos.row][currentpos.col]='*';
			DrawMap();
			break;
		case 3:
			map[currentpos.row][currentpos.col]='%';
			DrawMap();
			break;
		default:
			break;	
	}
	wrefresh(wmap);
}