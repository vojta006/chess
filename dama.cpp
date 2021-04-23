#include "dama.h"
#include "main.h"

Dama::Dama(bool color):Figurka(color){//:Strelec(color,sachovnice),Vez (color,sachovnice){
    hodnota = 900;
    pos = 4;
}

bool Dama::moznosti(int x, int y, int cilX, int cilY, Sachovnice *sachovnice, bool kdoVola){
    if((x==cilX||y==cilY) && !(x==cilX && y==cilY)) //dama muze tuto cestu prejit
        return Figurka::moznosti(x,y,cilX,cilY,sachovnice,kdoVola);
    if(abs(cilX-x) == abs(cilY-y) && !(x==cilX && y==cilY)) //strelcova cesta
          return Figurka::moznosti(x,y,cilX,cilY,sachovnice,kdoVola);
    else return false;
}

Figurka *Dama::vytvor(){
    Dama* v = new Dama(barva);
    v->tahnuto = this->tahnuto;
    return v;
}
