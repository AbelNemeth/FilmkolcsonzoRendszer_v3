#ifndef ELOFIZETO_H
#define ELOFIZETO_H

#include "vasarlo.h"
#include <felhasznalo.h>

class Elofizeto : public Felhasznalo
{
private:
    int elofizetesID;
    time_t elofizetesMegkezdese;
public:
    Elofizeto(string _szID);
    Elofizeto(string _szID, string _jelszo,string _emailCim,int _bankszamlaSzam,int _elofizetesID, time_t _elofizetesMegkezdese);
    Elofizeto();

    void menu();
    void sajatAdatokBetolt();

    void adatokMegtekintese();

    void elofizetesMegtekintese();

    Vasarlo* elofizetesLemondasa();
    bool elofizetesLemondasMegkezdese();

    void filmekListazasa();

    int getElofizetesID() const;
    time_t getElofizetesMegkezdese() const;
    int getHatralevoNapok();
};

#endif // ELOFIZETO_H
