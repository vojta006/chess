#include "ai.h"
#include "main.h"
#include <vector>

void ai(){

    Sachovnice *s = sachovnice;
    if(s->diblik){
        if(s->diblik->tah == 2) s->diblik->tah = s->tah;
        else if(s->diblik->tah != s->tah) return;
    }
    volani=0;
    srand(time(NULL));
    int cas = SDL_GetTicks();
    printf("pocet tahu %d\n",(int)s->tahy.size());
    fflush(stdout);
    s->tahy.clear();
    s->generujTahy(MAX_HLOUBKA,s->tah? -1e9:1e9,s->hodnoceni(),s->historie[s->histVrat]);
    printf("AI time: %d  ms.\n",SDL_GetTicks()-cas);
    printf("Evaluated positions %d.\n",volani);
    fflush(stdout);
    long int max_hodnoceni =  s->tah?-1e10:1e10;
    std::vector<int> nej_tahy;

    for(int i = 0; i<(int)s->tahy.size();i++){
        if((s->tah && s->tahy[i][4]>=max_hodnoceni)||(!s->tah && s->tahy[i][4]<=max_hodnoceni)){
            if(s->tahy[i][4]!=max_hodnoceni) nej_tahy.clear();
            max_hodnoceni = s->tahy[i][4];
            nej_tahy.push_back(i);
        }
    } //z nej tahu vybrat takovy, ktery nezpusobi tri stejne tahy za sebou
    int n = rand()%nej_tahy.size();
    s->posun(s->tahy[nej_tahy[n]][0],s->tahy[nej_tahy[n]][1],s->tahy[nej_tahy[n]][2],s->tahy[nej_tahy[n]][3],s->historie[s->histVrat]);
    s->dalsiTah(1);
}

//nedovolit zahrat tri stejne tahy

