#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>
#include <string>
#include <mysql/mysql.h>

#include "../secrets/secret.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::to_string;
using std::stoi;

class DBConnect
{
protected:
    DBConnect();

    static DBConnect* connection;

    MYSQL* conn = NULL;

public:
    DBConnect(DBConnect &) = delete;
    void operator=(const DBConnect &) = delete;

    static DBConnect* getInstance();

    int getGenresNumber();
    int getRandomFilm();
    const int getFilmsNumber();
    string getFilmTitleYear(int);
    string getFilmDirector(int);
    vector<int> getFilmGenres(int);
    vector<string> getFilmCast(int);
};



#endif
