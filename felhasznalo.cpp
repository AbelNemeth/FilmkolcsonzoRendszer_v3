#include "felhasznalo.h"
#include <_mingw_mac.h>

void Felhasznalo::setSzID(const string &newSzID)
{
    szID = newSzID;
}

string Felhasznalo::getJelszo() const
{
    return jelszo;
}

Felhasznalo::Felhasznalo(string _szID):
    szID(_szID)
{

}

Felhasznalo::Felhasznalo(string _szID, string _jelszo, string _emailCim, int _bankszamlaSzam):
    szID(_szID),
    jelszo(_jelszo),
    emailCim(_emailCim),
    bankszamlaSzam(_bankszamlaSzam)
{

}

string Felhasznalo::getSzID() const
{
    return szID;
}

string Felhasznalo::getEmailCim() const
{
    return emailCim;
}

int Felhasznalo::getBankszamlaSzam() const
{
    return bankszamlaSzam;
}

void Felhasznalo::setBankszamlaSzam(const int &newBankszamlaSzam)
{
    bankszamlaSzam = newBankszamlaSzam;
}

void Felhasznalo::setEmailCim(const string &newEmailCim)
{
    emailCim = newEmailCim;
}
