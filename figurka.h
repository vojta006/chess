#ifndef FIGURKA_H
#define FIGURKA_H
#include <SDL/SDL.h>
#include <iostream>

class Sachovnice;
class Figurka
{
public:
    int pos;
    int hodnota;
    bool tahnuto;
    bool barva;
    void kresli();
    Figurka(bool color);
    bool tahnuti(); //vraci tahnuto figurky
    bool vratbarvu(); //vraci barvu
    void umisti(int x,int y); //umistuje figurku
    virtual Figurka *vytvor()=0; //vytvori kopii figurky
    virtual void konec();
    virtual bool pozorSach(int x,int y,Sachovnice *s);
    virtual void tazeno(int stareX, int stareY, int noveX, int noveY,Sachovnice *s,bool ai = 0);
    virtual bool moznosti(int x, int y , int cilX, int cilY, Sachovnice *s, bool kdoVola = 0); //informace o tom, ze bylo s figurkou tazeno, napr. rosada
};


#endif // FIGURKA_H
