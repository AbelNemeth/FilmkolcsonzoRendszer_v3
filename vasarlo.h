#ifndef VASARLO_H
#define VASARLO_H

#include "film.h"
#include <List>
#include <felhasznalo.h>

class Vasarlo : public Felhasznalo
{
    list<Film*> sajatFilmek;
public:
    Vasarlo(string _szID);
    Vasarlo(string _szID, string _jelszo,string _emailCim,int _bankszamlaSzam);
    Vasarlo();

    void menu();
    void sajatAdatokBetolt();

    void adatokMegtekintese();

    bool elofizetesVasarlasa();


    bool filmHozzaad(string filmID);

    void vasarolhatoFilmekListaz();
    void sajatFilmekListaz();

    void filmVasarlas();
    list<Film*> getSajatFilmek() const;
};

#endif // VASARLO_H
