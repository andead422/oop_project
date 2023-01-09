#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <mysql/mysql.h>

#include "../secrets/secret.hpp"
#include "../singleton/singleton.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::map;
using std::string;
using std::to_string;
using std::stoi;
using std::stod;

class DBConnect: public Singleton<DBConnect> { // наслідування від шаблону
protected:
    DBConnect(); // конструктор захищений, аби його неможливо було викликати ззовні класу

    MYSQL* conn = NULL;
public:
    // DBConnect();
    int getGenresNumber();
    const int getFilmsNumber();
    int getRandomFilm(int);
    string getFilmTitleYear(int);
    string getFilmDirector(int);
    vector<int> getFilmGenres(int);
    vector<string> getFilmCast(int);
    double getFilmRate(int);

    string getUserLogin(int);
    char getViewerSex(int);
    int getViewerAge(int);
    vector<int> getViewerRatedFilms(int);
    int checkAdmin(int);

    int getUserId(string);
    char getViewerSex(string);
    int getViewerAge(string);
    vector<int> getViewerRatedFilms(string);
    int checkAdmin(string);

    int insertUser(string, int, int, string);
    int insertFilms(int, map<int, double>);

    friend class Singleton;

};



#endif
