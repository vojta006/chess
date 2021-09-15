#ifndef PESEC_H
#define PESEC_H
#include "figurka.h"


class Pesec:public Figurka
{
private:
    Figurka *mimo;
public:
    Pesec(bool color, int posX, int posY);
    virtual bool smery(int x, int y, int cx, int cy,bool vezStrel);
    void tazeno(int stareX, int stareY, int noveX, int noveY,std::array<int,4> historie,Sachovnice *s,bool vraceni,bool ai = 0);
    bool moznosti(std::vector<std::array<int,2>> &tahy,Sachovnice *s,std::vector<std::array<int,2>> smery);
};


#endif // PESEC_H
