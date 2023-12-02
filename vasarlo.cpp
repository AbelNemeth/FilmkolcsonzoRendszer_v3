#include "vasarlo.h"
#include "elofizeto.h"
#include <iostream>

list<Film *> Vasarlo::getSajatFilmek() const
{
    return sajatFilmek;
}

Vasarlo::Vasarlo(string _szID):
    Felhasznalo(_szID)
{

}

Vasarlo::Vasarlo(string _szID, string _jelszo,string _emailCim,int _bankszamlaSzam):
    Felhasznalo(_szID, _jelszo, _emailCim, _bankszamlaSzam)
{

}

Vasarlo::Vasarlo():
    Felhasznalo("")
{

}

void Vasarlo::menu()
{
    sajatAdatokBetolt();
    bool aktiv = true;
    while(aktiv)
    {
        cout << "1. Elofizetes Vasarlasa" << endl;
        cout << "2. Vasarolhato Filmek Listazasa" << endl;
        cout << "3. Sajat Filmek Listazasa" << endl;
        cout << "4. Felhaszanloi adatok megtekintese" << endl;
        cout << "5. Problema bejelentese" << endl;
        cout << "0. Kijelentkezes" << endl;

        int valasz;
        cin >> valasz;

        string bemenet;
        switch (valasz) {
        case 0:
            cout << "Kijelentkes..." << endl;
            aktiv = false;
            break;
        case 1:
            aktiv = elofizetesVasarlasa();
            break;
        case 2:
            vasarolhatoFilmekListaz();
            break;
        case 3:
            sajatFilmekListaz();
            break;
        case 4:
            adatokMegtekintese();
            break;
        case 5:
            cout << "Mi a problema amit be szeretne jelenteni? (irja be hogy '0' a visszalepeshez)" << endl;
            cin >> bemenet;
            problemaJelentese(bemenet, "bejelentett");
            break;
        default:
            cout << "Nincs ilyen opcio" << endl;
            break;
        }
    }
}

void Vasarlo::sajatAdatokBetolt()
{
    QFile vas("vasarlok.json");
    if(vas.exists()){
        if(vas.open(QIODevice::ReadOnly | QIODevice::Text)){
            QJsonArray vasarlokJson = QJsonDocument::fromJson(vas.readAll()).object()["felhasznalok"].toArray();
            for(auto item : vasarlokJson)
            {
                auto elem = item.toObject();
                if(elem["SzID"].toString().toStdString() == szID)
                {
                    jelszo = elem["jelszo"].toString().toStdString();
                    emailCim = elem["emailCim"].toString().toStdString();
                    bankszamlaSzam = elem["bankszamlaSzam"].toString().toInt();

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
                        filmHozzaad(item);
                    }
                }
            }
            vas.close();
        }else cout << "error with json files" << endl;
    }else cout << "File(s) Missing!" << endl;
}

void Vasarlo::adatokMegtekintese()
{
    Felhasznalo::adatokMegtekintese();
    cout << "Tipus: Felhasznalo" << endl << "Sajat Filmjeid: " << endl;
    for(const auto &item : sajatFilmek)
    {
        cout << "\t" << item->getFilmID()<< " " << item->getCim() << endl;
    }
}

bool Vasarlo::elofizetesVasarlasa()
{
    cout << "Irja be hogy 'MEGEROSITES' hogy megerositse a vasarlast" << endl;
    string megerosites;
    cin >> megerosites;
    if(megerosites == "MEGEROSITES")
    {
        if(this->getBankszamlaSzam() != 1234) //itt lenne egy üzenet a banknak
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
                vasarlok.remove(this);
                time_t currentTime = time(nullptr);
                elofizetok.push_back(new Elofizeto(szID, jelszo, emailCim, bankszamlaSzam, 1, currentTime));
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
                cout << "JSON array saved to vasarlok.json";
            }else cout << "Hiba a hiba lista mentesekor" << endl;
            //elofizetok ment
            QJsonDocument docE(elofizetokLista);
            QFile fileE("elofizetok.json");
            if (fileE.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&fileE);
                out << docE.toJson();
                fileE.close();
                cout << "JSON array saved to elofizetok.json";
            }else cout << "Hiba a hiba lista mentesekor" << endl;
            return false;
        }
        else
        {
            cout << "Vasalas nem sikerult" << endl;
            problemaJelentese("nincs eleg penz az adott szamlan.", "tranzakcios");
            return true;
        }
    }
    cout << "Vasarlas megszakitva" << endl;
    return true;
}

