#ifndef FILM_H
#define FILM_H

#include <string>

using namespace std;

class Film
{
private:
    string filmID;
    string cim;
    int ar;
public:
    Film(string _filmID, string _cim, int _ar);
    Film() = default;

    void lejatszas();

    string getFilmID() const;
    string getCim() const;
    void setCim(const string &newCim);
    int getAr() const;
    void setAr(int newAr);
};

#endif // FILM_H
