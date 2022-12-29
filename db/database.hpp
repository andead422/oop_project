#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>
#include <string>
#include <mysql/mysql.h>

#include "secret.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::to_string;

class DBConnect
{
protected:
    DBConnect();

    static DBConnect* connection;

    MYSQL* conn = NULL;

public:
    DBConnect(DBConnect &) = delete;
    void operator=(const DBConnect &) = delete;

    static DBConnect* GetInstance();

    int getGenresNumber();
    const int getFilmsNumber();
    string getFilmName(int);
    string getFilmDirector(int);
    vector<int> getFilmGenres(int);
    vector<string> getFilmCast(int);
};



#endif
