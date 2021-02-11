#include "dadu.h"

DDICE dice;

char dicesymbol[10][10][10] = {
    {
        "#=======#",
        "|       |",
        "|   O   |",
        "|       |",
        "#=======#",
    },
    {
        "#=======#",
        "|    O  |",
        "|       |",
        "|  O    |",
        "#=======#",
    },
    {
        "#=======#",
        "|    O  |",
        "|   O   |",
        "|  O    |",
        "#=======#",
    },
    {
        "#=======#",
        "|  O O  |",
        "|       |",
        "|  O O  |",
        "#=======#",
    },
    {
        "#=======#",
        "|  O O  |",
        "|   O   |",
        "|  O O  |",
        "#=======#",
    },
    {
        "#=======#",
        "|  O O  |",
        "|  O O  |",
        "|  O O  |",
        "#=======#",
    },
};

void resetDice(){
    dice.totaldice = 0;
    dice.dice1 = 0;
    dice.dice2 = 0;
    dice.countdouble = 0;
    dice.isdouble = false;
}

void shakeDice(){
    srand(time(NULL));
    dice.isdouble = false;
    dice.totaldice = 0;

    
    dice.dice2 = rand() % 6 + 1;
    dice.dice1 = rand() % 6 + 1;

    dice.totaldice = dice.dice1 + dice.dice2;

    if(dice.dice1==dice.dice2){
        dice.isdouble = true;
        dice.countdouble++;
    }
}
