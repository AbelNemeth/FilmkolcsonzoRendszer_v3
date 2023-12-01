#include "hiba.h"

int Hiba::getId() const
{
    return id;
}

string Hiba::getSzID() const
{
    return szID;
}

string Hiba::getLeiras() const
{
    return leiras;
}

bool Hiba::getActiv() const
{
    return activ;
}

void Hiba::setActiv(bool newActiv)
{
    activ = newActiv;
}

string Hiba::getTipus() const
{
    return tipus;
}

Hiba::Hiba(int id, string szID, string leiras):
    id(id),
    szID(szID),
    leiras(leiras),
    activ(true)
{

}

Hiba::Hiba(int id, string szID, string tipus, string leiras):
    id(id),
    szID(szID),
    leiras(leiras),
    tipus(tipus),
    activ(true)
{

}
