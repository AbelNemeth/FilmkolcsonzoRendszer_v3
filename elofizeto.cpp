#include "elofizeto.h"
#include "elofizetes.h"
#include <iostream>

int Elofizeto::getElofizetesID() const
{
    return elofizetesID;
}

time_t Elofizeto::getElofizetesMegkezdese() const
{
    return elofizetesMegkezdese;
}

int Elofizeto::getHatralevoNapok()
{
    time_t currentTime;
    time(&currentTime); // Get the current time

    // Calculate the difference in seconds between the two times
    double secondsDiff = difftime(elofizetesMegkezdese, currentTime);

    // Convert seconds to days (1 day = 86400 seconds)
    int daysPassed = (int)(secondsDiff / 86400);

    return daysPassed;
}

Elofizeto::Elofizeto(string _szID):
    Felhasznalo(_szID)
{

}

Elofizeto::Elofizeto(string _szID, string _jelszo, string _emailCim, int _bankszamlaSzam, int _elofizetesID, time_t _elofizetesMegkezdese):
    Felhasznalo(_szID, _jelszo, _emailCim, _bankszamlaSzam),
    elofizetesID(_elofizetesID),
    elofizetesMegkezdese(_elofizetesMegkezdese)
{

}

Elofizeto::Elofizeto():
    Felhasznalo("")
{

}

void Elofizeto::menu()
{
    this->sajatAdatokBetolt();
    bool aktiv = true;
    while(aktiv)
    {
        cout << "1. Elofizetes megtekintese" << endl;
        cout << "2. Filmek listazasa" << endl;
        cout << "3. Felhaszanloi adatok megtekintese" << endl;
        cout << "4. Elofizetes lemondasa" << endl;
        cout << "5. Problema bejelentese" << endl;
        cout << "0. Kijelentkezes" << endl;

        int valasz;
        cin >> valasz;

        string jelentes;
        switch (valasz) {
        case 0:
            cout << "Kijelentkes..." << endl;
            aktiv = false;
            break;
        case 1:
            elofizetesMegtekintese();
            break;
        case 2:
            filmekListazasa();
            break;
        case 3:
            adatokMegtekintese();
            break;
        case 4:
            aktiv = elofizetesLemondasMegkezdese();
            break;
        case 5:
            cout << "Mi a problema amit be szeretne jelenteni? (irja be hogy '0' a visszalepeshez)" << endl;
            cin >> jelentes;
            problemaJelentese(jelentes, "bejelentett");
            break;
        default:
            cout << "Nincs ilyen opcio" << endl;
            break;
        }
    }
}

void Elofizeto::sajatAdatokBetolt()
{
    cout << "loading files..." << endl;
    QFile elo("elofizetok.json");
    if(elo.exists()){
        if(elo.open(QIODevice::ReadOnly | QIODevice::Text)){
            QJsonArray elofizetokJson = QJsonDocument::fromJson(elo.readAll()).object()["elofizetok"].toArray();

            for(auto item : elofizetokJson)
            {
                auto elem = item.toObject();
                string id = elem["SzID"].toString().toStdString();
                if(id == szID)
                {
                    jelszo = elem["jelszo"].toString().toStdString();
                    emailCim = elem["emailCim"].toString().toStdString();
                    bankszamlaSzam = elem["bankszamlaSzam"].toString().toInt();
                    elofizetesID = elem["elofizetesID"].toString().toInt();
                    elofizetesMegkezdese = elem["elofizetesMegkezdese"].toString().toInt();

                }
            }
            elo.close();
        }else cout << "error with json files" << endl;
    }else cout << "File(s) Missing!" << endl;
}

void Elofizeto::adatokMegtekintese()
{
    Felhasznalo::adatokMegtekintese();
    cout << " Tipus: Elofizeto" << endl;
}

void Elofizeto::elofizetesMegtekintese()
{
    //Elofizetes* elofizetes = nullptr;
    QFile elo("elofizetesek.json");

    if(elo.exists())
    {
        if(elo.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QJsonArray elofizetesekJson = QJsonDocument::fromJson(elo.readAll()).object()["elofizetesek"].toArray();
            for(auto item : elofizetesekJson)
            {
                auto elem = item.toObject();
                int id = elem["elofizetesTipus"].toString().toInt();
                if(id == this->getElofizetesID())
                {
                    //elofizetes = new Elofizetes(elem["elofizetesTipus"].toString().toInt(),elem["elofizetesAra"].toString().toInt());
                    cout << "Elofizetesi statusz: Elofizeto Elofizetes ara: " << elem["elofizetesTipus"].toString().toInt() << " Elofizetesbol hatralevo napok: " << elem["elofizetesAra"].toString().toInt() << endl;
                }
            }
            elo.close();
        }else cout << "JSon hiba!" << endl;
    }else cout << "File(ok) hianyoznak!" << endl;

    //if(elofizetes != nullptr)cout << "Elofizetesi statusz: Elofizeto Elofizetes ara: " << elofizetes->getElofizetesAra() << " Elofizetesbol hatralevo napok: " << this->getHatralevoNapok() << endl;
}

Vasarlo *Elofizeto::elofizetesLemondasa()
{
    return new Vasarlo(this->getSzID(), this->getJelszo(), this->getEmailCim(), this->getBankszamlaSzam());
}

