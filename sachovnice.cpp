#include "sachovnice.h"
#include "main.h"
#include "strelec.h"
#include "vez.h"
#include "dama.h"
#include "kral.h"
#include "pesec.h"
#include "kun.h"
#include "SDL/SDL.h"
#include <SDL/SDL_image.h>

Sachovnice::Sachovnice(){
    figX = figY = 8;
    CkY = kresli_hodnoceni = Hloubka  = pocetTahu =  koncovka =0;
    minX = minY= 3;
    histVrat = -1;
    tah = BILAFIG;
    SDL_WM_SetCaption("Chess",NULL);
    matBila = IMG_Load("figures/bily_vyhra.png");
    matCerna = IMG_Load("figures/cerny_vyhra.png");
    sachovnice = IMG_Load("figures/chess.jpg");
    pat = IMG_Load("figures/remiza.png");
    obrysM = IMG_Load("figures/obrysModra.png");
    obrysZ = IMG_Load("figures/obrysZluta.png");
    obrysC = IMG_Load("figures/obrysCervena.png");
    Bila = IMG_Load("figures/bila.png");
    BkX=CkX=4; BkY=7; //bila kral Y,X
    generuj =true;
    okraj  = 20;
    policko = 80;

    for(int a= 0; a<8;a++) for(int b= 0;b<8;b++) pole[a][b]=NULL;

    for(int j=0;j<8;j++) //zajistit pat pri nedostatecnem poctu figur
    {
        pole[j][1]=new Pesec(CERNAFIG);
        pole[j][6]=new Pesec(BILAFIG);
    }
    for(int k=0;k<2;k++){
        pole[0][7*k]=new Vez(BILAFIG*k);
        pole[1][7*k]=new Kun(BILAFIG*k);
        pole[2][7*k]=new Strelec(BILAFIG*k);
        pole[7][7*k]=new Vez(BILAFIG*k);
        pole[6][7*k]=new Kun(BILAFIG*k);
        pole[5][7*k]=new Strelec(BILAFIG*k);
        pole[4][7*k]=new Kral(BILAFIG*k);
        pole[3][7*k]=new Dama(BILAFIG*k);
    }
}

void Sachovnice::kresli(){
    if(!prekresli) return;
    prekresli = false;
    SDL_Rect dst,src;

    SDL_FillRect(screen,NULL,0);
    SDL_BlitSurface(sachovnice,NULL,screen,0);
    if(klikPosun){ //kresleni moznych tahu
        dst.x = figX*policko+okraj, dst.y = figY*policko+okraj;
        SDL_BlitSurface(obrysZ,NULL,screen,&dst);
        for(int i=0; i<(int) tahy.size(); i++)
            if(tahy[i][0]== figX && tahy[i][1]== figY){
                dst.x = tahy[i][2]*policko+okraj, dst.y= tahy[i][3]*policko+okraj;
                SDL_BlitSurface(obrysM,NULL,screen,&dst);
            }
    }

    src.h = src.w = 80;
    for(int a= 0; a<8;a++) //kresleni figurek
        for(int b= 0;b<8;b++)
            if(pole[a][b]){
                dst.x = a*policko+okraj, dst.y= b*policko+okraj;
                src.x = pole[a][b]->pos*policko;
                src.y = pole[a][b]->barva?0:policko;
                SDL_BlitSurface(figurky,&src,screen,&dst);
            }

    if(sach){
        dst.x = okraj+policko*(tah? BkX:CkX), dst.y = okraj+policko*(tah? BkY:CkY);
        SDL_BlitSurface(obrysC,NULL,screen,&dst);
    }

    dst.x = 680;
    dst.y = 340 - hodnoceni()/5;
    SDL_BlitSurface(Bila,NULL,screen,&dst);

    if(generuj){ //vytvari se nove tahy
        generuj = false;
        tahy.clear();
        generujTahy(0,tah?-1e9:1e9,0);
        pridej();
        if(!tahy.size()){
            hraj = false;
            SDL_Rect dst;
            dst.x = 720, dst.y = 200;
            if(tah && pole[BkX][BkY]->pozorSach(BkX,BkY,this))  SDL_BlitSurface(matCerna,NULL,screen,&dst);
            else if(!tah && pole[CkX][CkY]->pozorSach(CkX,CkY,this))  SDL_BlitSurface(matBila,NULL,screen,&dst);
            else  SDL_BlitSurface(pat,NULL,screen,0);
        }
    }
    SDL_Flip(screen);
}

