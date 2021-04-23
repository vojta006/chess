#ifndef MAIN_H
#define MAIN_H
#include "menu.h"
#include "sachovnice.h"

extern Screen *aktivni;
extern Sachovnice *sachovnice;
extern Menu *menu;
extern Sachovnice *test;
extern Sachovnice *zaloha;
extern int volani,NewDama;
extern SDL_Surface *screen;
extern SDL_Surface *figurky;
extern bool hraj;
extern std::vector<Sachovnice*> historie;
#endif // MAIN_H

