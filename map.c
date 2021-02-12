#include "system.h"

WINDOW* wmap = NULL;

char map[40][100] = {
	"#---------|---------------------------------------------------------------------|---------",
	"|  BEBAS  |CIBENYING|  KESEM  |BATUNUNG.| MARIBAYA| ANTAPANI|  ANDIR  |SUMUR BDG|  MASUK  ",
	"|         |         |         |         |         |         |         |         |         ",
	"|  PARKIR |  $120   |  PATAN  |  $125   |   $20   |  $140   |  $145   |  $150   | PENJARA ",
	"#-----------------------------------------------------------------------------------------",
	"|  REGOL  |                                                                     | DAGO DP ",
	"|         |                                                                     |         ",
	"|  $100   |                                                                     |   $20   ",
	"<---------|                                                                     |---------",
	"|   TSM   |                                                                     | KIRCON  ",
	"|         |                                                                     |         ",
	"|   $20   |                                                                     |  $165   ",
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
	"|   $70   |                     |------------------------|                      | $14.000 ",
	"<---------|                                                                     |---------",
	"|PJK MASUK|                                                                     |BDG WETAN",
	"|         |                                                                     |         ",
	"| $14.000 |                                                                     |  $200   ",
	"#-----------------------------------------------------------------------------------------",
	"|  HANYA  |BUAHBATU |BOJONGLOA| CIBIRU  |  GN. TP | GEDEBAGE|  KESEM  | CICADAP |  START  ",
	"|         |         |         |         |         |         |         |         |         ",
	"|  LEWAT  |   $55   |   $50   |   $45   |   $20   |   $20   |  PATAN  |   $20   |  +$20   ",
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
				waddch(wmap, ACS_VLINE);
			}else if(map[i][j] == '-'){
				waddch(wmap, ACS_HLINE);
			}else{
				waddch(wmap, map[i][j]);
			}
		}
        //waddstr(wmap, map[i]);
        waddch(wmap,'\n');
    }

	box(wmap, ACS_VLINE, ACS_HLINE);

	wrefresh(wmap);
}