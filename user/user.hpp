#ifndef USER_H
#define USER_H

#include "../film/film.hpp"
#include "../includes.hpp"

class User {
    int idUser;
    static int userCount;

public:
    User(): idUser(userCount++) {}
    User(int idUser) { userCount++; this->idUser = max(userCount, idUser); }
    User(const User&) = delete;
    ~User() = default;

    int getIdU() const { return idUser; }
    User& setIdU(int);
};

#endif