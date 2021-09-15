#include "sachovnice.h"
#include "main.h"
#include "SDL/SDL.h"
#include <SDL/SDL_image.h>
#include "pesec.h"
#include "strelec.h"
#include "kun.h"
#include "vez.h"
#include "kral.h"
#include "dama.h"

Sachovnice::Sachovnice(){
    figX = figY = 8;
    Hloubka  = pocetTahu  = hraniOnline = histVrat = klikPosun = 0;
    tah = BILAFIG;
    SDL_WM_SetCaption("Chess",NULL);
    Menu = IMG_Load("figures/menu.png");
    Bila = IMG_Load("figures/bila.png");
    pat = IMG_Load("figures/remiza.png");
    sachovnice = IMG_Load("figures/chess.jpg");
    obrysM = IMG_Load("figures/obrysModra.png");
    obrysZ = IMG_Load("figures/obrysZluta.png");
    matBila = IMG_Load("figures/bily_vyhra.png");
    obrysC = IMG_Load("figures/obrysCervena.png");
    matCerna = IMG_Load("figures/cerny_vyhra.png");
    figObrazky = IMG_Load("figures/figurky_mensi.png");
    generuj = true;
    okraj  = 20;
    policko = 80;
    diblik = nullptr;
    historie.push_back({0,0,0,0}); //vychozi pozice

    memset(figurky,0,sizeof(figurky));

    for(int  i = 0; i < 8; i++){
           figurky[i][1] = new Pesec(CERNAFIG,i,1);
           figurky[i][6] = new Pesec(BILAFIG,i,6);
    }

    for(int i = 0; i< 2; i++){
        for(int j = 0; j < 2; j++){
            figurky[j? 7:0][i*7] = new Vez(i,j? 7:0,i*7);
            figurky[j? 6:1][i*7] = new Kun(i,j? 6:1,i*7);
            figurky[j? 5:2][i*7] = new Strelec(i,j? 5:2,i*7);
        }
        figurky[3][i*7] = new Dama(i,3,i*7);
        figurky[4][i*7] = new Kral(i,4,i*7);
    }


    int c,b;
    b = c = 0;
    for(int i = 0; i<8;i++) for(int j = 0; j<8;j++){
        if(!figurky[i][j]) continue;
        if(figurky[i][j]->barva == CERNAFIG){ figurky[i][j]->index = b; b++;   poloha[CERNAFIG].push_back({i,j});}
        else if(figurky[i][j]->barva == BILAFIG){ figurky[i][j]->index = c; c++;   poloha[BILAFIG].push_back({i,j});}
        printf(" poloha ve figurce: %d,%d  figurky[%d][%d]->index = %d \n",figurky[i][j]->x,figurky[i][j]->y, i,j,figurky[i][j]->index);
        fflush(stdout);
    }

    kralove[0] = figurky[4][0];
    kralove[1] = figurky[4][7];
}

void Sachovnice::kresli(){
    if(diblik)
        diblik->posta(); //kontrola, jestli neco neprislo
    if(!prekresli) return;
    prekresli = false;
    SDL_Rect dst,src;

    SDL_FillRect(screen,NULL,0); //smazani obrazovky
    SDL_BlitSurface(sachovnice,NULL,screen,0); //kresleni sachovnice

    if(klikPosun){
        dst.x = figX*policko+okraj, dst.y = figY*policko+okraj;
        SDL_BlitSurface(obrysZ,NULL,screen,&dst); //oznaceni figurky na tahu

        for(int i=0; i<(int) tahy.size(); i++) //kresleni moznych tahu
            if(tahy[i][0]== figX && tahy[i][1]== figY){
                dst.x = tahy[i][2]*policko+okraj, dst.y= tahy[i][3]*policko+okraj;
                SDL_BlitSurface(obrysM,NULL,screen,&dst);
            }
    }

    src.h = src.w = 80;

    for(int i = 0; i < 8; i++) for(int j = 0; j < 8; j++){
        if(!figurky[i][j]) continue;
        dst.x = figurky[i][j]->x*policko+okraj;
        dst.y = figurky[i][j]->y*policko+okraj;
        src.x = figurky[i][j]->tabulka*policko;
        src.y = figurky[i][j]->barva?0:policko;
        SDL_BlitSurface(figObrazky,&src,screen,&dst);
    }

    if(sach){ //kdyz je sach, kresli se cerveny obrys okolo krale
        dst.x = okraj + policko*kralove[tah]->x;
        dst.y = okraj + policko*kralove[tah]->y;
        SDL_BlitSurface(obrysC,NULL,screen,&dst);
    }

    //dst.x = 680, dst.y = 340 - hodnoceni()/5;
    SDL_BlitSurface(Bila,NULL,screen,&dst); //kresleni hodnoceni

    dst.x = 740,dst.y = 10;
    SDL_BlitSurface(Menu,NULL,screen,&dst); //kresleni tlacitka menu

    if(generuj){ //vytvari se nove tahy
        generuj = false;
        tahy.clear();
        generujTahy(0,tah?-1e9:1e9,hodnoceni(),historie[histVrat]);
        if(!tahy.size()){ //konec hry
            hraj = false;
            dst.x = 720, dst.y = 200;
            if(sach) SDL_BlitSurface(tah? matBila:matCerna,NULL,screen,&dst); //policko s kralem je sachovane
            else SDL_BlitSurface(pat,NULL,screen,0);
        }
    }
    SDL_Flip(screen);
}

