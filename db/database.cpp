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

DBConnect* DBConnect::connection = NULL;

DBConnect* DBConnect::getInstance() {
    if(connection == NULL) {
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
    MYSQL_RES* res;
    int output;
    mysql_query(conn, "SELECT * FROM genre");
    if (res = mysql_store_result(conn)) {
        output = mysql_num_rows(res);
        mysql_free_result(res);
        return output;
    }
}

const int DBConnect::getFilmsNumber() {
    MYSQL_RES* res;
    int output;
    mysql_query(conn, "SELECT * FROM film");
    if (res = mysql_store_result(conn)) {
        output = mysql_num_rows(res);
        mysql_free_result(res);
        return output;
    }
}

int DBConnect::getRandomFilm() {
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(conn, "SELECT id_film FROM film ORDER BY RAND() LIMIT 1");
    if (res = mysql_store_result(conn)) {
        row = mysql_fetch_row(res);
        mysql_free_result(res);
        return stoi(row[0]);
    }
}

string DBConnect::getFilmTitleYear(int id) {
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(conn, ("SELECT title, release_year FROM film WHERE id_film = " + to_string(id)).c_str());
    if (res = mysql_store_result(conn)) {
        row = mysql_fetch_row(res);
        mysql_free_result(res);
        return row[0] + (char*)" (" + row[1] + (char*)")";
    }
}

string DBConnect::getFilmDirector(int id) {
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(conn, ("SELECT d.full_name FROM director d WHERE d.id_dir = (SELECT fd.id_dir FROM film_dir fd WHERE fd.id_film = " + to_string(id) + ")").c_str());
    if (res = mysql_store_result(conn)) {
        row = mysql_fetch_row(res);
        mysql_free_result(res);
        return row[0];
    }
}

vector<string> DBConnect::getFilmCast(int id) {
    MYSQL_RES* res;
    MYSQL_ROW row;
    vector<string> output;
    mysql_query(conn, ("SELECT a.full_name FROM actor a WHERE a.id_act IN (SELECT fa.id_act FROM film_act fa WHERE fa.id_film = " + to_string(id) + ")").c_str());
    if (res = mysql_store_result(conn)) {
        while(row = mysql_fetch_row(res)) {
            output.push_back(row[0]);
        }
        mysql_free_result(res);
        return output;
    }
}
