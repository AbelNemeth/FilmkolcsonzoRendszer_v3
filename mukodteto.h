#ifndef MUKODTETO_H
#define MUKODTETO_H

#include <string>
#include <vector>
#include "hiba.h"

using namespace std;

class Mukodteto
{
private:
    string szID;
    int tipus;
    string jelszo;
    vector<Hiba> problemakLista;
    vector<Hiba> tranzakciosHibakLista;
public:
    Mukodteto(string _szID);

    virtual void menu() = 0;
    virtual void SajatAdatokBetolt();

    void felhasznaloiAdatokModositasa();
    void felhaszanloIDModositasa(string oldID, string newID);
    void felhaszanloEmailCimModositasa(string id, string emailCim);

    void problemakListaBeolvas();
    void problemakListaKiir();

    void hibaAllapotModositasa(bool allapot);
    void hibaListaTorlese();

};

#endif // MUKODTETO_H
