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

int Elofizetes::getHatralevoNapok()
{
    time_t currentTime;
    time(&currentTime); // Get the current time

    // Calculate the difference in seconds between the two times
    double secondsDiff = difftime(currentTime, elofizetesMegkezdese);

    // Convert seconds to days (1 day = 86400 seconds)
    int daysPassed = (int)(secondsDiff / 86400);

    return daysPassed;
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