void Sachovnice::klik(int MysX, int MysY){
    int x = (MysX-okraj)/policko;
    int y = (MysY-okraj)/policko;
    if(x<8 && y<8 && x>=0 && y>=0){
        if(klikPosun){ //jiz je oznacena figurka
            bool posunout=false;

            for(auto i:tahy)
                if(i[0]== figX && i[1]== figY && i[2]==x && i[3]==y) {posunout = true; break;}

            if(posunout){ //posun figurky
                posun(figX,figY,x,y,historie[histVrat]);
                dalsiTah(1); //jestli se ma tah odeslat
                sach = kralove[tah]->jeSach(figX,figY,historie[histVrat],this);
                historie.push_back({figX,figY,x,y}); //ulozeni posledniho tahu do historie
            }
            else{ //jiz vybrana firugka, vybrani jineho pole, kam nelze vstoupit
                if(figX == x && figY == y) klikPosun = false;
                else if (figurky[x][y] && figurky[x][y]->barva == tah)
                    figX = x, figY = y; //jina vlastni figurka
                else
                    klikPosun = false, figX  = kralove[tah]->x, figY = kralove[tah]->y; //nastaveni mimo souradnice
            }
            prekresli = true;
        }
        else if(figurky[x][y] && figurky[x][y]->barva == tah){ //vybrani vlastni figurky; kdyz je tah 1, tahne bila; v bit tabulce je bila 2 a cerna 1. Proto se pricita 1.
            figX = x, figY = y;
            klikPosun = true;
            prekresli = true;
        }
    }
    else if(MysX>740 && MysY>10 && MysX<840 && MysY<60){ aktivni = menu; prekresli = true;} //obrazek menu
}

void Sachovnice::dalsiTah(bool posli){ //informuj diblika o tahu
    tah =!tah;
    prekresli = generuj = true;
    klikPosun = sach =  false;
    histVrat++;
    if(hraniOnline && posli) diblik->odeslatTah(); //informovat server
}

int Sachovnice::hodnoceni(){
    int hodnota = 0;

    for(auto j: poloha[1]){ //bile figurky
        hodnota += figurky[j[0]][j[1]]->hodnota;
        hodnota += hodnoty[figurky[j[0]][j[1]]->pos][j[0]][j[1]];
    }

    for(auto j:poloha[0]){ //cerne figurky
        hodnota -= figurky[j[0]][j[1]]->hodnota;
        hodnota -= hodnoty[figurky[j[0]][j[1]]->pos][j[0]][j[1]];
    }
    return hodnota;
}

int Sachovnice::hodnoceni(int x, int y, int cx, int cy, int stare, Figurka *vyhozena){
    return stare + (vyhozena? (vyhozena->barva? -1:1 * (vyhozena->hodnota+hodnoty[vyhozena->pos][vyhozena->x][vyhozena->y])):0) //odecteni vyhozene figurky
        - hodnoty[figurky[cx][cy]->pos][x][y] //odecteni stare pozice
                + hodnoty[figurky[cx][cy]->pos][cx][cy];  //pricteni nove pozice
}


Sachovnice::~Sachovnice(){
    if(diblik) diblik->~Komunikace();
}

void Sachovnice::posun(int x, int y, int cilX, int cilY, array<int, 4> historie){
    if(figurky[cilX][cilY]){ //pri volani posun z generujTahy se figurka vyhodi uz drive
        delete figurky[cilX][cilY];
        poloha[!tah].erase(poloha[!tah].begin()+figurky[cilX][cilY]->index); //smazani vyhozene figurky
    }

    figurky[cilX][cilY] = figurky[x][y];
    figurky[x][y] = nullptr;

    figurky[cilX][cilY]->tazeno(x,y,cilX,cilY,historie,this,1);
}