bool Vasarlo::filmHozzaad(string filmID)
{
    QFile file("filmek.json");

    bool sikerult = false;

    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QJsonArray filmekJson = QJsonDocument::fromJson(file.readAll()).object()["filmek"].toArray();
            for(auto item : filmekJson)
            {
                auto elem = item.toObject();
                if(elem["FID"].toString().toStdString() == filmID)
                {
                    Film* film = new Film(elem["FID"].toString().toStdString(), elem["cim"].toString().toStdString(),elem["ar"].toString().toInt());
                    sajatFilmek.push_back(film);
                    sikerult = true;
                }
            }
            file.close();
        }else cout << "JSon hiba!" << endl;
    }else cout << "File(ok) hianyoznak!" << endl;


    //vasarlok betolt
    QJsonArray vasarlokLista;
    QFile vas("vasarlok.json");
    if(vas.exists()){
        if(vas.open(QIODevice::ReadOnly | QIODevice::Text)){
            vasarlokLista = QJsonDocument::fromJson(vas.readAll()).object()["felhasznalok"].toArray();
            vas.close();
        }else cout << "error with json files" << endl;
    }else cout << "File(s) Missing!" << endl;

    //vasarlo mentese
    QJsonObject v;
    v["SzID"] = QString::fromStdString(getSzID());
    v["jelszo"] = QString::fromStdString(getJelszo());
    v["emailCim"] = QString::fromStdString(getEmailCim());
    v["bankszamlaSzam"] = QString::number(getBankszamlaSzam());

    ostringstream outputStringStream;
    for(auto item2 : getSajatFilmek())
    {
        outputStringStream << item2->getFilmID() << ";";
    }
    string outputString = outputStringStream.str();
    v["filmLista"] = QString::fromStdString(outputString);

    vasarlokLista.push_back(v);

    //vasarlok ment
    QJsonDocument docV(vasarlokLista);
    QFile fileV("vasarlok.json");
    if (fileV.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&fileV);
        out << docV.toJson();
        fileV.close();
        cout << "JSON array saved to vasarlok.json" << endl;
    }else cout << "Hiba a hiba lista mentesekor" << endl;

    return sikerult;
}

void Vasarlo::vasarolhatoFilmekListaz()
{
    cout << "Vasarolhato filmek listazasa..." << endl;

    QFile file("filmek.json");

    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QJsonArray filmekJson = QJsonDocument::fromJson(file.readAll()).object()["filmek"].toArray();
            for(auto item : filmekJson)
            {
                auto elem = item.toObject();
                for(auto item2 : sajatFilmek)
                {
                    if(elem["FID"].toString().toStdString() == item2->getFilmID())
                    {
                        cout << "\t" << elem["FID"].toString().toStdString() << "\t" << elem["cim"].toString().toStdString() << "\t" << elem["ar"].toString().toInt() << endl;
                    }
                }

            }
            file.close();
        }else cout << "JSon hiba!" << endl;
    }else cout << "File(ok) hianyoznak!" << endl;
}

void Vasarlo::sajatFilmekListaz()
{
    for(auto item : sajatFilmek)
    {
        cout << "\t" << item->getFilmID() << "\t" << item->getCim() << "\t" << item->getAr() << endl;
    }

    cout << "Adjon meg egy filmID-t ha le szeretne jatszani egy filmet! (kilepes : 0)" << endl;
    string bemenet;
    cin >> bemenet;
    if(bemenet == "0") return;
    bool vanIlyen;
    for(auto item : sajatFilmek)
    {
        if(item->getFilmID() == bemenet)
        {
            vanIlyen = true;
            filmLejatszasa(item);
        }
    }
    if(!vanIlyen) cout << "Nincs ilyen filmje" << endl;
}

void Vasarlo::filmVasarlas()
{
    cout << "Adjon meg egy filmID-t amit meg szeretne vasarolni" << endl;

    string id;
    cin >> id;
    if(filmHozzaad(id))
    {
        if(bankszamlaSzam != 1234) // hasonlo a masikhoz, itt is a banknak kuldenenk egy kereset
        {
            cout << "Film sikeresen hozzaadva" << endl;
        }
        else
        {
            cout << "Valami nem sikerult" << endl;
            problemaJelentese("nincs eleg penz az adott szamlan.", "tranzakcios");
        }
    }
    else
    {
        cout << "Nincs ilyen film!" << endl;
    }
}
