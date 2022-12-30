#include "database.hpp"

DBConnect::DBConnect() {
    while (conn == NULL) {
        conn = mysql_init(NULL);
    }
    // Подключаемся к серверу
    if(!mysql_real_connect(conn, "localhost", getUser().c_str(), getPass().c_str(), getDB().c_str(), 0, NULL, 0)) {
        cout << "database connecting error" << endl;
    }
    else {
        mysql_set_character_set(conn, "utf8");
    }
}

DBConnect* DBConnect::connection = nullptr;

DBConnect* DBConnect::GetInstance() {
    if(connection == nullptr) {
        connection = new DBConnect();
    }
    return connection;
}

vector<int> DBConnect::getFilmGenres(int id) {
    MYSQL_RES* res;
    MYSQL_ROW row;
    vector<int> output;
    mysql_query(conn, ("SELECT id_genre FROM film_genre WHERE id_film = " + to_string(id)).c_str());
    if (res = mysql_store_result(conn)) {
        while(row = mysql_fetch_row(res)) {
            output.push_back((int)row[0]);
        }
    }
    return output;
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

int DBConnect::getFilmYear(int) {
    return 2019;
}

string DBConnect::getFilmDirector(int) {
    return "Damien Chazelle";
}

vector<string> DBConnect::getFilmCast(int) {
    return {"Emily Jean", "Ryan Thomas Gosling"};
}

FilmViewer DBConnect::getRandFilm() {
    return FilmViewer(100);
}
//parilka