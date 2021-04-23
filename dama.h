#ifndef DAMA_H
#define DAMA_H
#include "figurka.h"

class Dama:public Figurka//:public Strelec,public Vez
{
public:
    Dama(bool color);
    Figurka *vytvor();
    virtual bool moznosti(int x, int y , int cilX, int cilY, Sachovnice *s,bool kdoVola =0);
};


#endif // DAMA_H