void Sachovnice::klik(int MysX, int MysY){
    int x = (MysX-okraj)/policko;
    int y = (MysY-okraj)/policko;
    if(x<8 && y<8 && x>=0 && y>=0){
        if(klikPosun){
            bool mozno=false;

            for(int i=0; i<(int)tahy.size(); i++) //na vybrane policko lze vstoupit
                if(tahy[i][0]== figX && tahy[i][1]== figY && tahy[i][2]==x && tahy[i][3]==y) {mozno = true; break;}

            if(mozno){ //posun figurky
                posun(figX,figY,x,y,minule[0][0],minule[0][1]);
                rosada[tah] = false;
                dalsiTah();
                sach = pole[tah? BkX:CkX][tah? BkY:CkY]->pozorSach(tah? BkX:CkX,tah? BkY:CkY,this);
            }
            else{ //jiz vybrana firugka, vybrani jineho pole, kam nelze vstoupit
                if(figX==x && figY== y) klikPosun = false;
                else if (pole[x][y] && pole[x][y]->vratbarvu()==tah) figX = x, figY = y; //jina vlastni figurka
                else figX = figY = 17;
            }
            prekresli = true;
        }
        else if(pole[x][y] && pole[x][y]->vratbarvu()==tah){ //vybrani vlastni figurky
            figX = x, figY = y;
            klikPosun = true;
            prekresli = true;
        }
    }
}

void Sachovnice::dalsiTah(){
    tah =!tah;
    prekresli = generuj = true;
    klikPosun = sach =  false;
    kresli_hodnoceni = hodnoceni();
    pocetTahu++;
    if(!koncovka && (material(BILAFIG)<2000||material(CERNAFIG)<2000)){
        koncovka = true;
        for(int x = 0; x<8; x++)
            for(int y = 0; y<8; y++){
                hodnoty[5][x][y] = hodnoty[2][x][y];
                hodnoty[0][x][y]  = konec[x][y];
            }
    }
}

int Sachovnice::hodnoceni(){ //hodnoceni i pozice
    int hodnota = 0;
    volani++;
    for(int x = 0; x<8; x++)
        for(int y = 0; y<8; y++)
            if(pole[x][y]){
                hodnota += pole[x][y]->barva? pole[x][y]->hodnota : -pole[x][y]->hodnota;
                hodnota += pole[x][y]->barva? hodnoty[pole[x][y]->pos][y][x] : -hodnoty[pole[x][y]->pos][7-y][7-x]; //souradnice jsou prohozene
            }
    return hodnota;
}

int Sachovnice::material(bool barva){
     int hodnota = 0;
     for(int i = 0; i< 8; i++){
         for(int j =0; j< 8; j++){
             if(pole[i][j] && pole[i][j]->barva == barva)
                 hodnota += pole[i][j]->hodnota;
         }
     }
     return hodnota;
}

void Sachovnice::zkopiruj(Sachovnice *zdroj, bool prekresli){
    for(int a= 0; a<8;a++)
        for(int b= 0;b<8;b++){
            //if(pole[a][b]) delete pole[a][b];
            pole[a][b] = zdroj->pole[a][b]?zdroj->pole[a][b]->vytvor():NULL; //vytvori se nove figurky - posilat adresu teto sachovnice
            }
    tah=zdroj->tah;
    BkX=zdroj->BkX;
    BkY=zdroj->BkY;
    CkX=zdroj->CkX;
    CkY=zdroj->CkY;

    if(prekresli){
        pocetTahu = zdroj->pocetTahu;
        minule[0][0] = zdroj->minule[0][0];
        minule[0][1] = zdroj->minule[0][1];
        this->prekresli = true;
        generuj = true; //muze se zmenit, kdo tahne
    }
    klikPosun = false;
}

