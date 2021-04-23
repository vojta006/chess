#include "pesec.h"
#include "sachovnice.h"
#include "main.h"
#include "dama.h"

Pesec::Pesec(bool color):Figurka(color){
    hodnota = 100;
    pos = 0;
}

bool Pesec::moznosti(int x, int y, int cilX, int cilY, Sachovnice *s, bool kdoVola){ //kdoVola jednicka, kdyz jde o ohrozeni
    if(abs(cilX - x) > 1 || abs(cilY - y) > 2) return false;

    if(kdoVola){ if (x !=cilX && cilY-y == (barva? -1:1)) return true; return false;}  //kral se pta na sach

    if(cilY - y == (barva? -1:1)){ //o jedno pole dopredu
        if(cilX == x && !s->pole[cilX][cilY]) return true; //dopredu
        if(abs(cilX -x)==1 && s->pole[cilX][cilY] && s->pole[cilX][cilY]->barva!=barva) return true; //vyhozeni
    }

    if(!tahnuto && cilX == x && cilY - y == (barva? -2:2) && !s->pole[x][y + (barva?-1:1)] && !s->pole[x][y + (barva?-2:2)])
        return true; //chozeni o dve pole

    if(abs(cilX - x) == 1 && y == (barva? 3:4) && cilY == (barva? 2:5) && s->pole[cilX][y]  //brani mimochodem
            && s->minule[s->Hloubka][0]==cilX && s->minule[s->Hloubka][1] == y){
        return true;
    }

    return false;
}

void Pesec::tazeno(int stareX, int stareY, int noveX, int noveY, Sachovnice *s, bool ai){
    if(abs(stareY - noveY) == 2) s->minule[s->Hloubka+1][0] = noveX , s->minule[s->Hloubka+1][1] = noveY; //pesec sel o dve policka
    if(stareX!=noveX && ((barva && noveX == 3)||(!barva && noveX ==5)) && s->pole[noveX][stareY] && s->minule[s->Hloubka][0]==noveX && s->minule[s->Hloubka][1]==stareY){
        s->mimochodem[s->Hloubka] = s->pole[noveX][stareY];
        s->pole[noveX][stareY]=NULL;
        //volani++;
    }
    tahnuto = true;
    if(!ai && (noveY==7||noveY==0)){ //pesec dojde na konec sachovnice
        aktivni = menu;
        menu->nactiPesec(barva,noveX,noveY);
    }
    if(ai && (noveY==7||noveY==0)) {
        s->pole[noveX][noveY] = new Dama(barva);
    }
}

Figurka *Pesec::vytvor(){
    Pesec *p =new Pesec(barva);
    p->tahnuto=this->tahnuto;
    return p;
}
