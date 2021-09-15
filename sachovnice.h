#ifndef SACHOVNICE_H
#define SACHOVNICE_H

#include <vector>
#include <array>
#include <list>
#include "obrazovka.h"
#include "figurka.h"

#ifndef BILAFIG
#define BILAFIG 1
#define CERNAFIG 0
#endif

#define MAX_HLOUBKA 4
#define ZMENA_FIGUREK 3 //po jake hloubce se ma ukoncit ohodnocovani

using namespace std;
class Komunikace;
class SDL_Surface;

class Sachovnice:public Screen
{
private:
    SDL_Surface *matBila,*matCerna,*pat,*sachovnice,*obrysZ,*obrysM,*obrysC,*Bila,*Menu; //obrazky
    int figX,figY,Hloubka;
    bool klikPosun, generuj = true, prekresli = true,  sach = false, koncovka; //je aktivni, kdyz je vybrana figurka z lze ji posunout
    int okraj,policko;
    Figurka *kralove[2];
public:
    array<vector<array<int,2>>,2> poloha;
    Figurka *figurky[8][8];
    int histVrat;
    Komunikace *diblik;    
    vector<array<int,4>> historie;
    SDL_Surface *figObrazky;
    int pocetTahu;
    bool tah,hraniOnline;
    vector<array<int,5>> tahy;

    void kresli();
    int hodnoceni(int x,int y, int cx, int cy, int stare, Figurka *vyhozena);
    Sachovnice();
    void dalsiTah(bool posli);
    void klik(int MysX,int MysY);
    int hodnoceni();
    void posun(int stareX, int stareY, int noveX, int noveY, array<int,4> historie);
    int generujTahy(int max_hloubka, int srovnani, int hodnota,  std::array<int,4> historie);
    ~Sachovnice();
    void vypis();
    int fig[2][16][2];

    int  hodnoty[7][8][8] ={{{00,  00,  00,  00,  00,  00,  00,  00}, //pesec
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
                             {  20,  30,  10,  00,  00,  10,  30,  20}},

                            {{00,  00,  00,  00,  00,  00,  00,  00}, //pesec konec
                            {50,  50,  50,  50,  50,  50,  50,  50},
                            {40,  40,  40,  40,  40,  40,  40,  40},
                            {30,  30,  30,  25,  25,  30,  30,  30},
                            {20,  20,  20,  20,  20,  20,  20,  20},
                            {10, 10, 10,  10,  10, 10, 10,  10},
                            {0,  0, 0,  0, 0,  0,  0,  0},
                            {00,  00,  00,  00,  00,  00,  00,  00}}};
};

#endif // SACHOVNICE_H
