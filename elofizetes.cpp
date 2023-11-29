#include "elofizetes.h"

int Elofizetes::elofizetesAra = 500;

int Elofizetes::getElofizetesID() const
{
    return elofizetesID;
}

int Elofizetes::getElofizetesAra()
{
    return elofizetesAra;
}

void Elofizetes::setElofizetesAra(int newElofizetesAra)
{
    elofizetesAra = newElofizetesAra;
}

time_t Elofizetes::getElofizetesMegkezdese() const
{
    return elofizetesMegkezdese;
}

Elofizetes::Elofizetes(int _elofizetesID, time_t _elofizetesMegkezdese):
    elofizetesID(_elofizetesID),
    elofizetesMegkezdese(_elofizetesMegkezdese)
{

}

