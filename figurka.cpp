#include "figurka.h"
#include "sachovnice.h"
#include "SDL/SDL.h"
#include <SDL/SDL_image.h>
#include "main.h"

Figurka::Figurka(bool color,int posX, int posY):barva(color)
{
    this-> index = index;
    x = posX;
    y = posY;
    tahnuto = false;
}

void Figurka::tazeno(int stareX, int stareY, int noveX, int noveY, std::array<int, 4> historie, Sachovnice *s,bool vraceni, bool ai){
    x = noveX;
    y = noveY;
    tahnuto=true;
    s->vypis();
    printf("%d, %d", index, barva);
    fflush(stdout);
    s->poloha[barva][index] = {x,y};
    s->vypis();
}

bool Figurka::jeSach(int x, int y, std::array<int, 4> historie, Sachovnice *s){}

bool Figurka::moznosti(std::vector<std::array<int, 2> > &tahy, Sachovnice *s, std::vector<std::array<int, 2> > smery){
    int x,y;
    for(auto i:smery){
        x = this->x+i[0];
        y = this->y+i[1];
        while(x >= 0 && y >= 0 && x < 8 && y < 8){
            x+=i[0];
            y+=i[1];
            if(s->figurky[x][y]){
                if(s->figurky[x][y]->barva != barva) //narazilo se na figurku cizi barvy
                    tahy.push_back({x,y});
                break;
            }
            tahy.push_back({x,y});
        }
    }
    return tahy.size();
}

bool Figurka::smery(int x, int y, int cx, int cy,bool vezStrel){}
