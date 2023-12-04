#include "mukodteto.h"

#include "elofizeto.h"
#include "vasarlo.h"

Mukodteto::Mukodteto(string _szID):
    szID(_szID)
{

    hibaListakBeolvas();
    felhasznalokBeolvas();
    elofizetesekBeolvas();
}

void Mukodteto::adatokListazasa()
{
    cout << "Felhasznalok listazasa: " << endl;
    for(auto item : felhasznalok)
    {
        cout << "\tSzID: " << item->getSzID() << " emailCim: " << item->getEmailCim() << " bankszamlaSzam: " << item->getBankszamlaSzam();
        if(Vasarlo* vasarlo = dynamic_cast<Vasarlo*>(item))
        {
            cout << " Filmek: ";
            for(const auto &item2 : vasarlo->getSajatFilmek())
            {
                cout << item2->getFilmID() << " ";
            }
            cout << endl;
        }
        else if(Elofizeto* elofizeto = dynamic_cast<Elofizeto*>(item))
        {
            cout << " Elofizetes tipusa: " << elofizeto->getElofizetesID() << " Elofizetesbol hatralevo ido: " << elofizeto->getHatralevoNapok() << " nap" << endl;
        }
    }
    cout << "Elofizetesek listazasa: " << endl;
    for(auto item : elofizetesek)
    {
        cout << "\tElofizetestipus azonosito: " << item->getElofizetesID() << " Ar: " << item->getElofizetesAra() << endl;
    }
}

void Mukodteto::felhasznaloiAdatokModositasa()
{
    cout << "Milyen tipusu adatot szeretne modositani?" << endl;
    cout << "1. szID" << endl;
    cout << "2. email" << endl;
    cout << "3. BankszamlaSzam" << endl;
    cout << "0. visszalepes" << endl;

    int bemenet;
    cin >> bemenet;

    switch (bemenet) {
    case 1:
        felhaszanloIDModositasa();
        break;
    case 2:
        felhaszanloEmailCimModositasa();
        break;
    case 3:
        felhasznaloBankszamlaSzamModositasa();
        break;
    case 0:
        cout << "Kilepes" << endl;
        break;
    default:
        cout << "Nincs ilyen opcio" << endl;
        break;
    }
}

void Mukodteto::felhaszanloIDModositasa()
{
    cout << "Adja meg melyik felhasznalot akarja modositani" << endl;
    string oldID;
    cin >> oldID;
    cout << "Adja meg az uj ID-t" << endl;
    string newID;
    cin >> newID;
    bool sikerult = false;
    for(auto* item : felhasznalok)
    {
        if(item->getSzID() == oldID)
        {
            item->setSzID(newID);
            cout << "ID sikeresen megaltoztatva!" << endl;
            sikerult = true;
            //if(Vasarlo* vasarlo = dynamic_cast<Vasarlo*>(item))
        }
    }
    if(!sikerult) cout << "Nincs ilyen felhasznalo!" << endl;
}

void Mukodteto::felhaszanloEmailCimModositasa()
{
    cout << "Adja meg melyik felhasznalot akarja modositani" << endl;
    string id;
    cin >> id;
    cout << "Adja meg az uj email cimet" << endl;
    string email;
    cin >> email;
    bool sikerult = false;
    for(auto* item : felhasznalok)
    {
        if(item->getSzID() == id)
        {
            item->setEmailCim(email);
            cout << "Email cim sikeresen megaltoztatva!" << endl;
            sikerult = true;
        }
    }
    if(!sikerult) cout << "Nincs ilyen felhasznalo!" << endl;
}

void Mukodteto::felhasznaloBankszamlaSzamModositasa()
{
    cout << "Adja meg melyik felhasznalot akarja modositani" << endl;
    string id;
    cin >> id;
    cout << "Adja meg az uj bankszamla szamot" << endl;
    int szamlaSzam;
    cin >> szamlaSzam;
    bool sikerult = false;
    for(auto* item : felhasznalok)
    {
        if(item->getSzID() == id)
        {
            item->setBankszamlaSzam(szamlaSzam);
            cout << "Bankszamla szam sikeresen megaltoztatva!" << endl;
            sikerult = true;
        }
    }
    if(!sikerult) cout << "Nincs ilyen felhasznalo!" << endl;
}

