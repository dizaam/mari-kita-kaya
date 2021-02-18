#include "allheader.h"

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
	"|         |         |         |         |         |         |         |         |         ",
	"|  LEWAT  |   $55   |   $50   |   $45   |   $50   |   $20   |  PATAN  |   $20   |  +$100  ",
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

	DrawProperty();

	box(wmap, ACS_VLINE, ACS_HLINE);

	wrefresh(wmap);
}

void DrawProperty(){
	touchwin(wmap);
	

	wattrset(wmap, COLOR_PAIR(property[1].owner+1) | A_BOLD);
	mvwaddstr(wmap, 33, 72, "CIDADAP");

	wattrset(wmap, COLOR_PAIR(property[3].owner+1) | A_BOLD);
	mvwaddstr(wmap, 33, 52, "GEDEBAGE");
	
	wattrset(wmap, COLOR_PAIR(property[4].owner+1) | A_BOLD);
	mvwaddstr(wmap, 33, 43, "GN. TP");
	
	wattrset(wmap, COLOR_PAIR(property[5].owner+1) | A_BOLD);
	mvwaddstr(wmap, 33, 32, "CIBIRU");
	
	wattrset(wmap, COLOR_PAIR(property[6].owner+1) | A_BOLD);
	mvwaddstr(wmap, 33, 21, "BOJONGLOA");
	
	wattrset(wmap, COLOR_PAIR(property[7].owner+1) | A_BOLD);
	mvwaddstr(wmap, 33, 11, "BUAHBATU");
	
	wattrset(wmap, COLOR_PAIR(property[10].owner+1) | A_BOLD);
	mvwaddstr(wmap, 25, 2, "CICENDO");
	
	wattrset(wmap, COLOR_PAIR(property[11].owner+1) | A_BOLD);
	mvwaddstr(wmap, 21, 1, "ARCAMANIK");
	
	wattrset(wmap, COLOR_PAIR(property[13].owner+1) | A_BOLD);
	mvwaddstr(wmap, 13, 1, "LENGKONG");
	
	wattrset(wmap, COLOR_PAIR(property[14].owner+1) | A_BOLD);
	mvwaddstr(wmap, 9, 4, "TSM");
	
	wattrset(wmap, COLOR_PAIR(property[15].owner+1) | A_BOLD);
	mvwaddstr(wmap, 5, 3, "REGOL");
	
	wattrset(wmap, COLOR_PAIR(property[17].owner+1) | A_BOLD);
	mvwaddstr(wmap, 1, 11, "CIBENYING");

	wattrset(wmap, COLOR_PAIR(property[19].owner+1) | A_BOLD);
	mvwaddstr(wmap, 1, 31, "BATUNUNG.");

	wattrset(wmap, COLOR_PAIR(property[20].owner+1) | A_BOLD);
	mvwaddstr(wmap, 1, 42, "MARIBAYA");

	wattrset(wmap, COLOR_PAIR(property[21].owner+1) | A_BOLD);
	mvwaddstr(wmap, 1, 52, "ANTAPANI");

	wattrset(wmap, COLOR_PAIR(property[22].owner+1) | A_BOLD);
	mvwaddstr(wmap, 1, 63, "ANDIR");

	wattrset(wmap, COLOR_PAIR(property[23].owner+1) | A_BOLD);
	mvwaddstr(wmap, 1, 71, "SUMUR BDG");

	wattrset(wmap, COLOR_PAIR(property[25].owner+1) | A_BOLD);
	mvwaddstr(wmap, 5, 82, "DAGO DP");

	wattrset(wmap, COLOR_PAIR(property[26].owner+1) | A_BOLD);
	mvwaddstr(wmap, 9, 82, "KIRCON");
	
	wattrset(wmap, COLOR_PAIR(property[27].owner+1) | A_BOLD);
	mvwaddstr(wmap, 13, 81, "SUKAJADI");

	wattrset(wmap, COLOR_PAIR(property[29].owner+1) | A_BOLD);
	mvwaddstr(wmap, 21, 82, "COBLONG");

	wattrset(wmap, COLOR_PAIR(property[31].owner+1) | A_BOLD);
	mvwaddstr(wmap, 29, 81, "BDG WETAN");

	wattrset(wmap, A_NORMAL);
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