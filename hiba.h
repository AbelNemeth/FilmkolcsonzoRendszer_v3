#ifndef HIBA_H
#define HIBA_H

#include <string>

using namespace std;


class Hiba
{
    int id;
    string szID;
    string leiras;
    string tipus;
    bool activ;
public:
    Hiba(int id, string szID, string leiras);
    Hiba(int id, string szID, string tipus, string leiras);

    int getId() const;
    string getSzID() const;
    string getLeiras() const;
    bool getActiv() const;
    void setActiv(bool newActiv);
    string getTipus() const;
};

#endif // HIBA_H
