#ifndef KRAL_H
#define KRAL_H
#include "figurka.h"


class Sachovnice;
class Kral:public Figurka
{
public:
    Kral(bool color);
    Figurka *vytvor();
    bool neniKral(Sachovnice *s);
    bool pozorSach(int kX, int kY, Sachovnice *s);
    void tazeno(int stareX, int stareY, int noveX, int noveY, Sachovnice *s,bool ai =0);
    virtual bool moznosti(int x, int y , int cilX, int cilY, Sachovnice *s,bool kdoVola = 0);
};
#endif // KRAL_H
