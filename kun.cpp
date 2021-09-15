#include "kun.h"
#include "sachovnice.h"

Kun::Kun(bool color , int posX, int posY): Figurka(color,posX, posY){
    hodnota = 310;
    pos = tabulka = 1;
}

bool Kun::moznosti(std::vector<std::array<int,2>> &tahy,Sachovnice *s,std::vector<std::array<int,2>> nepouzito){
    int dx,dy,smery [2] = {1,2},nasobky [][2]= {{-1,-1},{-1,1},{1,-1},{1,1}};
    for(int i = 0; i< 4;i++){
        dx = smery[0]*nasobky[i][0];
        dy = smery[1]*nasobky[i][1];

        if(x+dx>=0 && x+dx <8 && y+dy>=0 && y+dy<8 && (!s->figurky[x+dx][y+dy] or s->figurky[x+dx][y+dy]->barva != barva))
            tahy.push_back({x+dx,y+dy});

        if(x+dy>=0 && x+dy <8 && y+dx>=0 && y+dx<8 && (!s->figurky [x+dy][y+dx] or s->figurky [x+dy][y+dx]->barva != barva ))
            tahy.push_back({x+dy,y+dx});
    }
    return true;
}

bool Kun::smery(int x, int y, int cx, int cy, bool vezStrel){
    return false;
}
