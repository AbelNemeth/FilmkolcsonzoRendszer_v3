#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "film.h"
#include <mukodteto.h>

class Administrator : public Mukodteto
{
public:
    Administrator(string _szID);
    Administrator();

    void menu();

    void ujFilmHozzaadasa();
    void filmAdatokModositasa();
    void elofizetesArModositasa();
};

#endif // ADMINISTRATOR_H
