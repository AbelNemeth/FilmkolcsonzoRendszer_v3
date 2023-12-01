#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "film.h"
#include <mukodteto.h>

class Administrator : public Mukodteto
{
    list<Film*> filmek;
public:
    Administrator(string _szID);
    Administrator();

    void menu();
    void adatokListazasa();

    void filmekBetolt();

    void ujFilmHozzaadasa();
    void filmAdatokModositasa();
    void elofizetesArModositasa();

    void kilepes();
};

#endif // ADMINISTRATOR_H
