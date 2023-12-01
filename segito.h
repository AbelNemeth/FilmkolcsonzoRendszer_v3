#ifndef SEGITO_H
#define SEGITO_H

#include "Elofizetes.h"

#include <mukodteto.h>

class Segito : public Mukodteto
{
public:
    Segito(string _szID);
    Segito();

    void menu();
    void adatokListazasa();

    void problemakKezelese();
    void elofizetesEllenorzese(); // vissza adja hogy kiknek járt le az előfizetésük
    void elofizetesMegszuntetese();

    void kilepes();
};

#endif // SEGITO_H
