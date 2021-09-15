#ifndef KOMUNIKACE_H
#define KOMUNIKACE_H
#include "sachovnice.h"
#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <array>
#include <vector>
extern TCPsocket socket;
extern SDLNet_SocketSet set;

using namespace std;

class Komunikace{
    /*
  Začne síťovou komunikaci se serverem
  výstup: 1=povedlo se	0=nepovedlo se
  pozn.: ve funkci se neinicializuje SDL knihovna
*/
private:
    //string nazevHry;
    Sachovnice *s;
public:
    char mistnost;
    int tah;
    int Zacit_Komunikaci(const char* ip_adresa, Uint16 port);
    bool hrani;
    //bool zadost; //prisla zadost o hru
    void posta();
    Komunikace(Sachovnice *s);
    void Ukoncit_Komunikaci();
    void odeslatTah();
    ~Komunikace();

    /*
  Ukončí síťovou komunikaci
  pozn.: komunikace skončí i s ukončením programu
*/

    /*
  Serveru pošle nějakou zprávu
  výstup: 1=povedlo se	0=nepovedlo se
*/

private:
    int Poslat_String(char* text);



    /*
  Zkontroluje, jestli server něco neposlal
  výstup: 1=server neco poslal se	0=nic neprislo
*/
    int Neco_Prislo();

    /*
  Zapíše zprávu od serveru na vystup (ukazatel na začátek pole charů, který byl funkci předán).
  Zápis skončí, když se najde ve zprávě 0 nebo načítaná zpráva přesáhne max_delka
  výstup: 1=vse probehlo v poradku	0=doslo k chybe
  pozn.: funkce čeká na to až přijde 0 nebo se přečte max_delka znaků, takže pokud přijde nějaká zpráva bez 0 na konci a je kratší
    než max_delka, tak se to zacyklí a neskončí to
*/
    int Precist_String(char* vystup, int max_delka);

};

#endif // KOMUNIKACE_H
