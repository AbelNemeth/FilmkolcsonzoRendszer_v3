#include "elofizeto.h"

int Elofizeto::getElofizetesID() const
{
    return elofizetesID;
}

Elofizeto::Elofizeto(string _szID):
    Felhasznalo(_szID)
{

}

Elofizeto::Elofizeto(string _szID, string _jelszo, string _emailCim, int _bankszamlaSzam, int _elofizetesID):
    Felhasznalo(_szID, _jelszo, _emailCim, _bankszamlaSzam),
    elofizetesID(_elofizetesID)
{

}

Elofizeto::Elofizeto():
    Felhasznalo("")
{

}
