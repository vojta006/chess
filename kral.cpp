#include "kral.h"
#include "sachovnice.h"
#include "main.h"

Kral::Kral(bool color): Figurka(color){
    hodnota = 1000;
    pos = tabulka = 5;
}

bool Kral::moznosti(int x, int y, int cilX, int cilY, Sachovnice *s,bool kdoVola){
    if(abs(cilX-x)<=1 && abs(cilY-y)<=1){
        if(kdoVola) return true;
        if(!kdoVola && (!s->pole[cilX][cilY]||s->pole[cilX][cilY]->barva!=barva)) return true;
    }
    if(!kdoVola && !tahnuto && abs(cilX - x)==2 && y==cilY){ //rosada
        int vezX = cilX<x? 0:7;
        if(!s->pole[vezX][y] || s->pole[vezX][y]->tahnuti()) return false; //tahnuto s vezi
        int dx = cilX<x?-1:1;
        while(x != cilX+dx){
            if((x+dx != vezX && s->pole[x+dx][y]) || pozorSach(x,y,s)) return false;
            x+=dx;
        }
        return true;
    }
    return false;
}

bool Kral::pozorSach(int kX, int kY, Sachovnice *s){ //je konkretni policko ohrozeno figurkami protihrace?
    for(int  x = 0; x < 8; x++)
        for(int y = 0; y < 8; y++)
            if(s->pole[x][y] && s->pole[x][y]->barva!=barva) //figurka cizi barvy
                if(s->pole[x][y]->moznosti(x,y,kX,kY,s,1)) return true;

    return false;
}


Figurka *Kral::vytvor(){return new Kral(*this);};

void Kral::tazeno(int stareX, int stareY, int noveX, int noveY, Sachovnice *s, bool ai){
    if(barva) //zmena polohy krale
        s->BkX=noveX,s->BkY=noveY;
    else
        s->CkX=noveX,s->CkY=noveY;

    tahnuto = true;

    bool rosada = false;
    if(stareX-noveX==2){ //vlevo rosada, vraceni z prave rosady
        if(s->rosada[barva]) //posun rosady z prava
            stareX = 5, noveX = 7;
        else stareX = 0, noveX = 3;

        s->rosada[barva] = !s->rosada[barva];
        s->posun(stareX,stareY,noveX,noveY,s->minule[s->Hloubka][0],s->minule[s->Hloubka][1]);
        if(!s->rosada[barva]) s->pole[noveX][noveY]->tahnuto=false; //vraceni rosady
        rosada = true;
    }

    if(stareX-noveX==-2 && !rosada){  //vpravo
        if(s->rosada[barva]) //vraceni rosady zleva
            stareX = 3, noveX = 0;
        else
            stareX=7,noveX=5;

        s->rosada[barva] = !s->rosada[barva];
        s->posun(stareX,stareY,noveX,noveY,s->minule[s->Hloubka][0],s->minule[s->Hloubka][1]);
        if(!s->rosada[barva]) s->pole[noveX][noveY]->tahnuto=false; //vraceni rosady
    }
}
