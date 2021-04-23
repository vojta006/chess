#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "main.h"
#include "ai.h"

Screen *aktivni;
Sachovnice *sachovnice,*zaloha,*test;
Menu *menu;
int volani;
SDL_Surface *screen;
SDL_Surface *figurky;
bool hraj = false;
std::vector<Sachovnice*> historie;

int main(int argc,char *argv[])
{
    figurky = IMG_Load("figures/figures_mensi.png");
    if(SDL_Init(SDL_INIT_VIDEO)){ printf("SDL_Init() selhalo: %s\n", SDL_GetError()); exit(1);}
    screen = SDL_SetVideoMode(1000,680,0,0);
    test = new Sachovnice;
    sachovnice = new Sachovnice;
    menu = new Menu;
    aktivni = sachovnice;
    zaloha = new Sachovnice;
    while(1){

        aktivni->kresli();
        if(hraj) ai();

        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button==SDL_BUTTON_LEFT)
                    aktivni->klik(event.motion.x,event.motion.y);
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    SDL_Quit();
                    return 0;
                case SDLK_a:
                    ai();
                    break;
                case SDLK_i:
                    hraj = !hraj;
                    break;
                case SDLK_b:
                    sachovnice->vrat(0); //dozadu
                    break;
                case SDLK_f:
                    sachovnice->vrat(1); //dopredu
                    break;
                }
                break;
            }
        }
    }
}
