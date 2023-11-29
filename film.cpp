#include "film.h"

Film::Film(string _filmID, string _cim, int _ar):
    filmID(_filmID),
    cim(_cim),
    ar(_ar)
{

}

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

int Film::getAr() const
{
    return ar;
}

void Film::setAr(int newAr)
{
    ar = newAr;
}

