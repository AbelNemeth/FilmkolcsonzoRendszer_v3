#include "vasarlo.h"

Vasarlo::Vasarlo(string _szID):
    Felhasznalo(_szID)
{

}

Vasarlo::Vasarlo(string _szID, string _jelszo,string _emailCim,int _bankszamlaSzam):
    Felhasznalo(_szID, _jelszo, _emailCim, _bankszamlaSzam)
{

}

Vasarlo::Vasarlo():
    Felhasznalo("")
{

}
