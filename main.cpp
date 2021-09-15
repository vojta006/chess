#include <SDL/SDL_image.h>
#include "main.h"
#include "ai.h"

Screen *aktivni;
Sachovnice *sachovnice;
Menu *menu;
int volani;
SDL_Surface *screen;
bool hraj = false;
std::vector<Sachovnice*> historie;

int main(int argc,char *argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO)){ printf("SDL_Init() selhalo: %s\n", SDL_GetError()); exit(1);}
    screen = SDL_SetVideoMode(1000,680,0,0);
    aktivni  = sachovnice = new Sachovnice;
    menu = new Menu;

    while(1){

        SDL_Delay(10);
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
                    menu->konecHry();
                    break;
                case SDLK_a:
                    ai();
                    break;
                case SDLK_i:
                    hraj = !hraj; //automaticke hrani
                    break;
                }
                break;
            }
        }
    }
}
