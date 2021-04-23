#ifndef STRELEC_H
#define STRELEC_H
#include "figurka.h"

class Strelec: virtual public Figurka
{
public:
    Strelec(bool color);
    Figurka *vytvor();
    virtual bool moznosti(int x, int y, int cilX, int cilY, Sachovnice *s,bool kdoVola = 0);
};

#endif // STRELEC_H
