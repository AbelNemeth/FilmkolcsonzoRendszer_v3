#ifndef HIBA_H
#define HIBA_H

#include <string>

using namespace std;


class Hiba
{
    int id;
    string szID;
    string leiras;
    bool activ;
public:
    Hiba(int id, string szID, string leiras);

    int getId() const;
    string getSzID() const;
    string getLeiras() const;
    bool getActiv() const;
    void setActiv(bool newActiv);
};

#endif // HIBA_H
