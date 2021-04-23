#include "menu.h"
#include "main.h"
#include "strelec.h"
#include "vez.h"
#include "dama.h"
#include "kun.h"

Menu::Menu()
{
     polroz=90; //sachovnice->polroz;
}

void Menu::klik(int MysX, int MysY){
    int x=MysX/polroz;
    int y=MysY/polroz;
    int kX,kY;

    if(pesecBarva && x==pesecX){ //bila
        switch (y) {
        case 0:
            sachovnice->pole[pesecX][pesecY]=new class Dama(BILAFIG);
            break;
        case 1:
            sachovnice->pole[pesecX][pesecY]=new class Vez(BILAFIG);
            break;
        case 2:
            sachovnice->pole[pesecX][pesecY]=new class Kun(BILAFIG);
            break;
        case 3:
            sachovnice->pole[pesecX][pesecY]=new class Strelec(BILAFIG);
            break;
        }
        kX=sachovnice->CkX,kY=sachovnice->CkY; //barvy jsou prohozene, protoze je jeste stary tah
    }
    else if(!pesecBarva && x==pesecX){
        switch (y) {
        case 4:
            sachovnice->pole[pesecX][pesecY]=new class Dama(CERNAFIG);
            break;
        case 5:
            sachovnice->pole[pesecX][pesecY]=new class Vez(CERNAFIG);
            break;
        case 6:
            sachovnice->pole[pesecX][pesecY]=new class Kun(CERNAFIG);
            break;
        case 7:
            sachovnice->pole[pesecX][pesecY]=new class Strelec(CERNAFIG);
            break;
        }
        kX=sachovnice->BkX,kY=sachovnice->BkY;
    }
      if(sachovnice->pole[pesecX][pesecY]){ //bylo vybrano
        aktivni=sachovnice;
        sachovnice->pole[kX][kY]->pozorSach(kX,kY,sachovnice);
    }
}

void Menu::kresli(){
//    if(pesecBarva){//bila
//        barva(MODRA);
//        obdelnik(pesecX*polroz,0,(pesecX+1)*polroz,polroz*4);
//    }
//    else {
//        barva(MODRA);
//         obdelnik(pesecX*polroz,4*polroz,(pesecX+1)*polroz,8*polroz);
//    }

//    Dama.kresli();
//    Vez.kresli();
//    Strelec.kresli();
//    Kun.kresli();
//    ukazatel->aktualizuj();
}

void Menu::umisti(bool barva){
//    if(barva){
//        Dama.nacti("figures/white_queen.png");
//        Kun.nacti("figures/white_knight.png");
//        Strelec.nacti("figures/white_bishop.png");
//        Vez.nacti("figures/white_rook.png");
//        Dama.umisti(pesecX*polroz,polroz*pesecY);
//        Vez.umisti(pesecX*polroz,polroz*(pesecY+1));
//        Kun.umisti(pesecX*polroz,polroz*(pesecY+2));
//        Strelec.umisti(pesecX*polroz,polroz*(pesecY+3));
//    }
//    else{
//        Dama.nacti("figures/black_queen.png");
//        Kun.nacti("figures/black_knight.png");
//        Strelec.nacti("figures/black_bishop.png");
//        Vez.nacti("figures/black_rook.png");
//        Dama.umisti(pesecX*polroz,polroz*(pesecY-3));
//        Vez.umisti(pesecX*polroz,polroz*(pesecY-2));
//        Kun.umisti(pesecX*polroz,polroz*(pesecY-1));
//        Strelec.umisti(pesecX*polroz,polroz*(pesecY));
//    }
}

void Menu::nactiPesec(bool barva, int x, int y){
    pesecX=x;
    pesecY=y;
    //sachovnice->poleNULL(pesecX,pesecY); //pole, na ktere vstoupil pesec se  nuluje
    sachovnice->pole[pesecX][pesecY]=NULL;
    sachovnice->kresli();
    umisti(barva);
    pesecBarva=barva;
}

void Menu::konec(){}



