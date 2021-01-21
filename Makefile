CCLIN	=	gcc
OUT		=	-o "MariKitaKaya"
STD		=	-std=c11
SRC		=	menu.c game.c properti.c map.c dadu.c player.c main.c
CFLAG	=	-Wall
LIB		= 	-lncurses

all	:
		$(CCLIN) $(SRC) $(OUT) $(CFLAG) $(LIB)
