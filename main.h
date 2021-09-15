#ifndef MAIN_H
#define MAIN_H
#include "menu.h"
#include "sachovnice.h"
#include "komunikace.h"

extern Screen *aktivni;
extern Sachovnice *sachovnice;
extern Menu *menu;
extern int volani;
extern SDL_Surface *screen;
extern bool hraj;
extern std::vector<Sachovnice*> historie;
#endif // MAIN_H

