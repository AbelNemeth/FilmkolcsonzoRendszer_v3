#ifndef ELOFIZETES_H
#define ELOFIZETES_H



//using namespace std;

class Elofizetes
{
    int elofizetesID;
    int elofizetesAra;
public:
    Elofizetes(int _elofizetesID,int _elofizetesAra);
    Elofizetes() = default;

    void adatokMegtekintese();

    int getElofizetesID() const;
    int getElofizetesAra();
    void setElofizetesAra(int newElofizetesAra);
};

#endif // ELOFIZETES_H
