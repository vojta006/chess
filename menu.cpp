#include <SDL/SDL_image.h>
#include "menu.h"
#include "main.h"
#include "strelec.h"
#include "vez.h"
#include "dama.h"
#include "kun.h"

Menu::Menu()
{
    polroz=80; //sachovnice->polroz;
    stav = vybirani = 0;
    prekresli = true;
    MPozadi = IMG_Load("figures/modrePozadi.png");
    figurky = sachovnice->figObrazky;
    server =  IMG_Load("figures/server.png");
    zpet = IMG_Load("figures/zpet.png");
    ukoncit = IMG_Load("figures/ukoncitServer.png");
    vyberMistnost = IMG_Load("figures/vyberMistnost.png");
    mistnosti = IMG_Load("figures/mistnost.png");
    konec = IMG_Load("figures/konec.png");
}

void Menu::PesecKlik(int MysX, int MysY){ //vybirani pesaka
    int x=MysX/polroz;
    int y=MysY/polroz;

    y = pesecBarva?y:7-y;
    Sachovnice *s = sachovnice;
    bool vybrano = true;

    if(x==pesecX){
        switch(y) {
        case 0:
            s->figurky[pesecX][pesecY] = new Dama(pesecBarva,pesecX,pesecY);
            break;
        case 1:
            s->figurky[pesecX][pesecY] = new Vez(pesecBarva,pesecX,pesecY);
            break;
        case 2:
            s->figurky[pesecX][pesecY] = new Strelec(pesecBarva,pesecX,pesecY);
            break;
        case 3:
            s->figurky[pesecX][pesecY] = new Kun(pesecBarva,pesecX,pesecY);
            break;
        default:
            vybrano = false;
        }
        if(vybrano){
            aktivni = sachovnice;
        }
    }
}


void Menu::klik(int MysX, int MysY){
    switch (stav) {
    case 0:
        menuKlik(MysX,MysY);
        break;
    case 1:
        PesecKlik(MysX,MysY);
        break;
    case 2:
        konecKlik(MysX,MysY);
        break;
    default:
        printf("neocekavany stav");
    }
}

void Menu::menuKlik(int MysX, int MysY){
    if(MysX<80 && MysY<80){ aktivni = sachovnice; vybirani = false; prekresli = true;} //obrazek zpet

    if(!vybirani && MysX > 100 && MysX <280 && MysY > 100 && MysY<140){
        if(!sachovnice->diblik){ //poprve vybran server
            sachovnice->diblik = new Komunikace(sachovnice);
            vybirani = true;
        }
        else if(!sachovnice->hraniOnline){ //po nekolikate vybran server
            vybirani = true;
            sachovnice->hraniOnline = true;
        }
        else {vybirani = false;sachovnice->hraniOnline = false;}
        prekresli = true;
    }
    if(vybirani && MysX >=250 && MysX<=290){
        if(MysY>= 200 && MysY< 240) sachovnice->diblik->mistnost = 'a';
        else if(MysY>= 240 && MysY< 280) sachovnice->diblik->mistnost = 'b';
        else if(MysY>= 280 && MysY< 320) sachovnice->diblik->mistnost = 'c';
        else if(MysY>= 320 && MysY< 360) sachovnice->diblik->mistnost = 'd';
        if(MysY>= 200 && MysY< 360){
            aktivni = sachovnice;
            sachovnice->hraniOnline = true;
            sachovnice->diblik->hrani=true;
            vybirani = false;
            prekresli = true;
        }
    }
}


void Menu::menuKresli(){
    SDL_FillRect(screen,NULL,0); //smaz
    SDL_Rect dst;
    dst.x = dst.y = 0;
    SDL_BlitSurface(zpet,NULL,screen,&dst);
    dst.x = dst.y = 100;
    if(!vybirani){
        if(!sachovnice->hraniOnline)
            SDL_BlitSurface(server,NULL,screen,&dst); //hrani pres server
        else SDL_BlitSurface(ukoncit,NULL,screen,&dst);
    }
    if(vybirani){
        dst.y = 200;
        SDL_BlitSurface(vyberMistnost,NULL,screen,&dst);
        dst.x = 250;
        SDL_BlitSurface(mistnosti,NULL,screen,&dst);
    }
    SDL_Flip(screen);
}


void Menu::kresli(){
    if(!prekresli)  return;
    prekresli = false;
    switch (stav){
    case 0:
        menuKresli();
        break;
    case 1: //pesec je na konci
        pesecKresli();
        break;
    case 2:
        konecHry();
        break;
    }
}

void Menu::pesecKresli(){ //20 je sirka okraje
    int pos = pesecBarva?0:4;
    SDL_Rect dst,src;
    dst.x = pesecX*polroz+20;
    src.h = src.w = polroz;
    src.y = pesecBarva? 0:polroz;

    for(int i = 0; i<4;i++,pos++){
        dst.y = pos*polroz+20;
        src.x = polroz *(pesecBarva? 4-i:i+1);
        SDL_BlitSurface(MPozadi,NULL,screen,&dst); //modre pozadi
        SDL_BlitSurface(figurky,&src,screen,&dst); //figurky
    }
    SDL_UpdateRect(screen, 0, 0, 0, 0);
}

void Menu::nactiPesec(bool barva, int x, int y){ //ulozi pozici a barvu pesce
    Sachovnice *s = sachovnice;
    pesecX=x;
    pesecY=y;
    stav = 1; // zmeni stav menu, aby se kreslil pesec na konci
    pesecBarva = barva;
}

void Menu::konecKlik(int x, int y){
    if(x<80 && y<80){
        aktivni = sachovnice;
        prekresli = true;
    }
    if(x >100 && y > 20 && x<223 && y <52 ){
        sachovnice->~Sachovnice();
        SDL_Quit();
        exit(0);
    }
}

void Menu::konecHry(){ //konec hry
    if(stav!= 2){
        stav = 2;
        aktivni = ::menu;
    }
    SDL_FillRect(screen,NULL,0);

    SDL_Rect dst;
    dst.x = dst.y = 0;
    SDL_BlitSurface(zpet,NULL,screen,&dst);

    dst.x = 100;
    dst.y = 20;
    SDL_BlitSurface(konec,NULL,screen,&dst);
    SDL_Flip(screen);
}
