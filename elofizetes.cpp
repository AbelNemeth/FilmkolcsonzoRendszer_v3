#include "elofizetes.h"

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

Elofizetes::Elofizetes(int _elofizetesID, int _elofizetesAra):
    elofizetesID(_elofizetesID),
    elofizetesAra(_elofizetesAra)
{

}

