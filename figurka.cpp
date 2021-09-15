#include "figurka.h"
#include "sachovnice.h"
#include "SDL/SDL.h"
#include <SDL/SDL_image.h>
#include "main.h"

Figurka::Figurka(bool color):barva(color)
{
    barva = color;
    tahnuto = false;
}

void Figurka::tazeno(int stareX, int stareY, int noveX, int noveY, Sachovnice *s, bool ai){tahnuto=true;}

bool Figurka::vratbarvu(){return barva;}

bool Figurka::tahnuti(){return tahnuto;}

void Figurka::konec(){}

bool Figurka::pozorSach(int x, int y, Sachovnice *s){}

bool Figurka::moznosti(int x, int y, int cilX, int cilY, Sachovnice *s, bool kdoVola){
    int dX,dY;                               //kdoVola  = 0  - pta se na moznosti tahu
    bool stop = false;                          //kdo Vola =1 - pta se na ohrozeni
    if(cilX!=x) dX = (cilX-x)/abs(cilX-x); //vzniklo by deleni nulou
    else dX = 0;
    if(cilY!=y) dY = (cilY-y)/abs(cilY-y); //do delty se ulozi 1, nebo -1, nebo 0
    else dY = 0;
    int i = x+y*8;
    while(i != cilX+cilY*8){
        x+=dX,y+=dY;
        i = x + y*8;
        if(stop || (!kdoVola && s->pole[x][y] && s->pole[x][y]->barva==barva)) return false;
        if(s->pole[x][y]) stop = true;
    }
    return true;
}
Figurka::~Figurka(){}

