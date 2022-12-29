#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>

using std::vector;
using std::string;

class DBConnect {
    //parilka
public:
    int getGenresNumber();
    const int getFilmsNumber();
    string getFilmName(int);
    string getFilmDirector(int);
    vector<int> getFilmGenres(int);
    vector<string> getFilmCast(int);
};

    // DBConnect() = default;
    // DBConnect(const DBConnect&) = delete;
    // ~DBConnect() = default;

#endif
