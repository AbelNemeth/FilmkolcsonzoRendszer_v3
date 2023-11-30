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
        cout << "1. Trazakcios hibak listazasa" << endl;
        cout << "2. Bejelentett hibak listazasa" << endl;
        cout << "3. Felhasznaloi adatok modositasa" << endl;
        cout << "4. Problemak megoldasa" << endl;
        cout << "5. Elofizetes ellenorzese" << endl;
        cout << "6. Elofizetes meszuntetese" << endl;
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
            felhasznaloiAdatokModositasa();
            break;
        case 4:
            problemakKezelese();
            break;
        case 5:
            elofizetesEllenorzese();
            break;
        case 6:
            elofizetesMegszuntetese();
            break;
        case 0:
            bejelentkezve = false;
            break;
        default:
            break;
        }
    }
}

void Segito::problemakKezelese()
{
    cout << "Handling problems" << endl;
}

void Segito::elofizetesEllenorzese()
{
    cout << "Adjon meg egy felhasznalot" << endl;
    string id;
    cin >> id;
    bool vanIlyen = false;
    for(auto& item : felhasznalok)
    {
        if(item->getSzID() == id)
        {
            vanIlyen = true;
            if(Elofizeto* elofizeto = dynamic_cast<Elofizeto*>(item))
            {
                if(elofizeto.)
            }
        }
    }
}





