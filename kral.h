#ifndef KRAL_H
#define KRAL_H
#include "figurka.h"


class Sachovnice;
class Vez;
class Kral:public Figurka
{

private:
    bool sachuje(int x, int y, int fx, int fy, Sachovnice *s);
public:
    Kral(bool color, int posX, int posY);
    bool jeSach(int x, int y,std::array<int,4> historie, Sachovnice *s);
    void tazeno(int stareX, int stareY, int noveX, int noveY,std::array<int,4> historie, Sachovnice *s,bool vraceni,bool ai =0);
    virtual bool moznosti(std::vector<std::array<int,2>> &tahy,Sachovnice *s,std::vector<std::array<int,2>> smery);
};
#endif // KRAL_H
