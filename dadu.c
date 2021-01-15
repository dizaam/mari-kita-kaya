#include "dadu.h"

void resetDadu(dadu* dd){
    dd->totaldd = 0;
    dd->dadu1 = 0;
    dd->dadu2 = 0;
    dd->countdouble = 0;
    dd->isdouble = false;
}

void shakeDadu(dadu* dd){
    srand(time(NULL));
    dd->isdouble = false;
    dd->totaldd = 0;

    
    dd->dadu2 = rand() % 6 + 1;
    dd->dadu1 = rand() % 6 + 1;

    dd->totaldd = dd->dadu1 + dd->dadu2;

    if(dd->dadu1==dd->dadu2){
        dd->isdouble = true;
        dd->countdouble++;
    }
}
