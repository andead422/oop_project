#ifndef user
#define user

#include "../film/film.hpp"
#include "../includes.hpp"

class User {
    int idUser;
    static int userCount;

public:
    User(): idUser(userCount++) {}
    //User(int idUser): idUser(idUser) {}
    User(const User&) = default;
    ~User() = default;

    int getIdU() { return idUser; }
    //User& setIdU(int idUser) { this->idUser = idUser; return *this; }
};

#endif