void Sachovnice::pridej(){
    if(pocetTahu == (int)historie.size()){ //novy tah
        historie.push_back(new Sachovnice(*this));
        historie.back()->zkopiruj(this);
        histVrat++;
    }
    else if(pocetTahu+1 == (int)historie.size()){ //vraceni jeden tah zpet
        historie[pocetTahu] = new Sachovnice(*this);
    }
}

void Sachovnice::vrat(bool dopredu){
    if(dopredu){
        if(pocetTahu+1<(int)historie.size()){
            zkopiruj(historie[pocetTahu+1],1);
        }
    }
    else if(histVrat>0){
        zkopiruj(historie[pocetTahu-1],1);
    }
}

void Sachovnice::posun(int stareX, int stareY, int noveX, int noveY, int &minX, int &minY, bool ai){
    pole[noveX][noveY] = pole[stareX][stareY]; //prirazeni
    pole[stareX][stareY] = NULL;  //vynulovani stareho mista
    pole[noveX][noveY]->tazeno(stareX,stareY,noveX,noveY,this,ai);
    minX = noveX; minY = noveY;
    historieTahy.push_back({stareX,stareY,noveX,noveY,hodnoceni()});
}


//int Sachovnice::generujTahy(int max_hloubka, int srovnani,int material){
//    int kX,kY,aktualni = tah?-1e9:1e9,sKX = tah? CkX:BkX,sKY = tah? CkY:BkY,nej = tah?-1e9:1e9,moznychTahu = 0; //nejlepsi hodnota v jedne funkci
//    bool tahnuto,vyhozeni,matProti = false;
//    Figurka * zalohy[2]; //prvni je startovaci policko, druhe je cilove policko

//    for(int x = 0; x<8; x++) for(int y = 0; y<8; y++)
//        if(pole[x][y] && pole[x][y]->barva == tah)

//            for(int cil_x = 0; cil_x < 8; cil_x++) for(int cil_y = 0; cil_y < 8; cil_y++)
//                if(pole[x][y]->moznosti(x,y,cil_x,cil_y,this)){

//                    tahnuto = pole[x][y]->tahnuto, zalohy[0] = pole[x][y], zalohy[1]=pole[cil_x][cil_y]; //zaloha figurek
//                    vyhozeni = pole[cil_x][cil_y]? 1:0; //doslo k vyhozeni figurky

//                    pole[cil_x][cil_y] = pole[x][y];
//                    pole[x][y] = NULL;
//                    pole[cil_x][cil_y]->tazeno(x,y,cil_x,cil_y,this,1);

//                    kX = tah?BkX:CkX,kY = tah? BkY:CkY; //nastaveni souradnic krale

//                    if(!pole[kX][kY]->pozorSach(kX,kY,this)){ //mozny tah

//                        if(pole[sKX][sKY]->pozorSach(sKX,sKY,this) && test!=this){ //souper je v sachu
//                            test->zkopiruj(this),test->tah =!tah;
//                            aktualni = test->generujTahy(0,tah?-1e9:1e9);
//                            if(aktualni == 1e9 || aktualni == -1e9) matProti = true;//nenalezen tah
//                        }

//                        if((Hloubka == max_hloubka || (vyhozeni? 0:material+1) > ZMENA_FIGUREK) && !matProti) aktualni = hodnoceni();
//                        else if(!matProti){tah=!tah; Hloubka++; aktualni = generujTahy(max_hloubka,nej,vyhozeni? 0:material+1); Hloubka--; tah =!tah;}
//                        if(!Hloubka)
//                            tahy.push_back({x,y,cil_x,cil_y,aktualni});
//                    }
//                    pole[x][y] = zalohy[0];
//                    pole[cil_x][cil_y] = zalohy[1]; //vraceni vyhozene figurky
//                    if(kX == cil_x && kY == cil_y) pole[x][y]->tazeno(cil_x,cil_y,x,y,this); //vraceni figurky
//                    pole[x][y]->tahnuto = tahnuto;
//                    if(mimochodem[Hloubka]){ pole[cil_x][y] = mimochodem[Hloubka];  mimochodem[Hloubka] = NULL;} //vraceni brani mimochodem
//                    if((tah && nej<aktualni)||(!tah && nej>aktualni) || matProti){ nej = aktualni; if(test == this) return aktualni;} //nalezena nejaka hodnota
//                    if(Hloubka && ((tah && srovnani < aktualni)||(!tah && srovnani > aktualni))){
//                        return aktualni;
//                    }
//                }
//    return nej;
//}


