#include "administrator.h"

#include <Elofizetes.h>

Administrator::Administrator(string _szID):
    Mukodteto(_szID)
{

}

Administrator::Administrator():
    Mukodteto("")
{

}

void Administrator::menu()
{
    bool bejelentkezve = true;
    while(bejelentkezve)
    {
        cout << "1. Trazakcios hibak listazasa" << endl;
        cout << "2. Bejelentett hibak listazasa" << endl;
        cout << "3. Hiba modositasa" << endl;
        cout << "4. Befejezett hibak torlese" << endl;
        cout << "5. Felhasznaloi adatok modositasa" << endl;
        cout << "6. Uj Film Hozzadadasa" << endl;
        cout << "7. Egy film adatainak modositasa" << endl;
        cout << "8. Elofizetes aranak megvaltoztatasa" << endl;
        cout << "0. Kijelentkezes" << endl;

        int bemenet;
        cin >> bemenet;

        switch (bemenet) {
        case 1:
            tranzakciosHibakKiir();
            break;
        case 2:
            problemakListaKiir();
            break;
        case 3:
            hibaAllapotModositasa();
            break;
        case 4:
            hibaListaTorlese();
            break;
        case 5:
            felhasznaloiAdatokModositasa();
            break;
        case 6:
            ujFilmHozzaadasa(); //admin
            break;
        case 7:
            filmAdatokModositasa(); //admin
            break;
        case 8:
            elofizetesArModositasa(); //admin
            break;
        case 0:
            bejelentkezve = false;
            break;
        default:
            break;
        }
    }
}

void Administrator::filmekBetolt()
{
    QFile file("filmek.json");

    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QJsonArray filmekJson = QJsonDocument::fromJson(file.readAll()).object()["filmek"].toArray();
            for(auto item : filmekJson)
            {
                auto elem = item.toObject();

                Film* film = new Film(elem["FID"].toString().toStdString(), elem["cim"].toString().toStdString(),elem["ar"].toInt());
                filmek.push_back(film);
            }
            file.close();
        }else cout << "JSon hiba!" << endl;
    }else cout << "File(ok) hianyoznak!" << endl;
}

void Administrator::ujFilmHozzaadasa()
{
    string id;
    string cim;
    int ar;
    cout << "Adja meg az uj film azonositojat" << endl;
    cin >> id;
    for(auto item : filmek)
    {
        if(item->getFilmID() == id)
        {
            cout << "Mar van ilyen azonositoju film" << endl;
            return;
        }
    }
    cout << "Adja meg az uj film cimet" << endl;
    cin >> cim;
    cout << "Adja meg az uj film arat" << endl;
    cin >> ar;
    bool dontes = true;
    while(dontes)
    {
        cout << "Szeretne letrehozni ezt a filmet:" << endl;
        cout << "\t" << id << " " << cim << " " << ar << " (1/0)" << endl;
        int bemenet;
        cin >> bemenet;
        switch (bemenet) {
        case 1:
            filmek.push_back(new Film(id, cim, ar));
            break;
        case 2:
            dontes = false;
            break;
        default:
            cout << "Nincs ilyen opcio. Irja hogy 1 ha igen, 0 ha nem." << endl;
            break;
        }
    }
}

void Administrator::filmAdatokModositasa()
{
    cout << "Melyik film adatait akarja modositani?" << endl;
    string id;
    cin >> id;
    bool talalat = false;
    auto it = filmek.begin();
    while(it != filmek.end())
    {
        if((*it)->getFilmID() == id)
        {
            talalat = true;
            break;
        }
    }
    if(talalat)
    {
        bool modositas = true;
        while(modositas)
        {
            cout << "Melyik adatot akarja modositani?" << endl;
            cout << "1. Cim modositasa" << endl;
            cout << "2. Ar modositasa" << endl;
            cout << "0. Kilepes a modosito menubol" << endl;
            int bemenet;
            cin >> bemenet;

            int ar;
            string cim;
            switch (bemenet) {
            case 1:
                cout << "Adja meg az uj cimet" << endl;
                cin >> cim;
                (*it)->setCim(cim);
                break;
            case 2:
                cout << "Adja meg az uj arat" << endl;
                cin >> ar;
                (*it)->setAr(ar);
                break;
            case 0:
                modositas = false;
                break;
            default:
                break;
            }
        }
    }
    else
    {
        cout << "Nincs ilyen film" << endl;
    }
}

void Administrator::elofizetesArModositasa()
{
    int ar = 0;
    cout << "Adja meg az uj arat! (vagy 0-t a visszlepeshez)" << endl;
    cin >> ar;
    if(ar != 0)
    {
        Elofizetes::setElofizetesAra(ar);
    }
}

void Administrator::kilepes()
{
    QJsonArray filmekQArray;
    for(auto item : filmek)
    {
        QJsonObject fil;
        fil["FID"] = QString::fromStdString(item->getFilmID());
        fil["cim"] = QString::fromStdString(item->getCim());
        fil["ar"] = item->getAr();
        filmekQArray.push_back(fil);
    }
    QJsonDocument doc(filmekQArray);
    QFile file("hibak.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << doc.toJson();
        file.close();
        cout << "JSON array saved to filmek.json";
    }else cout << "Hiba a hiba lista mentesekor" << endl;

    Mukodteto::kilepes();
}









