#include "dama.h"
#include "main.h"

Dama::Dama(bool color, int posX, int posY):Figurka(color,posX, posY), Strelec(color,posX,posY), Vez (color,posX,posY){
    hodnota = 900;
    pos = tabulka = 4;
}

bool Dama::moznosti(std::vector<std::array<int, 2> > &tahy, Sachovnice *s, std::vector<std::array<int, 2> > minule){
    Vez::moznosti(tahy,s,{});
    return Strelec::moznosti(tahy,s,{});
}

bool Dama::smery(int x, int y, int cx, int cy, bool vezStrel){
    return Vez::smery(x,y,cx,cy,vezStrel)? true: Strelec::smery(x,y,cx,cy,vezStrel);
}


