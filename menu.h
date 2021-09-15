#ifndef MENU_H
#define MENU_H
#include "obrazovka.h"
#include <SDL/SDL.h>
#include <map>

using namespace std;
class Menu: public Screen
{
private:
    int pesecX,pesecY;
    int polroz,stav;
    bool pesecBarva,prekresli,vybirani; //vybirani mistnosti
    SDL_Surface *komunikace,*MPozadi,*server,*zpet,*ukoncit,*vyberMistnost,*mistnosti,*konec; //obrazek

    //map<string,SDL_Surface*> tlacitka;
    //map<string,array<int,4>> obrPozice;

    SDL_Surface *figurky;
    void menuKresli();
    void menuKlik(int x, int y);
public:
    Menu();
    void menu();
    void kresli();
    void nactiPesec(bool barva, int x,int y);
    void PesecKlik(int x,int y);
    void klik(int MysX,int MysY);
    void pesecKresli();
    void konecHry();
    void konecKlik(int x, int y);
    void zacatekKlik(int MysX, int MysY);
    void zacatekKresli();
};

#endif // MENU_H
