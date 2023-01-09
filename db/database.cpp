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

int DBConnect::getRandomFilm(int genre) { // повертає id випадкового фільму 
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(conn, ("SELECT t1.id_film FROM film t1 WHERE t1.id_film IN (SELECT t2.id_film FROM film_genre t2 WHERE id_genre = " + to_string(genre) + ") AND popularity > 25 ORDER BY RAND() LIMIT 1").c_str());
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

double DBConnect::getFilmRate(int id) { // повертає середню оцінку фільму
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(conn, ("SELECT avg_rate FROM rating WHERE id_film = " + to_string(id)).c_str());
    if (res = mysql_store_result(conn)) {
        row = mysql_fetch_row(res);
        mysql_free_result(res);
        return stod(row[0]);
    }
    return -1; 
}

string DBConnect::getUserLogin(int id) { // повертає username по id
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(conn, ("SELECT username FROM user WHERE id_user = " + to_string(id)).c_str());
    if (res = mysql_store_result(conn)) {
        row = mysql_fetch_row(res);
        mysql_free_result(res);
        return row[0];
    }
    return "";
}

int DBConnect::getUserId(string username) { // повертає id по username
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(conn, ("SELECT id_user FROM user WHERE username = " + username).c_str());
    if (res = mysql_store_result(conn)) {
        row = mysql_fetch_row(res);
        mysql_free_result(res);
        return stoi(row[0]);
    }
    return -1;
}

char DBConnect::getViewerSex(int id) { // повертає стать по id
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(conn, ("SELECT sex FROM user WHERE id_user = " + to_string(id)).c_str());
    if (res = mysql_store_result(conn)) {
        row = mysql_fetch_row(res);
        mysql_free_result(res);
        return *row[0];
    }
    return ' ';
}

char DBConnect::getViewerSex(string username) { // повертає стать по username
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(conn, ("SELECT sex FROM user WHERE username = " + username).c_str());
    if (res = mysql_store_result(conn)) {
        row = mysql_fetch_row(res);
        mysql_free_result(res);
        return *row[0];
    }
    return ' ';
}

int DBConnect::getViewerAge(int id) { // повертає вік по id
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(conn, ("SELECT age FROM user WHERE id_user = " + to_string(id)).c_str());
    if (res = mysql_store_result(conn)) {
        row = mysql_fetch_row(res);
        mysql_free_result(res);
        return stoi(row[0]);
    }
    return -1;
}

int DBConnect::getViewerAge(string username) { // повертає вік по username
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(conn, ("SELECT age FROM user WHERE username = " + username).c_str());
    if (res = mysql_store_result(conn)) {
        row = mysql_fetch_row(res);
        mysql_free_result(res);
        return stoi(row[0]);
    }
    return -1;
}

vector<int> DBConnect::getViewerRatedFilms(int id) { // повертає фільми, переглянуті певним користувачем по його id
    MYSQL_RES* res;
    MYSQL_ROW row;
    vector<int> output;
    mysql_query(conn, ("SELECT id_film FROM film_user_rated WHERE id_user = " + to_string(id)).c_str());
    if (res = mysql_store_result(conn)) {
        while(row = mysql_fetch_row(res)) {
            output.push_back(stoi(row[0]));
        }
        return output;
    }
    return {};
}

vector<int> DBConnect::getViewerRatedFilms(string username) { // повертає фільми, переглянуті певним користувачем по його username
    int id = getUserId(username);
    return getViewerRatedFilms(id);
}

int DBConnect::checkAdmin(int id) { // перевіряє, чи адмін користувач по id
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(conn, ("SELECT admin FROM user WHERE id_user = " + to_string(id)).c_str());
    if (res = mysql_store_result(conn)) {
        if (mysql_num_rows(res)) {
            row = mysql_fetch_row(res);
            mysql_free_result(res);
            return stoi(row[0]);
        }
    }
    return -1;
}

int DBConnect::checkAdmin(string username) { // перевіряє, чи адмін користувач по username
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_query(conn, ("SELECT admin FROM user WHERE username = " + username).c_str());
    if (res = mysql_store_result(conn)) {
        if (mysql_num_rows(res)) {
            row = mysql_fetch_row(res);
            mysql_free_result(res);
            return stoi(row[0]);
        }
    }
    return -1;
}

int DBConnect::insertUser(string username, int admin, int age = 0, string sex = "n") { // вносить інформацію про користувача
    int res;
    if (!admin) { // якщо не адмін
        res = mysql_query(conn, ("INSERT INTO user (username, age, sex, admin) VALUES ('" + username + "', " + to_string(age) + ", '" + sex + "', 0)").c_str());
    }
    else { // якщо адмін
        res = mysql_query(conn, ("INSERT INTO user (username, admin) VALUES ('" + username + "', 1)").c_str());
    }
    mysql_commit(conn);
    return res;
}

int DBConnect::insertFilms(int id, map<int, double> films) { // вносить інформацію про переглянуті користувачем фільми
    int status = 0;
    for (auto it : films) {
        if (mysql_query(conn, ("INSERT INTO film_user_rated (id_user, id_film, rate) VALUES (" + to_string(id) + ", " + to_string(it.first) + ", " + to_string(it.second) + ")").c_str())) {
            status = 1;
        }
        mysql_commit(conn);
    }
    return status;
}
