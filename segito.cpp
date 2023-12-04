#include "segito.h"
#include "elofizeto.h"
#include <time.h>
Segito::Segito(string _szID):
    Mukodteto(_szID)
{

}
Segito::Segito():
    Mukodteto("")
{

}

void Segito::menu()
{
    bool bejelentkezve = true;
    while(bejelentkezve)
    {
        cout << "1. Adatok listazasa" << endl;
        cout << "2. Trazakcios hibak listazasa" << endl;
        cout << "3. Bejelentett hibak listazasa" << endl;
        cout << "4. Felhasznaloi adatok modositasa" << endl;
        cout << "5. Problemak megoldasa" << endl;
        cout << "6. Elofizetes ellenorzese" << endl;
        cout << "7. Elofizetes meszuntetese" << endl;
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
            felhasznaloiAdatokModositasa();
            break;
        case 5:
            problemakKezelese();
            break;
        case 6:
            elofizetesEllenorzese();
            break;
        case 7:
            elofizetesMegszuntetese();
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

void Segito::adatokListazasa()
{
    Mukodteto::adatokListazasa();
}

void Segito::problemakKezelese()
{
    cout << "Handling problems" << endl;
}

void Segito::elofizetesEllenorzese()
{
//    cout << "Adjon meg egy felhasznalot" << endl;
//    string id;
//    cin >> id;
//    bool vanIlyen = false;
    cout << "Elofizetok listazasa" << endl;
    for(auto& item : felhasznalok)
    {
//        if(item->getSzID() == id)
//        {
//            vanIlyen = true;
            if(Elofizeto* elofizeto = dynamic_cast<Elofizeto*>(item))
            {
                cout << "Elofizeto: " << elofizeto->getSzID() << " Hatralevo napok szama: ";
                if(elofizeto->getHatralevoNapok() < 0)
                {
                    cout << "AZ ELOFIZETESE LEJART!" << endl;
                }
                else
                {
                    cout << elofizeto->getHatralevoNapok() << endl;
                }
            }
//            else cout << "A felhasznalo nem elofizeto" << endl;
//        }
    }
//    if(!vanIlyen)
//    {
//        cout << "Nincs ilyen felhasznalo!" << endl;
//    }
    cout << "Szeretne megszuntetni egy elofizetest? (i/n)" << endl;
    string bemenet;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin,bemenet);
    if(bemenet == "i") elofizetesMegszuntetese();
    else return;
}

void Segito::elofizetesMegszuntetese()
{
    cout << "Melyik felhasznalo elofizeteset akarja megszuntetni?" << endl;
    string id;
    cin >> id;
    bool vanIlyen = false;
    Elofizeto* elofizetoToDelete;
    for(auto& item : felhasznalok)
    {
        if(item->getSzID()==id)
        {
            if(Elofizeto* elofizeto = dynamic_cast<Elofizeto*>(item))
            {
                vanIlyen = true;
                elofizetoToDelete = elofizeto;
//                Vasarlo* vasarlo = elofizeto->elofizetesLemondasa();
//                felhasznalok.remove(item);
//                felhasznalok.push_back(vasarlo);
//                cout << "Elofizetes sikeresen megszuntetve!" << endl;
            }
        }
    }
    if(!vanIlyen) cout << "Nincs ilyen elofizeto" << endl;
    else
    {
        felhasznalok.remove_if([&](const Felhasznalo* obj){return obj->getSzID() == id;});
        felhasznalok.push_back(elofizetoToDelete->elofizetesLemondasa());
        cout << "Elofizetes sikeresen megszuntetve!" << endl;
    }
}

void Segito::kilepes()
{
    Mukodteto::kilepes();
}