void Mukodteto::hibaListakBeolvas()
{
    QFile hib("hibak.json");

    if(hib.exists())
    {
        if(hib.open(QIODevice::ReadOnly | QIODevice::Text))
        {

            QJsonArray hibakJson = QJsonDocument::fromJson(hib.readAll()).array();

            for(auto item : hibakJson)
            {
                auto elem = item.toObject();

                Hiba hiba = *new Hiba(elem["ID"].toString().toInt(), elem["SzID"].toString().toStdString(),elem["leiras"].toString().toStdString());
                if(elem["tipus"].toString().toStdString() == "tranzakcios")
                {
                    tranzakciosHibakLista.push_back(hiba);
                }
                else if(elem["tipus"].toString().toStdString() == "bejelentett")
                {
                    problemakLista.push_back(hiba);
                }
                else cout << "Nem ismert hiba tipus!" << endl;
            }
            hib.close();
        }else cout << "JSon hiba!" << endl;
    }else cout << "File(ok) hianyoznak!" << endl;
}

void Mukodteto::felhasznalokBeolvas()
{
    QFile vas("vasarlok.json");
    QFile elo("elofizetok.json");
    if(vas.exists() && elo.exists()){
        if(vas.open(QIODevice::ReadOnly | QIODevice::Text) && elo.open(QIODevice::ReadOnly | QIODevice::Text)){

            QJsonArray vasarlokJson =       QJsonDocument::fromJson(vas.readAll()).array();
            QJsonArray elofizetokJson =     QJsonDocument::fromJson(elo.readAll()).array();
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

                felhasznalok.push_back(vasarlo);
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
                felhasznalok.push_back(new Elofizeto(SzID, jelszo, emailCim, bankszamlaSzam, elofizetesID, elofizetesMegkezdese));
            }
            vas.close();
            elo.close();
        }else cout << "error with json files" << endl;
    }else cout << "File(s) Missing!" << endl;
}

void Mukodteto::elofizetesekBeolvas()
{
    QFile elo("elofizetesek.json");

    if(elo.exists())
    {
        if(elo.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QJsonArray elofizetesekJson = QJsonDocument::fromJson(elo.readAll()).array();

            for(auto item : elofizetesekJson)
            {
                auto elem = item.toObject();
                elofizetesek.push_back(new Elofizetes(elem["elofizetesTipus"].toString().toInt(),elem["elofizetesAra"].toString().toInt()));
            }
            elo.close();
        }else cout << "JSon hiba!" << endl;
    }else cout << "File(ok) hianyoznak!" << endl;
}

void Mukodteto::tranzakciosHibakKiir()
{
    cout << endl << "hibak listazasa.." << endl;

    if(!tranzakciosHibakLista.empty())
    {
        for(auto& item : tranzakciosHibakLista)
        {
            cout << item.getId() << " : felhasznalao: " << item.getSzID() << endl << "\tTranzakcios hiba: " << item.getLeiras() << " Allapota: " << item.getActiv() << endl;
        }
    }
    else cout << "Nincsenek tranzakcios hibak!" << endl;

    cout << endl;
}

void Mukodteto::problemakListaKiir()
{
    cout << endl << "hibak listazasa.." << endl;

    if(!tranzakciosHibakLista.empty())
    {
        for(auto& item : problemakLista)
        {
            cout << item.getId() << " : felhasznalao: " << item.getSzID() << endl << "\tBejelentett hiba: " << item.getLeiras() << " Allapota: " << item.getActiv() << endl;
        }
    }
    else cout << "Nincsenek tranzakcios hibak!" << endl;

    cout << endl;
}

void Mukodteto::hibaAllapotModositasa()
{
    cout << "Melyik hiba allapotat szeretne megvaltoztatni?" << endl;
    int bemenet;
    cin >> bemenet;
    bool vanIlyen = false;

    for(auto& item : tranzakciosHibakLista)
    {
        if(bemenet == item.getId())
        {
            vanIlyen = true;
            cout << "Mi legyen az uj allapota?(0/1)" << endl;
            int allapot;
            cin >> allapot;
            if(allapot == 1) item.setActiv(true);
            else item.setActiv(false);
        }
    }
    for(auto& item : problemakLista)
    {
        if(bemenet == item.getId())
        {
            vanIlyen = true;
            cout << "Mi legyen az uj allapota?(0/1)" << endl;
            int allapot;
            cin >> allapot;
            item.setActiv(allapot);
            if(allapot == 1) item.setActiv(true);
            else item.setActiv(false);
        }
    }
    if(!vanIlyen) cout << "Nincs ilyen azonositoju hiba" << endl;
}

