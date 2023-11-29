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
    string bankszamlaSzam;
public:
    Felhasznalo(string _szID);

    void problemaJelentes();
    void filmLejatszasa();

    virtual void adatokMegtekintese();
    virtual void menu() = 0;
    virtual void SajatAdatokBetolt();

    //getters and setters
    string getSzID() const;
    string getEmailCim() const;
    string getBankszamlaSzam() const;
    void setBankszamlaSzam(const string &newBankszamlaSzam);
    void setEmailCim(const string &newEmailCim);
};

#endif // FELHASZNALO_H
