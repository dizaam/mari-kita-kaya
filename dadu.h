#ifndef _DADU_H
#define _DADU_H
#include <time.h>


// membuat tipe data dadu 
typedef struct dadu{
    int dadu1;
    int dadu2;
    int totaldd;
    int countdouble;
    bool isdouble;

}dadu;

//dadu dadu;

// prosedur untuk mereset nilai dadu
void resetDadu(dadu* dd);

// prosedur untuk mengocok dadu
void kocokDadu(dadu* dd);

#endif