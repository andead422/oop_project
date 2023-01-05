#include "database.hpp"

DBConnect::DBConnect() { // конструктор класу для з'єднання з базою даних
    while (conn == NULL) { // поки не вдасться встановити з'єднання з бд, повторюємо спроби
        conn = mysql_init(NULL);
    }
    if(!mysql_real_connect(conn, "localhost", getUser().c_str(), getPass().c_str(), getDB().c_str(), 0, NULL, 0)) { // логінимось у нашу бд за допомогою username та password
        cout << "database connecting error" << endl; // якщо не вдалося, видаємо повідомлення про помилку
    }
    else {
        mysql_set_character_set(conn, "utf8"); // якщо все добре, перемикаємо кодування на utf8
    }
}

vector<int> DBConnect::getFilmGenres(int id) { // повертає масив id жанрів для деякого фільму
    MYSQL_RES* res;
    MYSQL_ROW row;
    vector<int> output;
    mysql_query(conn, ("SELECT id_genre FROM film_genre WHERE id_film = " + to_string(id)).c_str());
    if (res = mysql_store_result(conn)) {
        while(row = mysql_fetch_row(res)) {
            output.push_back(stoi(row[0]));
        }
        return output;
    }
    return {};
}

int DBConnect::getGenresNumber() { // повертає список жанрів та їхні id
    MYSQL_RES* res;
    int output;
    mysql_query(conn, "SELECT * FROM genre");
    if (res = mysql_store_result(conn)) {
        output = mysql_num_rows(res);
        mysql_free_result(res);
        return output;
    }
    return 0;
}

const int DBConnect::getFilmsNumber() { // повертає кількість фільмів
    MYSQL_RES* res;
    int output;
    mysql_query(conn, "SELECT * FROM film");
    if (res = mysql_store_result(conn)) {
        output = mysql_num_rows(res);
        mysql_free_result(res);
        return output;
    }
    return 0;
}

int DBConnect::getRandomFilm() { // повертає id випадкового фільму
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(conn, "SELECT id_film FROM film ORDER BY RAND() LIMIT 1");
    if (res = mysql_store_result(conn)) {
        row = mysql_fetch_row(res);
        mysql_free_result(res);
        return stoi(row[0]);
    }
    return 0;
}

string DBConnect::getFilmTitleYear(int id) { // повертає назву та рік випуску деякого фільму
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(conn, ("SELECT title, release_year FROM film WHERE id_film = " + to_string(id)).c_str());
    if (res = mysql_store_result(conn)) {
        row = mysql_fetch_row(res);
        mysql_free_result(res);
        return row[0] + string(" (") + row[1] + string(")");
    }
    return "";
}

string DBConnect::getFilmDirector(int id) { // повертає ім'я режисера фільму
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(conn, ("SELECT d.full_name FROM director d WHERE d.id_dir = (SELECT fd.id_dir FROM film_dir fd WHERE fd.id_film = " + to_string(id) + ")").c_str());
    if (res = mysql_store_result(conn)) {
        row = mysql_fetch_row(res);
        mysql_free_result(res);
        return row[0];
    }
    return "";
}

vector<string> DBConnect::getFilmCast(int id) { // повертає масив імен акторів
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
    return {};
}
