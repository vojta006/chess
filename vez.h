#ifndef VEZ_H
#define VEZ_H
#include "figurka.h"

class Vez: virtual public Figurka {
private:

public:
    Vez(bool color);
    Figurka *vytvor();
    virtual bool moznosti(int x, int y , int cilX, int cilY,Sachovnice *s,bool kdoVola =0);
};

#endif // VEZ_H
