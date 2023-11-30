#ifndef ELOFIZETES_H
#define ELOFIZETES_H


#include <time.h>
//using namespace std;

class Elofizetes
{
    int elofizetesID;
    static int elofizetesAra;
    time_t elofizetesMegkezdese;
public:
    Elofizetes(int _elofizetesID, time_t _elofizetesMegkezdese);
    Elofizetes() = default;

    int getElofizetesID() const;
    time_t getElofizetesMegkezdese() const;
    static int getElofizetesAra();
    static void setElofizetesAra(int newElofizetesAra);

    int getHatralevoNapok();
};

#endif // ELOFIZETES_H
