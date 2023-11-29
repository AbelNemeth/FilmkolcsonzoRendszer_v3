#ifndef ELOFIZETO_H
#define ELOFIZETO_H

#include <felhasznalo.h>

class Elofizeto : public Felhasznalo
{
private:
    int elofizetesID;
public:
    Elofizeto(string _szID);
    Elofizeto(string _szID, string _jelszo,string _emailCim,int _bankszamlaSzam,int _elofizetesID);
    Elofizeto();

    void menu();

    void ElofizetesMegtekintese();
    void elofizetesLemondasa();
    void filmekListazasa();
    int getElofizetesID() const;
};

#endif // ELOFIZETO_H