void Mukodteto::hibaListaTorlese()
{
    cout << "Melyik lista teljesitett hibait akarja torolni?" << endl;
    cout << "1. Tranzakcios hibak" << endl;
    cout << "2. Bejelentett hibak" << endl;
    cout << "3. Mindketto" << endl;

    int bemenet;
    cin >> bemenet;

    if(bemenet == 1)
    {
        for (auto itT = tranzakciosHibakLista.begin(); itT != tranzakciosHibakLista.end();)
        {
            if (!itT->getActiv()) {
                itT = tranzakciosHibakLista.erase(itT);
            } else {
                ++itT; // Move to the next element
            }
        }
    }
    else if(bemenet == 2)
    {
        for (auto itP = problemakLista.begin(); itP != problemakLista.end();)
        {
            if (!itP->getActiv()) {
                itP = problemakLista.erase(itP);
            } else {
                ++itP; // Move to the next element
            }
        }
    }
    else if(bemenet == 3)
    {
        for (auto itT = tranzakciosHibakLista.begin(); itT != tranzakciosHibakLista.end();)
        {
            if (!itT->getActiv()) {
                itT = tranzakciosHibakLista.erase(itT);
            } else {
                ++itT; // Move to the next element
            }
        }
        for (auto itP = problemakLista.begin(); itP != problemakLista.end();)
        {
            if (!itP->getActiv()) {
                itP = problemakLista.erase(itP);
            } else {
                ++itP; // Move to the next element
            }
        }
    }
    else
    {
        cout << "Hibas bemenet" << endl;
    }
}

void Mukodteto::kilepes()
{
    cout << "mukodteto kilepes..." << endl;
    //hibak mentese
    QJsonArray hibakLista;
    for(auto& item : tranzakciosHibakLista)
    {
        if(item.getActiv())
        {
            QJsonObject hiba;
            hiba["ID"] = QString::number(item.getId());
            hiba["SzID"] = QString::fromStdString(item.getSzID());
            hiba["tipus"] = QString::fromStdString("tranzakcios");
            hiba["leiras"] = QString::fromStdString(item.getLeiras());
            hibakLista.append(hiba);
        }
    }
    for(auto& item : problemakLista)
    {
        if(item.getActiv())
        {
            QJsonObject hiba;
            hiba["ID"] = QString::number(item.getId());
            hiba["SzID"] = QString::fromStdString(item.getSzID());
            hiba["tipus"] =  QString::fromStdString("bejelentett");
            hiba["leiras"] = QString::fromStdString(item.getLeiras());
            hibakLista.append(hiba);
        }
    }
    QJsonDocument docH(hibakLista);
    QFile fileH("hibak.json");
    if (fileH.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&fileH);
        out << docH.toJson();
        fileH.close();
        cout << "JSON array saved to hibak.json" << endl;
    }else cout << "Hiba a hiba lista mentesekor" << endl;

    //felhasznalok mentese
    QJsonArray vasarlokLista;
    QJsonArray elofizetokLista;
    for(auto& item : felhasznalok)
    {
        if(Vasarlo* vasarlo = dynamic_cast<Vasarlo*>(item))
        {
            QJsonObject v;
            v["SzID"] = QString::fromStdString(vasarlo->getSzID());
            v["jelszo"] = QString::fromStdString(vasarlo->getJelszo());
            v["emailCim"] = QString::fromStdString(vasarlo->getEmailCim());
            v["bankszamlaSzam"] = QString::number(vasarlo->getBankszamlaSzam());

            ostringstream outputStringStream;
            for(auto item2 : vasarlo->getSajatFilmek())
            {
                outputStringStream << item2->getFilmID() << ";";
            }
            string outputString = outputStringStream.str();
            v["filmLista"] = QString::fromStdString(outputString);

            vasarlokLista.append(v);
        }
        else if(Elofizeto* elofizeto = dynamic_cast<Elofizeto*>(item))
        {
            QJsonObject e;
            e["SzID"] = QString::fromStdString(elofizeto->getSzID());
            e["jelszo"] = QString::fromStdString(elofizeto->getJelszo());
            e["emailCim"] = QString::fromStdString(elofizeto->getEmailCim());
            e["bankszamlaSzam"] = QString::number(elofizeto->getBankszamlaSzam());
            e["elofizetesID"] = QString::number(elofizeto->getElofizetesID());
            e["elofizetesMegkezdese"] = QString::number(elofizeto->getElofizetesMegkezdese());
            elofizetokLista.append(e);
        }
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



    //elofizetesek mentese

    QJsonArray elofizetesekLista;
    for(auto& item : elofizetesek)
    {
        QJsonObject elofizetes;
        elofizetes["elofizetesTipus"] = QString::number(item->getElofizetesID());
        elofizetes["elofizetesAra"] = QString::number(item->getElofizetesAra());
        elofizetesekLista.append(elofizetes);
    }
    QJsonDocument docElofizetes(elofizetesekLista);
    QFile fileElofizetes("elofizetesek.json");
    if (fileElofizetes.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&fileElofizetes);
        out << docElofizetes.toJson();
        fileElofizetes.close();
        cout << "JSON array saved to hibak.json" << endl;
    }else cout << "Hiba a hiba lista mentesekor" << endl;

}

























