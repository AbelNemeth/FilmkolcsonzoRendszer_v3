#include "felhasznalo.h"

Felhasznalo::Felhasznalo(string _szID):
    szID(_szID)
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

string Felhasznalo::getBankszamlaSzam() const
{
    return bankszamlaSzam;
}

void Felhasznalo::setBankszamlaSzam(const string &newBankszamlaSzam)
{
    bankszamlaSzam = newBankszamlaSzam;
}

void Felhasznalo::setEmailCim(const string &newEmailCim)
{
    emailCim = newEmailCim;
}
