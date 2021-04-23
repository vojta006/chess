#ifndef SACHOVNICE_H
#define SACHOVNICE_H
#include "figurka.h"
#include "obrazovka.h"
#include <vector>
#include <array>
#include <map>

#define BILAFIG 1
#define CERNAFIG 0
#define MAX_HLOUBKA 4
#define ZMENA_FIGUREK 3 //po jake hloubce se ma ukoncit ohodnocovani
using namespace std;

class Sachovnice:public Screen
{
private:
    SDL_Surface *matBila,*matCerna,*pat,*sachovnice,*obrysZ,*obrysM,*obrysC,*Bila;
    int figX,figY,kresli_hodnoceni;
    bool klikPosun = false, generuj = true, prekresli = true,  sach = false, koncovka; //je aktivni, kdyz je vybrana figurka z lze ji posunout
    int *pozice,okraj,policko,histVrat; //k jake verzi sachovnice se vracet
public:
    Figurka *pole[8][8];
    Figurka *mimochodem[MAX_HLOUBKA+1]={NULL}; //uklada figurky vyhozene mimochodem
    int Hloubka, minX,minY,CkX,CkY,BkX,BkY; //aktualni hloubka rekurze
    int *rosadaBila,*rosadaCerna,pocetTahu; //
    bool tah,rosada[2]={};
    void vrat(bool dopredu);
    int minule[MAX_HLOUBKA+2][2];
    vector<array<int,5>> tahy;
    void kresli();
    Sachovnice();
    void pridej();
    void dalsiTah();
    int hodnoceni();
    void porovnani(Sachovnice *zdroj);
    void klik(int MysX,int MysY);
    void posun(int stareX, int stareY, int noveX, int noveY,int &minX,int &minY,bool ai = 0);
    void zkopiruj(Sachovnice *zdroj, bool prekresli = 0);
    bool overeni(Figurka *kontrolni[8][8]);
    int generujTahy(int max_hloubka, int srovnani,int material=0);
    void zalohuj(Figurka *zdroj[8][8],Figurka *cil[8][8],bool zalohy[8][8],bool zalohuj);
    void zalohuj(Figurka * zdroj[8][8],Figurka * cil[8][8]);
    vector<array<int,5>> historieTahy;
    int material(bool barva);
    int konec[8][8] =    {{00,  00,  00,  00,  00,  00,  00,  00}, //pesec
                          {50,  50,  50,  50,  50,  50,  50,  50},
                          {40,  40,  40,  40,  40,  40,  40,  40},
                          {30,  30,  30,  25,  25,  30,  30,  30},
                          {20,  20,  20,  20,  20,  20,  20,  20},
                          {10, 10, 10,  10,  10, 10, 10,  10},
                          {0,  0, 0,  0, 0,  0,  0,  0},
                          {00,  00,  00,  00,  00,  00,  00,  00}};

    int  hodnoty[6][8][8] ={{{00,  00,  00,  00,  00,  00,  00,  00}, //pesec
                             {50,  50,  50,  50,  50,  50,  50,  50},
                             {10,  10,  20,  30,  30,  20,  10,  10},
                             {05,  05,  10,  25,  25,  10,  05,  05},
                             {00,  00,  00,  20,  20,  00,  00,  00},
                             {05, -05, -10,  00,  00, -10, -05,  05},
                             {05,  10, 10,  -20, -20,  10,  10,  05},
                             {00,  00,  00,  00,  00,  00,  00,  00}},

                            {{-50, -40, -30, -30, -30, -30, -40, -50}, //kun
                             {-40, -20,  00,  00,  00,  00, -20, -40},
                             {-30,  00,  10,  15,  15,  10,  00, -30},
                             {-30,  05,  15,  20,  20,  15,  05, -30},
                             {-30,  00,  15,  20,  20,  15,  00, -30},
                             {-30,  05,  10,  15,  15,  10,  05, -30},
                             {-40, -20,  00,  05,  05,  00, -20, -40},
                             {-50, -40, -30, -30, -30, -30, -40, -50}},

                            {{-20, -10, -10, -10, -10, -10, -10, -20}, //strelec
                             {-10,  00,  00,  00,  00,  00,  00, -10},
                             {-10,  00,  05,  10,  10,  05,  00, -10},
                             {-10,  05,  05,  10,  10,  05,  05, -10},
                             {-10,  00,  10,  10,  10,  10,  00, -10},
                             {-10,  10,  10,  10,  10,  10,  10, -10},
                             {-10,  05,  00,  00,  00,  00,  05, -10},
                             {-20, -10, -10, -10, -10, -10, -10, -20}},

                            {{ 00, 00, 00, 00, 00, 00, 00,  00}, //vez
                             { 05, 10, 10, 10, 10, 10, 10,  05},
                             {-05, 00, 00, 00, 00, 00, 00, -05},
                             {-05, 00, 00, 00, 00, 00, 00, -05},
                             {-05, 00, 00, 00, 00, 00, 00, -05},
                             {-05, 00, 00, 00, 00, 00, 00, -05},
                             {-05, 00, 00, 00, 00, 00, 00, -05},
                             { 00, 00, 00, 05, 05, 00, 00,  00}},

                            {{-20, -10, -10, -05, -05, -10, -10, -20}, //kralovna
                             {-10,  00,  00,  00,  00,  00,  00, -10},
                             {-10,  00,  05,  05,  05,  05,  00, -10},
                             {-05,  00,  05,  05,  05,  05,  00, -05},
                             {-05,  00,  05,  05,  05,  05,  00, -05},
                             {-10,  05,  05,  05,  05,  05,  00, -10},
                             {-10,  00,  05,  00,  00,  00,  00, -10},
                             {-20, -10, -10, -05, -05, -10, -10, -20}},

                            {{ -30, -40, -40, -50, -50, -40, -40, -30}, //kral
                             { -30, -40, -40, -50, -50, -40, -40, -30},
                             { -30, -40, -40, -50, -50, -40, -40, -30},
                             { -30, -40, -40, -50, -50, -40, -40, -30},
                             { -20, -30, -30, -40, -40, -30, -30, -20},
                             { -10, -20, -20, -20, -20, -20, -20, -10},
                             {  20,  20,  00,  00,  00,  00,  20,  20},
                             {  20,  30,  10,  00,  00,  10,  30,  20}}};

};

#endif // SACHOVNICE_H