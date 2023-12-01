#include "elofizeto.h"
#include "segito.h"
#include "vasarlo.h"
#include <iostream>

#include <QJsonObject> //json objektum létrehozására
#include <QJsonArray> //json lista
#include <QFile> //json file nyitás, olvasás stb.
#include <QJsonDocument> //itt tudunk átalakításokat csinálni, vagy valami ilyesmi
#include <Administrator.h>

using namespace std;

void belepes();
void regisztracio();
void adatokBetolt();

map<string, int> tipusIndex;
map<string, string> idEsJelszo;

int main()
{
    adatokBetolt();
    cout << "Program starting... " << endl;
    while(true)
    {
        cout << "1. Bejelentkezes" << endl;
        cout << "2. Regisztracio" << endl;
        int valasztas = 0;
        cin >> valasztas;
        switch(valasztas)
        {
        case 1 :    belepes(); break;
        //case 2 :    regisztracio(); break;
        default :   cout << "Nincs ilyen menu opcio" << endl; break;
        }
    }
    return 0;
}

void adatokBetolt()
{
    //getting the types and stuff
    QFile vas("vasarlok.json");
    QFile elo("elofizetok.json");
    QFile seg("segitok.json");
    QFile adm("adminok.json");

    if(vas.exists() && elo.exists() && seg.exists() && adm.exists()){
        if(vas.open(QIODevice::ReadOnly | QIODevice::Text) && elo.open(QIODevice::ReadOnly | QIODevice::Text) && seg.open(QIODevice::ReadOnly | QIODevice::Text) && adm.open(QIODevice::ReadOnly | QIODevice::Text)){

            QJsonArray vasarlok =       QJsonDocument::fromJson(vas.readAll()).object()["felhasznalok"].toArray();
            QJsonArray elofizetok =     QJsonDocument::fromJson(elo.readAll()).object()["elofizetok"].toArray();
            QJsonArray adminok =        QJsonDocument::fromJson(seg.readAll()).object()["segitok"].toArray();
            QJsonArray segitok =        QJsonDocument::fromJson(adm.readAll()).object()["adminok"].toArray();
            for(auto item : vasarlok)
            {
                tipusIndex[item.toObject()["SzID"].toString().toStdString()] = 1;
                idEsJelszo[item.toObject()["SzID"].toString().toStdString()] = item.toObject()["jelszo"].toString().toStdString();
            }
            for(auto item : elofizetok)
            {
                tipusIndex[item.toObject()["SzID"].toString().toStdString()] = 2;
                idEsJelszo[item.toObject()["SzID"].toString().toStdString()] = item.toObject()["jelszo"].toString().toStdString();
            }
            for(auto item : adminok)
            {
                tipusIndex[item.toObject()["SzID"].toString().toStdString()] = 3;
                idEsJelszo[item.toObject()["SzID"].toString().toStdString()] = item.toObject()["jelszo"].toString().toStdString();
            }
            for(auto item : segitok)
            {
                tipusIndex[item.toObject()["SzID"].toString().toStdString()] = 4;
                idEsJelszo[item.toObject()["SzID"].toString().toStdString()] = item.toObject()["jelszo"].toString().toStdString();
            }
            vas.close();
            elo.close();
            seg.close();
            adm.close();
        }else cout << "error with json files" << endl;
    }
    else cout << "File(s) Missing!" << endl;
}
void belepes()
{
    //adatok bekerese
    string id;
    string jelszo;
    cout << "Kerem adja meg a bejelentkezesi ID-jat: " << endl;
    cin >> id;

    cout << "Kerem adja meg a jelszavat: " << endl;
    cin >> jelszo;

    if(tipusIndex.find(id)==tipusIndex.end()) //ellenőrzi hogy van-e ilyen felhasználó az adatbázisban
    {
        cout << "Hibas belepesi adatok" << endl;
    }
    else if(idEsJelszo[id] != jelszo)
    {
        cout << "Hibas belepesi adatok" << endl;
    }
    else{
        Vasarlo* vasarlo;
        Elofizeto* elofizeto;
        Segito* segito;
        Administrator* admin;
        switch (tipusIndex[id])
        {
        case 1:
            vasarlo = new Vasarlo(id);
            vasarlo->menu();
            break;
        case 2:
            elofizeto = new Elofizeto(id);
            elofizeto->menu();
            break;
        case 3:
            segito = new Segito(id);
            segito->menu();
            break;
        case 4:
            admin = new Administrator(id);
            admin->menu();
            break;
        default:
            cout << "Nincs ilyen bejelentkezesi tipus opcio. Bejelentkezesben hiba lepett fel. Ertesitsen egy varázslót" << endl;
            break;
        }
    }

}

void registracio()
{
    string bemenet;
    cout << "Adjon meg egy felhasznalonevet! (a kilepeshez irja be hogy 0)" << endl;
    cin >> bemenet;
    if(bemenet == "0") return;
    if(idEsJelszo.find(bemenet) != idEsJelszo.end())
    {
        cout << "Ez a felhasznalonev foglalt!" << endl;
        return;
    }
    string szID = bemenet;

    cout << "Adja meg a jelszavat! (a kilepeshez irja be hogy 0)" << endl;
    cin >> bemenet;
    if(bemenet == "0") return;
    string jelszo = bemenet;

    cout << "Adja meg az email cimet! (a kilepeshez irja be hogy 0)" << endl;
    cin >> bemenet;
    if(bemenet == "0") return;
    string email = bemenet;

    cout << "Adja meg a bankszamla szamat! (a kilepeshez irja be hogy 0)" << endl;
    int bankszamlaSzam;
    cin >> bankszamlaSzam;
    if(bankszamlaSzam == 0) return;

    //vasarlok betolt
    QJsonArray vasarlokLista;
    QFile vas("vasalok.json");
    if(vas.exists()){
        if(vas.open(QIODevice::ReadOnly | QIODevice::Text)){
            vasarlokLista = QJsonDocument::fromJson(vas.readAll()).object()["felhasznalok"].toArray();
            vas.close();
        }else cout << "error with json files" << endl;
    }else cout << "File(s) Missing!" << endl;

    //vasarlo mentese
    QJsonObject v;
    v["SzID"] = QString::fromStdString(szID);
    v["jelszo"] = QString::fromStdString(jelszo);
    v["emailCim"] = QString::fromStdString(email);
    v["bankszamlaSzam"] = bankszamlaSzam;
    v["filmLista"] = QString::fromStdString("");

    vasarlokLista.push_back(v);

    //vasarlok ment
    QJsonDocument docV(vasarlokLista);
    QFile fileV("vasarlok.json");
    if (fileV.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&fileV);
        out << docV.toJson();
        fileV.close();
        cout << "JSON array saved to vasarlok.json";
    }else cout << "Hiba a hiba lista mentesekor" << endl;
}