int Sachovnice::generujTahy(int max_hloubka, int srovnani,int material){
    int kX = tah?BkX:CkX,kY = tah? BkY:CkY,aktualni = tah?-1e9:1e9,nej = tah?-1e9:1e9; //nejlepsi hodnota v jedne funkci
    bool tahnuto,vyhozeni,nalezenTah = false,matProti = false;
    Figurka * zalohy[2]; //prvni je startovaci policko, druhe je cilove policko

    for(int x = 0; x<8; x++) for(int y = 0; y<8; y++)
        if(pole[x][y] && pole[x][y]->barva == tah)

            for(int cil_x = 0; cil_x < 8; cil_x++) for(int cil_y = 0; cil_y < 8; cil_y++)
                if(pole[x][y]->moznosti(x,y,cil_x,cil_y,this)){

                    tahnuto = pole[x][y]->tahnuto, zalohy[0] = pole[x][y], zalohy[1]=pole[cil_x][cil_y]; //zaloha figurek
                    vyhozeni = pole[cil_x][cil_y]? 1:0; //doslo k vyhozeni figurky

                    pole[cil_x][cil_y] = pole[x][y];
                    pole[x][y] = NULL;
                    pole[cil_x][cil_y]->tazeno(x,y,cil_x,cil_y,this,1);

                    kX = tah?BkX:CkX,kY = tah? BkY:CkY; //nastaveni souradnic krale

                    if(!pole[kX][kY]->pozorSach(kX,kY,this)){ //mozny tah

                        if (Hloubka == max_hloubka || (vyhozeni? 0:material+1) > ZMENA_FIGUREK ) aktualni = hodnoceni();
                        else {tah=!tah; Hloubka++; aktualni = generujTahy(max_hloubka,nej,vyhozeni? 0:material+1); Hloubka--; tah =!tah;}
                        if(!Hloubka)
                            tahy.push_back({x,y,cil_x,cil_y,aktualni});
                    }
                    pole[x][y] = zalohy[0];
                    pole[cil_x][cil_y] = zalohy[1]; //vraceni vyhozene figurky
                    if(kX == cil_x && kY == cil_y) {pole[x][y]->tazeno(cil_x,cil_y,x,y,this); kX = tah?BkX:CkX,kY = tah?BkY:CkY;} //vraceni figurky
                    pole[x][y]->tahnuto = tahnuto;
                    if(mimochodem[Hloubka]){ pole[cil_x][y] = mimochodem[Hloubka];  mimochodem[Hloubka] = NULL;} //vraceni brani mimochodem
                    if((tah && nej<aktualni)||(!tah && nej>aktualni) || matProti){ nej = aktualni; nalezenTah = true;} //nalezena nejaka hodnota
                    if(Hloubka && ((tah && srovnani < aktualni)||(!tah && srovnani > aktualni))){
                        return aktualni;
                    }
                }

    if(!nalezenTah) //zadny tah, pat, nebo mat
        if(!pole[kX][kY]->pozorSach(kX,kY,this)) return -nej; //neni sach; je pat

    return nej;
}

//pojistit proti patu
//udelat pojistku proti opakovani tahu
//udelat historii

//bool Sachovnice::overeni(Figurka *kontrolni[8][8]){
//    for(int i =0; i< 8;i++)
//        for(int j =0; j< 8;j++)
//            if(kontrolni[i][j] != pole[i][j]){
//                return true;
//            }

//    return false;
//}

//void Sachovnice::zalohuj(Figurka *(*zdroj)[8], Figurka *(*cil)[8]){
//    for(int a= 0; a<8;a++)
//        for(int b= 0;b<8;b++)
//            cil[a][b] = zdroj[a][b];
//}
