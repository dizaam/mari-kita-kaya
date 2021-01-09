CCLIN	=	gcc
CCWIN	=	mingw
SRC		=	properti.c map.c dadu.c player.c main.c
CFLAG	=	-Wall

win :
		$(CCWIN) $(SRC) $(CFLAG)
lin	:
		$(CCLIN) $(SRC) $(CFLAG)
