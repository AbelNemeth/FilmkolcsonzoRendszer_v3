#ifndef VASARLO_H
#define VASARLO_H

#include <List>
#include <felhasznalo.h>

class Vasarlo : public Felhasznalo
{
    list<Film> sajatFilmek;
public:
    Vasarlo(string _szID);
    Vasarlo(string _szID, string _jelszo,string _emailCim,int _bankszamlaSzam);
    Vasarlo();
    void menu();

    void elofizetesVasarlasa();

    void vasarolhatoFilmekListaz();
    void sajatFilmekListaz();

    void filmVasarlas();
};

#endif // VASARLO_H
