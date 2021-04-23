#ifndef KUN_H
#define KUN_H
#include "figurka.h"


class Kun:public Figurka
{
public:
    Kun(bool color);
    Figurka *vytvor();
    virtual bool moznosti(int x, int y , int cilX, int cilY, Sachovnice *s, bool kdoVola = 0);
};


#endif // KUN_H
