CCLIN	=	gcc
OUT		=	-o "MariKitaKaya"
STD		=	-std=c11
SRC		=	card.c menu.c game.c property.c map.c dice.c player.c main.c
CFLAG	=	-Wall
LIB		= 	-lncurses

all	:
		$(CCLIN) $(SRC) $(OUT) $(CFLAG) $(LIB)