bool Elofizeto::elofizetesLemondasMegkezdese()
{
    cout << "Irja be hogy 'MEGEROSITES' hogy megerositse a lemondast" << endl;
    string megerosites;
    cin >> megerosites;
    if(megerosites == "MEGEROSITES")
    {
        list<Vasarlo*> vasarlok;
        list<Elofizeto*> elofizetok;
        QFile vas("vasarlok.json");
        QFile elo("elofizetok.json");
        if(vas.exists() && elo.exists()){
            if(vas.open(QIODevice::ReadOnly | QIODevice::Text) && elo.open(QIODevice::ReadOnly | QIODevice::Text)){

                QJsonArray vasarlokJson =       QJsonDocument::fromJson(vas.readAll()).object()["felhasznalok"].toArray();
                QJsonArray elofizetokJson =     QJsonDocument::fromJson(elo.readAll()).object()["elofizetok"].toArray();
                for(auto item : vasarlokJson)
                {
                    auto elem = item.toObject();
                    string SzID = elem["SzID"].toString().toStdString();
                    string jelszo = elem["jelszo"].toString().toStdString();
                    string emailCim = elem["emailCim"].toString().toStdString();
                    int bankszamlaSzam = elem["bankszamlaSzam"].toString().toInt();
                    Vasarlo* vasarlo =new Vasarlo(SzID, jelszo, emailCim, bankszamlaSzam);

                    string inputString = elem["filmLista"].toString().toStdString();
                    // Vector to store the substrings
                    std::vector<std::string> substrings;

                    // Use std::istringstream to split the string
                    std::istringstream ss(inputString);
                    std::string token;

                    while (std::getline(ss, token, ';'))
                    {
                        substrings.push_back(token);
                    }

                    for(auto& item : substrings)
                    {
                        vasarlo->filmHozzaad(item);
                    }

                    vasarlok.push_back(vasarlo);
                }
                for(auto item : elofizetokJson)
                {
                    auto elem = item.toObject();
                    string SzID = elem["SzID"].toString().toStdString();
                    string jelszo = elem["jelszo"].toString().toStdString();
                    string emailCim = elem["emailCim"].toString().toStdString();
                    int bankszamlaSzam = elem["bankszamlaSzam"].toString().toInt();
                    int elofizetesID = elem["elofizetesID"].toString().toInt();
                    time_t elofizetesMegkezdese = elem["elofizetesMegkezdese"].toString().toInt();
                    elofizetok.push_back(new Elofizeto(SzID, jelszo, emailCim, bankszamlaSzam, elofizetesID, elofizetesMegkezdese));
                }
                vas.close();
                elo.close();
            }else cout << "error with json files" << endl;
        }else cout << "File(s) Missing!" << endl;


        {//listák aátírása
            elofizetok.remove(this);
            vasarlok.push_back(elofizetesLemondasa());
        }

        //felhasznalok mentese
        QJsonArray vasarlokLista;
        QJsonArray elofizetokLista;
        for(auto& item : vasarlok)
        {
            QJsonObject v;
            v["SzID"] = QString::fromStdString(item->getSzID());
            v["jelszo"] = QString::fromStdString(item->getJelszo());
            v["emailCim"] = QString::fromStdString(item->getEmailCim());
            v["bankszamlaSzam"] = QString::number(item->getBankszamlaSzam());

            ostringstream outputStringStream;
            for(auto item2 : item->getSajatFilmek())
            {
                outputStringStream << item2->getFilmID() << ";";
            }
            string outputString = outputStringStream.str();
            v["filmLista"] = QString::fromStdString(outputString);

            vasarlokLista.push_back(v);
        }
        for(auto& item : elofizetok)
        {
            QJsonObject e;
            e["SzID"] = QString::fromStdString(item->getSzID());
            e["jelszo"] = QString::fromStdString(item->getJelszo());
            e["emailCim"] = QString::fromStdString(item->getEmailCim());
            e["bankszamlaSzam"] = QString::number(item->getBankszamlaSzam());
            e["elofizetesID"] = QString::number(item->getElofizetesID());
            elofizetokLista.push_back(e);
        }
        //vasarlok ment
        QJsonDocument docV(vasarlokLista);
        QFile fileV("vasarlok.json");
        if (fileV.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&fileV);
            out << docV.toJson();
            fileV.close();
            cout << "JSON array saved to vasarlok.json" << endl;
        }else cout << "Hiba a hiba lista mentesekor" << endl;
        //elofizetok ment
        QJsonDocument docE(elofizetokLista);
        QFile fileE("elofizetok.json");
        if (fileE.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&fileE);
            out << docE.toJson();
            fileE.close();
            cout << "JSON array saved to elofizetok.json" << endl;
        }else cout << "Hiba a hiba lista mentesekor" << endl;
        return false;
    }

    cout << "Lemondas megszakitva" << endl;
    return true;
}

void Elofizeto::filmekListazasa()
{
    cout << "Filmek listazasa..." << endl;

    QFile file("filmek.json");
    list<Film*> filmek;
    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QJsonArray filmekJson = QJsonDocument::fromJson(file.readAll()).object()["filmek"].toArray();
            for(auto item : filmekJson)
            {
                auto elem = item.toObject();
                cout << "\t" << elem["FID"].toString().toStdString() << "\t" << elem["cim"].toString().toStdString() << "\t" << elem["ar"].toString().toInt() << endl;

                Film* film = new Film(elem["FID"].toString().toStdString(), elem["cim"].toString().toStdString(),elem["ar"].toString().toInt());
                filmek.push_back(film);
            }
            file.close();
        }else cout << "JSon hiba!" << endl;
    }else cout << "File(ok) hianyoznak!" << endl;

    cout << "Adjon meg egy filmID-t ha le szeretne jatszani egy filmet! (kilepes : 0)" << endl;
    string bemenet;
    cin >> bemenet;
    if(bemenet == "0") return;
    bool vanIlyen;
    for(auto item : filmek)
    {
        if(item->getFilmID() == bemenet)
        {
            vanIlyen = true;
            filmLejatszasa(item);
        }
    }
    if(!vanIlyen) cout << "Nincs ilyen filmje" << endl;
}
