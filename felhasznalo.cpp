#include "felhasznalo.h"
#include "hiba.h"
#include <_mingw_mac.h>
#include <iostream>

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

void Felhasznalo::problemaJelentese(string jelentes, string tipus)
{
    if(jelentes == "0")
    {
        return;
    }
    else
    {
        list<Hiba> hibak;
        QFile hib("hibak.json");

        if(hib.exists())
        {
            if(hib.open(QIODevice::ReadOnly | QIODevice::Text))
            {

                QJsonArray hibakJson = QJsonDocument::fromJson(hib.readAll()).object()["hibak"].toArray();

                for(auto item : hibakJson)
                {
                    auto elem = item.toObject();

                    Hiba hiba = *new Hiba(elem["ID"].toString().toInt(), elem["SzID"].toString().toStdString(),elem["leiras"].toString().toStdString());
                    hibak.push_back(hiba);
                }
                hib.close();
                { // uj hiba hozzáadása a listához
                string felhaszId = this->szID;
                string _tipus = tipus;
                int id = hibak.back().getId();
                id++;
                hibak.push_back(*new Hiba(id, felhaszId, _tipus, jelentes));
                }
            }else cout << "JSon hiba!" << endl;
        }else cout << "File(ok) hianyoznak!" << endl;

        QJsonArray hibakLista;
        for(auto& item : hibak)
        {
            if(item.getActiv())
            {
                QJsonObject hiba;
                hiba["ID"] = item.getId();
                hiba["SzID"] = QString::fromStdString(item.getSzID());
                hiba["tipus"] = QString::fromStdString(item.getTipus());
                hiba["leiras"] = QString::fromStdString(item.getLeiras());
                hibakLista.push_back(hiba);
            }
        }
        QJsonDocument docH(hibakLista);
        QFile fileH("hibak.json");
        if (fileH.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&fileH);
            out << docH.toJson();
            fileH.close();
            cout << "JSON array saved to hibak.json";
        }else cout << "Hiba a hiba lista mentesekor" << endl;
        cout << "Problema jelentve" << endl;
    }
}

void Felhasznalo::filmLejatszasa(Film *film)
{
    cout << "Film jatszasa.. (" << film->getCim() << ")" << endl;
}

void Felhasznalo::adatokMegtekintese()
{
    cout << "Felhasznalo: " << szID << " Email cim: " << emailCim << " bankszamla szam : " << bankszamlaSzam;
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
