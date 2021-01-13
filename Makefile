CCLIN	=	gcc
STD		=	-std=c11
SRC		=	properti.c map.c dadu.c player.c main.c
CFLAG	=	-Wall
LIB		= 	-lncurses

all	:
		$(CCLIN) $(SRC) $(CFLAG) $(LIB)
