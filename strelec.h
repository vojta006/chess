#ifndef STRELEC_H
#define STRELEC_H
#include "figurka.h"

class Strelec: virtual public Figurka
{
public:
    Strelec(bool color,int posX, int posY);
    virtual bool smery(int x, int y, int cx, int cy,bool vezStrel);
    bool moznosti(std::vector<std::array<int,2>> &tahy,Sachovnice *s,std::vector<std::array<int,2>> smery);
};

#endif // STRELEC_H
