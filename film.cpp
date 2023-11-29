#include "film.h"

string Film::getFilmID() const
{
    return filmID;
}

string Film::getCim() const
{
    return cim;
}

void Film::setCim(const string &newCim)
{
    cim = newCim;
}

int Film::getHosszPercben() const
{
    return hosszPercben;
}

void Film::setHosszPercben(int newHosszPercben)
{
    hosszPercben = newHosszPercben;
}

int Film::getAr() const
{
    return ar;
}

void Film::setAr(int newAr)
{
    ar = newAr;
}

Film::Film(string _filmID, string _cim, int _hossz, int _ar):
    filmID(_filmID),
    cim(_cim),
    hosszPercben(_hossz),
    ar(_ar)
{

}
