#include "database.hpp"

vector<int> DBConnect::getFilmGenres(int id) {
    return {1, 10 , 5};
}

int DBConnect::getGenresNumber() {
    return 19;
}

int DBConnect::getFilmsNumber() {
    return 100500;
}

string getFilmName(int) {
    return "LA LA LAND";
}

string getFilmDirector(int) {
    return "Damien Chazelle";
}

vector<string> getFilmCast(int) {
    return {"Emily Jean", "Ryan Thomas Gosling"};
}
//parilka