#ifndef VEZ_H
#define VEZ_H
#include "figurka.h"

class Vez: virtual public Figurka {
private:

public:
    Vez(bool color, int posX, int posY);
    virtual bool smery(int x, int y, int cx, int cy,bool vezStrel);
    virtual bool moznosti(std::vector<std::array<int,2>> &tahy,Sachovnice *s,std::vector<std::array<int,2>> smery);
};

#endif // VEZ_H
