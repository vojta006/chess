#include "vez.h"
#include "main.h"

Vez::Vez(bool color): Figurka(color){
    hodnota = 500;
    pos = 3;
}

bool Vez::moznosti(int x, int y, int cilX, int cilY, Sachovnice *sachovnice, bool kdoVola){
    if((x==cilX || y==cilY) && !(x==cilX && y==cilY)) //vez muze tuto cestu prejit
        return Figurka::moznosti(x,y,cilX,cilY,sachovnice,kdoVola);
    return false;
}

Figurka *Vez::vytvor(){
    Vez * v = new Vez(barva);
    v->tahnuto = this->tahnuto;
    return v;
}