void Sachovnice::vypis(){
    int j = 0;
    for(int i = 0; i<16; i++){
        if(poloha[0][i][0] != fig[0][i][0]){
            j = 1;
            fig[0][i][0] = poloha[0][i][0] ;
        }

        if(poloha[0][i][1] != fig[0][i][1]){
            j = 2;
            fig[0][i][1] = poloha[0][i][1];
        }

        if(poloha[1][i][0] != fig[1][i][0]){
            j=3;
            fig[1][i][0] = poloha[1][i][0] ;
        }

        if(poloha[1][i][1] != fig[1][i][1]){
            j=4;
            fig[1][i][1] = poloha[1][i][1] ;
        }
    }
    if(j)
        int b = 4;
}

int Sachovnice::generujTahy(int max_hloubka, int srovnani,int hodnota,std::array<int,4> hst){ //material je zbytecny
    int aktualni = tah?-1e9:1e9 , nej = aktualni;
    bool tahnuto,nalezenTah = false;
    int x,y,cilX, cilY;
    Figurka *zaloha; //ulozeni vyhozene figurky

    vector<array<int,2>> tahy; //mozne tahy figurky, ktera se zkousi

    vypis();
    for(auto pol: poloha[tah]){ //ktera barva je na tahu

        tahy.clear(); //smaze tahy
        x = pol[0];
        y = pol[1];
        vypis();
        figurky[x][y]->moznosti(tahy,this,{{hst[0],hst[1]},{hst[2],hst[3]}}); //vygenerovani tahu //generovani tahu, posledni argument jsou souradnice minuleho pohnuti figurkou
        vypis();

        for(auto posun:tahy){ //zkouseni vygenerovanych tahu
            vypis();
            cilX = posun[0];
            cilY = posun[1];
            vypis();
            tahnuto = figurky[x][y]->tahnuto; //zaloha na tahnuto
            vypis();
            if(figurky[cilX][cilY]){ //zalohovani figurky, ktera bude vyhozena
                zaloha = figurky[cilX][cilY];
                vypis();
                poloha[!tah].erase(poloha[!tah].begin() + zaloha->index); //smaze prvek vectoru
                vypis();
            }
            else zaloha = nullptr;
            vypis();

            figurky[cilX][cilY] = figurky[x][y];
            figurky[x][y] = nullptr;
            vypis();

            figurky[cilX][cilY]->tazeno(x,y,cilX,cilY,{hst[0],hst[1],hst[2],hst[3]},this,false,true);
            vypis();
            if(not kralove[tah]->jeSach(cilX,cilY,{hst[0],hst[1],hst[2],hst[3]},this)){ //kralove tah se pise proto, ze se mohlo pohnout s kralem, a tudiz neni jasne, jestli pouzit x nebo cilX
                if(Hloubka == max_hloubka)
                    aktualni = hodnoceni(x,y,cilX,cilY,hodnota,zaloha);
                else{
                    tah=!tah; Hloubka++; //jde se do hloubky
                    aktualni = generujTahy(max_hloubka,nej,hodnoceni(x,y,cilX,cilY,hodnota,zaloha),{x,y,cilX,cilY});
                    tah=!tah; Hloubka--;
                }
                if(!Hloubka) //ulozeni tahu do seznamu pouzitelnych tahu
                    this->tahy.push_back({x,y,cilX,cilY,aktualni});
            }
            vypis();
            //vraceni figurky
            figurky[x][y] = figurky[cilX][cilY];
            figurky[x][y]->tazeno(cilX,cilY,x,y,{hst[0],hst[1],hst[2],hst[3]},this,true,true);
            vypis();
            if(zaloha){
                figurky[cilX][cilY] = zaloha;
                poloha[!tah].push_back({cilX,cilY});
            }
            figurky[x][y]->tahnuto = tahnuto;

            vypis();

            if((tah && nej < aktualni) || (not tah && nej > aktualni))  nej = aktualni, nalezenTah = true;

            if((tah && srovnani < aktualni) || (not tah && srovnani > aktualni)) //alfa beta pruning
                if(Hloubka)
                    return aktualni;
        }
    }

    if(!nalezenTah) //zadny tah, pat, nebo mat
        if(not kralove[tah]->jeSach(cilX,cilY,{hst[0],hst[1],hst[2],hst[3]},this)) return -nej; //neni sach; je pat

    return nej;
}
