#include "kun.h"
#include "sachovnice.h"
#include "main.h"

Kun::Kun(bool color): Figurka(color){
    hodnota = 310;
    pos = 1;
}

bool Kun::moznosti(int x, int y, int cilX, int cilY, Sachovnice *s,bool kdoVola){
    if((abs(x-cilX)==2 && abs(y-cilY) == 1) || (abs(x-cilX) == 1 && abs(y-cilY) == 2)){ //souradnice jsou v mezich
        if(kdoVola) return true;  //policka konem ohrozena
        if(!s->pole[cilX][cilY] || s->pole[cilX][cilY]->barva!=barva) return true; //pole, kam muze kun vstoupit
    }
    return false;
}

Figurka *Kun::vytvor(){
    Kun* v=new Kun(barva);
    v->tahnuto=this->tahnuto;
    return v;
}
