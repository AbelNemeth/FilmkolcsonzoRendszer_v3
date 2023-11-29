#ifndef FILM_H
#define FILM_H

#include <string>

using namespace std;

class Film
{
private:
    string filmID;
    string cim;
    int hosszPercben;
    int ar;
public:
    Film(string _filmID, string _cim, int _hossz, int _ar);

    void lejatszas();

    string getFilmID() const;
    string getCim() const;
    void setCim(const string &newCim);
    int getHosszPercben() const;
    void setHosszPercben(int newHosszPercben);
    int getAr() const;
    void setAr(int newAr);
};

#endif // FILM_H
