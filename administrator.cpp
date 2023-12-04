#include "administrator.h"

Administrator::Administrator(string _szID):
    Mukodteto(_szID)
{
    filmekBetolt();
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
        cout << "1. Adatok listazasa" << endl;
        cout << "2. Trazakcios hibak listazasa" << endl;
        cout << "3. Bejelentett hibak listazasa" << endl;
        cout << "4. Hiba modositasa" << endl;
        cout << "5. Befejezett hibak torlese" << endl;
        cout << "6. Felhasznaloi adatok modositasa" << endl;
        cout << "7. Uj Film Hozzadadasa" << endl;
        cout << "8. Egy film adatainak modositasa" << endl;
        cout << "9. Elofizetes aranak megvaltoztatasa" << endl;
        cout << "0. Kijelentkezes" << endl;

        int bemenet;
        cin >> bemenet;

        switch (bemenet) {
        case 1:
            adatokListazasa();
            break;
        case 2:
            tranzakciosHibakKiir();
            break;
        case 3:
            problemakListaKiir();
            break;
        case 4:
            hibaAllapotModositasa();
            break;
        case 5:
            hibaListaTorlese();
            break;
        case 6:
            felhasznaloiAdatokModositasa();
            break;
        case 7:
            ujFilmHozzaadasa(); //admin
            break;
        case 8:
            filmAdatokModositasa(); //admin
            break;
        case 9:
            elofizetesArModositasa(); //admin
            break;
        case 0:
            bejelentkezve = false;
            break;
        default:
            break;
        }
    }
    kilepes();
}

void Administrator::adatokListazasa()
{
    Mukodteto::adatokListazasa();
    cout << "Filmek Listazasa: " << endl;
    for(auto item : filmek)
    {
        cout << "\tID: " << item->getFilmID() << " Cim: " << item->getCim() << " Ar: " << item->getAr() << endl;
    }
}

void Administrator::filmekBetolt()
{
    QFile file("filmek.json");

    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QJsonArray filmekJson = QJsonDocument::fromJson(file.readAll()).array();
            for(auto item : filmekJson)
            {
                auto elem = item.toObject();

                Film* film = new Film(elem["FID"].toString().toStdString(), elem["cim"].toString().toStdString(), elem["ar"].toString().toInt());
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
    int id;
    cout << "Adjon meg az elofizetes azonositojat (vagy 0-t a visszlepeshez)" << endl;
    cin >> id;
    bool vanIlyen = false;
    if(id!=0)
    {
        for(auto& item : elofizetesek)
        {
            if(item->getElofizetesID()==id)
            {
                vanIlyen = true;
                int ar = 0;
                cout << "Adja meg az uj arat! (vagy 0-t a visszlepeshez)" << endl;
                cin >> ar;
                if(ar != 0) item->setElofizetesAra(ar);
            }
        }
    }
    if(!vanIlyen) cout << "Nincs ilyen id" << endl;

}

void Administrator::kilepes()
{
    cout << "admin kilepes..." << endl;
    //filmek save
    QJsonArray filmekQArray;
    for(auto item : filmek)
    {
        QJsonObject fil;
        fil["FID"] = QString::fromStdString(item->getFilmID());
        fil["cim"] = QString::fromStdString(item->getCim());
        fil["ar"] = QString::number(item->getAr());
        filmekQArray.push_back(fil);
    }
    QJsonDocument doc(filmekQArray);
    QFile file("hibak.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << doc.toJson();
        file.close();
        cout << "JSON array saved to filmek.json" << endl;
    }else cout << "Hiba a hiba lista mentesekor" << endl;

    Mukodteto::kilepes();
}









