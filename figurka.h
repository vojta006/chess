#ifndef FIGURKA_H
#define FIGURKA_H
#include <SDL/SDL.h>
#include <vector>
#include <array>

class Sachovnice;

class Figurka
{
public:
    int pos,tabulka,index;
    int hodnota;
    bool tahnuto;
    bool barva;
    int x, y;

    Figurka(bool color,int posX, int posY);
    virtual bool smery(int x, int y, int cx, int cy,bool Strel);
    virtual bool jeSach(int x, int y,std::array<int,4> historie, Sachovnice *s);
    virtual void tazeno(int stareX, int stareY, int noveX, int noveY,std::array<int,4> historie,Sachovnice *s,bool vraceni,bool ai = 0);
    virtual bool moznosti(std::vector<std::array<int,2>> &tahy,Sachovnice *s,std::vector<std::array<int,2>> smery); //informace o tom, ze bylo s figurkou tazeno, napr. rosada
};


#endif // FIGURKA_H
