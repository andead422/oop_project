#include "database.hpp"

vector<int> DBConnect::getFilmGenres(int id) {
    return {1, 10 , 5};
}

int DBConnect::getGenresNumber() {
    return 19;
}

const int DBConnect::getFilmsNumber() {
    return 100500;
}

string DBConnect::getFilmName(int) {
    return "LA LA LAND";
}

string DBConnect::getFilmDirector(int) {
    return "Damien Chazelle";
}

vector<string> DBConnect::getFilmCast(int) {
    return {"Emily Jean", "Ryan Thomas Gosling"};
}
//parilka