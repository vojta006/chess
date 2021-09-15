#ifndef PESEC_H
#define PESEC_H
#include "figurka.h"


class Pesec:public Figurka
{
public:
    Pesec(bool color);
    Figurka *vytvor();
    void tazeno(int stareX, int stareY, int noveX, int noveY,Sachovnice *s,bool ai = 0);
    bool moznosti(int x, int y , int cilX, int cilY, Sachovnice *s,bool kdoVola = 0);
    ~Pesec();
};


#endif // PESEC_H
