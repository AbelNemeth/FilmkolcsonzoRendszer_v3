#include "administrator.h"

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
            ujFilmHozzaadasa();
            break;
        case 7:
            filmAdatokModositasa();
            break;
        case 8:
            elofizetesArModositasa();
            break;
        case 0:
            bejelentkezve = false;
            break;
        default:
            break;
        }
    }
}
