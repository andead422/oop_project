#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>
#include <string>
#include <mysql/mysql.h>

#include "../secrets/secret.hpp"
#include "../singleton/singleton.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::to_string;
using std::stoi;

class DBConnect: public Singleton<DBConnect> { // наслідування від шаблону
protected:
    DBConnect(); // конструктор захищений, аби його неможливо було викликати ззовні класу

    MYSQL* conn = NULL;
public:

    int getGenresNumber();
    int getRandomFilm();
    const int getFilmsNumber();
    string getFilmTitleYear(int);
    string getFilmDirector(int);
    vector<int> getFilmGenres(int);
    vector<string> getFilmCast(int);
};



#endif
