#include "strelec.h"

Strelec::Strelec(bool color , int posX, int posY): Figurka(color,posX, posY){
    hodnota = 320;
    pos = tabulka =  2;
}

bool Strelec::moznosti(std::vector<std::array<int, 2> > &tahy, Sachovnice *s, std::vector<std::array<int,2>> nepouzito){
    return Figurka::moznosti(tahy,s,{{1,1},{1,-1},{-1,1},{-1,-1}});
}

bool Strelec::smery(int x, int y, int cx, int cy,bool vezStrel){ //prijdou souradnice na uhlopricce, nebo na care
    if(vezStrel &&( x != cx || y != cy)) return false; //meli by prijit jen souradnice
    return false;
}
