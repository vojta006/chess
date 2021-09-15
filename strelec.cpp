#include "strelec.h"
#include "main.h"

Strelec::Strelec(bool color):Figurka(color){
    hodnota = 320;
    pos = tabulka =  2;
}

bool Strelec::moznosti(int x, int y, int cilX, int cilY, Sachovnice *s, bool kdoVola){
    if(abs(cilX-x) == abs(cilY-y) && !(x==cilX && y==cilY))
        return Figurka::moznosti(x,y,cilX,cilY,s,kdoVola);

    return false;
}

Figurka *Strelec::vytvor(){
    Strelec * v= new Strelec(barva);
    v->tahnuto=this->tahnuto;
    return v;
}

