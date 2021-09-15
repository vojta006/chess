#include "vez.h"

Vez::Vez(bool color, int posX, int posY): Figurka(color,posX, posY){
    hodnota = 500;
    pos = tabulka = 3;
}

bool Vez::moznosti(std::vector<std::array<int, 2> > &tahy, Sachovnice *s, std::vector<std::array<int, 2>> nepouzito){
    return Figurka::moznosti(tahy,s,{{1,0},{0,1},{-1,0},{0,-1}});
}

bool Vez::smery(int x, int y, int cx, int cy, bool Strel){
    if(Strel && (x == cx || y == cy)) return true;
    return false;
}
