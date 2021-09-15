#ifndef DAMA_H
#define DAMA_H
#include "strelec.h"
#include "vez.h"

class Dama: public Strelec, public Vez
{
public:
    Dama(bool color, int posX, int posY);
    virtual bool smery(int x, int y, int cx, int cy, bool vezStrel);
    virtual bool moznosti(std::vector<std::array<int,2>> &tahy,Sachovnice *s,std::vector<std::array<int,2>> smery);
};


#endif // DAMA_H
