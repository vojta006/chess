#include "pesec.h"
#include "sachovnice.h"
#include "main.h"
#include "dama.h"

Pesec::Pesec(bool color , int posX, int posY): Figurka(color,posX, posY){
    hodnota = 100;
    pos = tabulka = 0;
    mimo = nullptr;
}

bool Pesec::moznosti(std::vector<std::array<int,2>> &tahy,Sachovnice *s,std::vector<std::array<int,2>> minule){
    int dy = barva? -1:1; //kterym smerem jde

    if(!s->figurky[x][y+dy]){ //dopredu
        tahy.push_back({x,y+dy});
        if(!tahnuto && !s->figurky[x][y+2*dy]) //o dve pole
            tahy.push_back({x,y+2*dy});
    }

    if(x != 0 && s->figurky[x-1][y+dy] && s->figurky[x-1][y+dy]->barva !=barva) //vyhozeni doleva
        tahy.push_back({x-1,y+dy});

    if(x != 7 && s->figurky[x+1][y+dy] && s->figurky[x-1][y+dy]->barva !=barva) //vyhozeni doleva
        tahy.push_back({x+1,y+dy});

    //rozdil x souradnic je jedna ;y souradnice se rovnaji;minule bylo tahnuto o dve policka;figurka je pesec

    if(abs(minule[1][0] - x) == 1 && y == minule[1][1] && abs(minule[0][1]-minule[1][1]) == 2 &&  //brani mimochodem
            s->figurky[minule[1][0]][minule[1][1]]->pos == pos)
        tahy.push_back({minule[0][0],y+dy});
    return true;
}

bool Pesec::smery(int x, int y, int cx, int cy, bool Strel){
    if(Strel && y - cy == barva? 1:-1) return true;
    return false;
}

void Pesec::tazeno(int stareX, int stareY, int noveX, int noveY, std::array<int, 4> minule, Sachovnice *s,bool vraceni, bool ai){

    s->vypis();
    Figurka::tazeno(stareX, stareY, noveX, noveY,  minule, s,ai);

    s->vypis();

        if(!vraceni && abs(minule[1] - minule[3]) == 2 && s->figurky[minule[2]][minule[3]]->pos == pos && stareY == minule[3] && noveX == minule[0]){//podminky pro brani mimochodem
            mimo = s->figurky[minule[2]][minule[1]]; //stare y, nove x
            s->figurky[minule[2]][minule[1]] = nullptr; //smazani z pole figurek
            s->poloha[mimo->barva].erase(s->poloha[mimo->barva].begin()+mimo->index); //smazani z databaze poloh
        }
        else if(mimo && mimo->y == noveY && vraceni){
            if(!s->figurky[mimo->x][mimo->y]){
                s->figurky[mimo->x][mimo->y] = mimo;
                mimo->index = s->poloha[mimo->barva].size();
                s->poloha[mimo->barva].push_back({mimo->x,mimo->y});
                mimo = nullptr;
            }
        }
    s->vypis();



    if(!ai && (noveY==7||noveY==0)){ //pesec dojde na konec sachovnice
        aktivni = menu;
        menu->nactiPesec(barva,noveX,noveY); //vybrani figurky
    }

    if(ai && (noveY==7||noveY==0)){
        s->figurky[x][y] = new Dama(barva,x,y);
        //tady nejak doresit
    }
}
