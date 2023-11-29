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



int main()
{
    cout << "Program starting... " << endl;
    while(true)
    {
        cout << "1. Bejelentkezes" << endl;
        cout << "2. Regisztracio" << endl;
        int valasztas = 0;
        switch(valasztas)
        {
        case 1 :    belepes(); break;
        case 2 :    regisztracio(); break;
        default :   cout << "Nincs ilyen menu opcio" << endl; break;
        }
    }
    return 0;
}

void belepes()
{
    map<string, int> tipusIndex;
    map<string, string> idEsJelszo;

    //getting the types and stuff
    QFile vas("vasalok.json");
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
        Vasarlo vasarlo;
        Elofizeto elofizeto;
        Segito segito;
        Administrator admin;
        switch (tipusIndex[id])
        {
        case 1:
            vasarlo = *new Vasarlo(id);
            vasarlo.menu();
            break;
        case 2:
            elofizeto = *new Elofizeto(id);
            elofizeto.menu();
            break;
        case 3:
            segito = *new Segito(id);
            segito.menu();
            break;
        case 4:
            admin = *new Administrator(id);
            admin.menu();
            break;
        default:
            cout << "Nincs ilyen bejelentkezesi tipus opcio. Bejelentkezesben hiba lepett fel. Ertesitsen egy varázslót" << endl;
            break;
        }
    }

}
