#ifndef FELHASZNALO_H
#define FELHASZNALO_H

#include <string>
#include "hiba.h"
#include "film.h"

using namespace std;

class Felhasznalo
{
private:
    string szID;
    int tipus;
    string jelszo;
    string emailCim;
    bool elofizeto;
    int bankszamlaSzam;
public:
    Felhasznalo(string _szID);
    Felhasznalo(string _szID, string _jelszo,string _emailCim,int _bankszamlaSzam);

    void problemaJelentes();
    void filmLejatszasa();

    virtual void adatokMegtekintese();
    virtual void menu() = 0;
    virtual void SajatAdatokBetolt();

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
