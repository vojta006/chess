#include "komunikace.h"

TCPsocket socket;
SDLNet_SocketSet set;


Komunikace::Komunikace(Sachovnice *s){
    this->s = s;
    hrani = false;
    if(!Zacit_Komunikaci("diblik.kapsa.cz", 1234)){
        printf("nepodarilo se navazat spojeni");
        delete this;
    }
    else {
        char posli[] = "nazdarek";
        Poslat_String(posli);
        tah = 2;
    }
}

int Komunikace::Zacit_Komunikaci(const char* ip_adresa, Uint16 port)
{
    // v pripade, ze se to nedela nekde drive v programu, tak je sem potreba inicializovat SDL (dela to ten zakomentovany kus kodu)
    /*
    if(SDL_Init(0) == -1) {
        printf("SDL_Init: %s\n", SDL_GetError());
        return 0;
    }
    */

    // Initialization
    if(SDLNet_Init() == -1) {
        printf("SDLNet_Init: %s\n", SDLNet_GetError());
        return 0;
    }

    IPaddress ip;
    // Resolve the argument into an IPaddress type
    if(SDLNet_ResolveHost(&ip, ip_adresa, port) == -1) {
        printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        return 0;
    }

    // open the server socket
    socket = SDLNet_TCP_Open(&ip);	// create a socket
    if(!socket) {
        printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        return 0;
    }
    set = SDLNet_AllocSocketSet(1);	// create a set of sockets
    if(!set) {
        printf("SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
        return 0;
    }
    if(SDLNet_TCP_AddSocket(set, socket) == -1) {	// add the one socket to the set of sockets
        printf("SDLNet_TCP_AddSocket: %s\n", SDLNet_GetError());
        return 0;
    }
    return 1;
}

void Komunikace::Ukoncit_Komunikaci()
{
    SDLNet_TCP_Close(socket);

    SDLNet_FreeSocketSet(set);

    // shutdown SDL_net
    SDLNet_Quit();
}

void Komunikace::posta(){ //kontrola, jestli neco prislo
    char prijem[100];
    int sourad[4];
    char mistnost;
    bool flag = false; //nalezen spravny tah
    char jmeno[10];
    memset(jmeno,0,10);
    memset(prijem, 0, 100);
    if(Neco_Prislo()){
        if(!Precist_String(prijem, 50))  return;
        if(hrani){
            if(sscanf(prijem,"sachy %c %d,%d->%d,%d %s",&mistnost,&sourad[0],&sourad[1],&sourad[2],&sourad[3],jmeno)!=6) return;
            if(mistnost == this->mistnost && strcmp(jmeno,"vojta")){
                for(auto tah:s->tahy){
                    flag = true;
                    for(int index = 0;index<4;index++)
                        if(tah[index] != sourad[index]){flag =false; break;}
                    if(flag){ //prijaty tah je korektni
                        s->posun(tah[0],tah[1],tah[2],tah[3],s->historie[s->histVrat]);
                        s->dalsiTah(0);
                        printf("%s\n", prijem);
                        fflush(stdout);
                        break;
                    }
                }
            }
        }
    }
}


void Komunikace::odeslatTah(){ //nazev hry
//    char text[50];
//    memset(text,0,50);
//    sprintf(text,"%s %c %d,%d->%d,%d vojta",s->nazev.c_str(),mistnost,s->historie.back()[0],s->historie.back()[1],
//            s->historie.back()[2],s->historie.back()[3]);
//    //sprintf(text,"%s %c %d,%d->%d,%d vojta",s->nazev.c_str(),mistnost,s->historieTahy.back()[0],s->historieTahy.back()[1],
//      //      s->historieTahy.back()[2],s->historieTahy.back()[3]);
//    Poslat_String(text);
}




int Komunikace::Poslat_String(char* text)
{
    if(SDLNet_TCP_Send(socket, text, int(strlen(text)) + 1) == int(strlen(text)) + 1)
        return 1;
    else {
        printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
        return 0;
    }
}

int Komunikace::Neco_Prislo()
{
    if(SDLNet_CheckSockets(set, 0) == -1) {
        printf("SDLNet_CheckSockets: %s\n", SDLNet_GetError());
    }
    else if(SDLNet_SocketReady(socket)) {
        return 1;
    }
    return 0;
}

Komunikace::~Komunikace(){
    Ukoncit_Komunikaci();
}


int Komunikace::Precist_String(char* vystup, int max_delka)
{
    int byte = 0;
    while(SDLNet_CheckSockets(set, 0) != -1) {
        if(SDLNet_SocketReady(socket)) {
            if(byte >= max_delka) {
                printf("Precist_String: Přišla zpráva delší než se čekalo\n");
                return 1;
            }
            SDLNet_TCP_Recv(socket , &vystup[byte], 1);
            if(vystup[byte] == 0)
                return 1;
            byte++;
        }
        else {
            SDL_Delay(1);
        }
    }
    printf("SDLNet_CheckSockets: %s\n", SDLNet_GetError());
    return 0;
}
