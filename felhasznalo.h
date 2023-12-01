#ifndef FELHASZNALO_H
#define FELHASZNALO_H

#include "film.h"
#include <string>
#include <time.h>

using namespace std;

#include <QJsonObject> //json objektum létrehozására
#include <QJsonArray> //json lista
#include <QFile> //json file nyitás, olvasás stb.
#include <QJsonDocument> //itt tudunk átalakításokat csinálni, vagy valami ilyesmi

class Felhasznalo
{
protected:
    string szID;
    string jelszo;
    string emailCim;
    int bankszamlaSzam;
public:
    Felhasznalo(string _szID);
    Felhasznalo(string _szID, string _jelszo, string _emailCim, int _bankszamlaSzam);

    void problemaJelentese(string jelentes, string tipus);
    void filmLejatszasa(Film* film);
    virtual void adatokMegtekintese();

    virtual void menu() = 0;
    virtual void sajatAdatokBetolt() = 0;

    //getters and setters
    string getSzID() const;
    string getEmailCim() const;
    int getBankszamlaSzam() const;
    string getJelszo() const;
    void setBankszamlaSzam(const int &newBankszamlaSzam);
    void setEmailCim(const string &newEmailCim);
    void setSzID(const string &newSzID);
};


#endif // FELHASZNALO_H
