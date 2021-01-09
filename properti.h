#ifndef _PROPERTI_H
#define _PROPERTI_H
#include <stdbool.h>


typedef struct properti{
    char name[50];
    int owner;
    int level;
    int price[5];
}properti;

extern properti property[32];

#endif