#ifndef ELOFIZETO_H
#define ELOFIZETO_H

#include <felhasznalo.h>

class Elofizeto : public Felhasznalo
{
private:
    int elofizetesID;
public:
    Elofizeto(string _szID);
    Elofizeto();

    void menu();

    void ElofizetesMegtekintese();
    void elofizetesLemondasa();
    void filmekListazasa();
};

#endif // ELOFIZETO_H
