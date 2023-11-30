#ifndef MUKODTETO_H
#define MUKODTETO_H

#include <string>
#include <vector>
#include "felhasznalo.h"
#include "hiba.h"
#include <iostream>

#include <QJsonObject> //json objektum létrehozására
#include <QJsonArray> //json lista
#include <QFile> //json file nyitás, olvasás stb.
#include <QJsonDocument> //itt tudunk átalakításokat csinálni, vagy valami ilyesmi

using namespace std;

class Mukodteto
{
private:
    string szID;
    string jelszo;
    vector<Hiba> problemakLista;
    vector<Hiba> tranzakciosHibakLista;
protected:
    list<Felhasznalo*> felhasznalok;
public:
    Mukodteto(string _szID);

    virtual void menu() = 0;

    void felhasznaloiAdatokModositasa();
    void felhaszanloIDModositasa();
    void felhaszanloEmailCimModositasa();
    void felhasznaloBankszamlaSzamModositasa();

    void hibaListakBeolvas();
    void felhasznalokBeolvas();

    void tranzakciosHibakKiir();
    void problemakListaKiir();

    void hibaAllapotModositasa();
    void hibaListaTorlese();

    virtual void kilepes();
};

#endif // MUKODTETO_H
