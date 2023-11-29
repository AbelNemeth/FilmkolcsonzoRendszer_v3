#ifndef SEGITO_H
#define SEGITO_H

#include <mukodteto.h>

class Segito : public Mukodteto
{
public:
    Segito(string _szID);
    Segito();

    void menu();

    void problemakKezelese();
    void elofizetesEllenorzese();
    void elofizetesMegszuntetese();
};

#endif // SEGITO_H
