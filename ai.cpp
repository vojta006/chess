#include "ai.h"
#include "main.h"
#include <vector>

void ai(){
    Sachovnice *s = sachovnice;
    volani=0;
    srand(time(NULL));
    long long int cas = SDL_GetTicks();
    s->tahy.clear();
    s->generujTahy(MAX_HLOUBKA,s->tah?-1e9:1e9,0);
    printf("AI time: %d  ms.\n",SDL_GetTicks()-cas);
    printf("Evaluated positions %d.\n",volani);
    fflush(stdout);
    int max_hodnoceni =  s->tah?-1e9:1e9;
    std::vector<int> nej_tahy;
    int skore;
    bool stop = false;

    while(s->tahy.size()){
        for(int i = 0; i<(int)s->tahy.size();i++){
            if((s->tah && s->tahy[i][4]>=max_hodnoceni)||(!s->tah && s->tahy[i][4]<=max_hodnoceni)){
                if(s->tahy[i][4]!=max_hodnoceni) nej_tahy.clear();
                max_hodnoceni = s->tahy[i][4];
                nej_tahy.push_back(i);
            }
        } //z nej tahu vybrat takovy, ktery nezpusobi tri stejne tahy za sebou
        int n = rand()%nej_tahy.size();
        s->posun(s->tahy[nej_tahy[n]][0],s->tahy[nej_tahy[n]][1],s->tahy[nej_tahy[n]][2],s->tahy[nej_tahy[n]][3],s->minX,s->minY,1);
        skore  = s->hodnoceni();

        for(int i = s->historieTahy.size();i!=(int)s->historieTahy.size()-20;i-=2){
            if(skore != s->historieTahy[i][4]) stop = true;
        }
        if(stop) break;
        else {
            s->posun(s->tahy[nej_tahy[n]][2],s->tahy[nej_tahy[n]][3],s->tahy[nej_tahy[n]][0],s->tahy[nej_tahy[n]][1],s->minX,s->minY,1);
            s->tahy.erase(s->tahy.begin()+nej_tahy[n]);
        }
    }

    s->dalsiTah();
}

//nedovolit zahrat tri stejne tahy

