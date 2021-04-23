#ifndef MENU_H
#define MENU_H
#include "obrazovka.h"

class Menu: public Screen
{
private:
    int pesecX,pesecY;
    int polroz;
    bool pesecBarva;
public:
    Menu();
    void kresli();
    void nactiPesec(bool barva, int x,int y);
    void PesecKonec(int x,int y);
    void  klik(int MysX,int MysY);
    void umisti(bool barva);
    void konec();
};

#endif // MENU_H
