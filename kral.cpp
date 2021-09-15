#include "kral.h"
#include "sachovnice.h"

Kral::Kral(bool color , int posX, int posY): Figurka(color,posX, posY){
    hodnota = 1000;
    pos = tabulka = 5;
}

bool Kral::moznosti(std::vector<std::array<int,2>> &tahy,Sachovnice *s,std::vector<std::array<int,2>> minTah){
    int smery[][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};                       //posledni tah
    int x,y;
    for(int i = 0; i<8;i++){ //projdou se vsechny smery, jestli nejsou obsazene
        x = this->x + smery[i][0];
        y = this->y + smery[i][1];
        if((x >= 0 && y >= 0 && x < 8 && y < 8) && (!s->figurky[x][y] || s->figurky[x][y]->barva!=barva))
            tahy.push_back({x,y});
    }

    if(!tahnuto){ //pridat podminky pro vez
        std::vector<std::array<int,2>> rosadaTahy;

        int pocitadlo = 0;
        for(int i = 0; i< 2; i++){
            //predalat
            if(s->figurky[x][i*7] && s->figurky[x][i*7]->tahnuto) continue;   //s vezi se pohnulo
            Figurka::moznosti(rosadaTahy,s,{{-1,0},{1,0}}); //jestli je volno mezi kralem a vezi
            rosadaTahy.push_back({x,y});
            if((int) rosadaTahy.size()==3+i) //lze projit az k vezi
                for(auto it :rosadaTahy){ //jestli neni sach
                    pocitadlo++;
                    if(jeSach(it[0],it[1],{minTah[0][0],minTah[0][1],minTah[1][0],minTah[1][1]},s)) break;
                    if(pocitadlo==3){ //jestlize na trech polickach neni sach, ulozi se tah do seznamu
                        tahy.push_back({x,i? y-2:y+2}); //rosada se ulozi do seznamu tahu
                        break;
                    }
                }
        }
    }
}

bool Kral::sachuje(int x, int y, int fx, int fy, Sachovnice *s){
    int dx = x>fx?-1:0,dy = y>fy?-1:0;
    dx = x<fx? 1:dx, dy = y<fy? 1:dy;
    Figurka *fig = NULL;
    int zx = x, zy = y; //zaloha

    while(x >= 0 && y >= 0 && x < 8 && y < 8) {
        x +=dx;
        y +=dy;
        if(s->figurky[x][y]){  //1 cerna 2 bila
            if(s->figurky[x][y]->barva != barva) //figurka opacne barvy
                fig = s->figurky[x][y];
            break;
        }
    }
    if(fig)
        return fig->smery(zx,zy,x,y, abs(zx-x) == abs(zy-y));

    //neni li odkaz na figurku, jako prvni je fig stejne barvy, nebo se doslo na konec sachovnice
    else return false;
}

bool Kral::jeSach(int x, int y,std::array<int,4> hst, Sachovnice *s){ //je konkretni policko ohrozeno figurkami protihrace?
    if(hst[2] == this->x || hst[3] == this-> y || abs(hst[2] - this->x) == abs(hst[3] - this->y))  //figurka, kterou bylo pohnuto
        if(sachuje(this->x,this->y,hst[2],hst[3],s)) return true;

    if(hst[0] == this->x || hst[1] == this->y || abs(hst[0] - this->x) == abs(hst[1] - this->y)) //figurka, ktera se nepohla (byla odkryta),nema smysl kun
        if(sachuje(this->x,this->y,hst[0],hst[1],s)) return true;

    if(hst[0] == this->x && hst[1] == this->y){ //pohnuto s kralem, zkontrolovat vsechny pozice, ktere mohou dosahnout
        int smery[][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
        for(int i = 0; i< 8; i++)
            if(sachuje(this->x,this->y,this->x+smery[i][0],this->y+smery[i][1],s)) return true;
        return false;
    }

    if((abs(this->x-hst[2])==2 && abs(this->y-hst[3]) == 1) || (abs(this->x-hst[2]) == 1 && abs(this->y-hst[3]) == 2)) //jestli je to kun, tak vrati true
        return s->figurky[hst[2]][hst[3]]->pos==1; //pos == 1 ma kun

    return false; //neni sach
}



//Figurka *Kral::sachuje(int x, int y, int sx, int sy,Sachovnice *s){
//    int dx = x==sx? 0: x>sx?-1:1;
//    int dy = y==sy? 0: y>sy?-1:1;
//    while(x<8 && x>0 && y<8 && y>0){
//        x+=dx;
//        y+=dy;
//        if(s->barvy[x][y]){
//            if(s->barvy[x][y] != barva+1)
//                return s->odkazy[x][y]->operator*();
//            else return nullptr;
//        }
//    }
//    return nullptr;
//}

//bool Kral::jeSach(int x, int y,std::array<int,4> hst, Sachovnice *s){ //je konkretni policko ohrozeno figurkami protihrace?
//    Figurka *sach = NULL;

//    if(hst[2] == this->x || hst[3] == this-> y){ //vez
//        sach = sachuje(this->x,this->y,hst[2],hst[3],s);
//        if(sach && smery(this->x,this->y, hst[2],hst[3],0)) return true;
//    }

//    if(hst[0] == this->x || hst[1] == this-> y){//vez
//        sach = sachuje(this->x,this->y,hst[0],hst[1],s);
//        if(sach && smery(this->x,this->y, hst[0],hst[1],0)) return true;
//    }

//    if(abs(hst[2] - this->x) == abs(hst[3] - this->y)){
//        sach = sachuje(this->x,this->y,hst[2],hst[3],s);
//        if(sach && smery(this->x,this->y, hst[2],hst[3],1)) return true;
//    }

//    if(abs(hst[0] - this->x) == abs(hst[1] - this->y)){ //figurka, ktera se nepohla (byla odkryta),nema smysl kun
//        sach = sachuje(this->x,this->y,hst[0],hst[1],s);
//        if(sach && smery(this->x,this->y, hst[0],hst[1],1)) return true;
//    }


//    if(hst[0] == this->x && hst[1] == this->y){ //pohnuto s kralem, zkontrolovat vsechny pozice, ktere mohou dosahnout
//        vector<array<int,2>> tahy;
//        moznosti(tahy,s,{});
//        for(auto t: tahy){
//            if(jeSach(tahy)) return true;
//        }
//    }

//    if((abs(x-hst[2])==2 && abs(y-hst[3]) == 1) || (abs(x-hst[2]) == 1 && abs(y-hst[3]) == 2)) //jestli je to kun, tak vrati true
//        return s->odkazy[hst[2]][hst[3]]->operator*()->pos==1; //pos == 1 ma kun

//    return false; //neni sach
//}




void Kral::tazeno(int stareX, int stareY, int noveX, int noveY,std::array<int,4> historie, Sachovnice *s,bool vraceni, bool ai){
    x = noveX;
    y = noveY;
    int vezX;

    if(abs(stareX - noveX) == 2){
        if(!tahnuto){ //rosada
            vezX = stareX>noveX? 0:7;
            s->posun(vezX,y,vezX? 5:3,y,historie); //posun veze
        }
        else{ //zpetna rosada
            vezX = stareX>noveX? 7:0; //cilove policko veze
            s->posun(vezX? 5:3,y,vezX,y,historie);
        }
    }
    tahnuto = true;
}
