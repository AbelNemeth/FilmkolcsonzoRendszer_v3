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

    void ujFilmHozzaadasa(Film film);
    void filmAdatokModositasa(string id);
    void elofizetesArModositasa(int ar);
};

#endif // ADMINISTRATOR_H
