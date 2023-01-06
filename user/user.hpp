#ifndef USER_H
#define USER_H

#include "../film/film.hpp"
#include "../includes.hpp"

class User {
    int idUser;
    static int userCount;
protected:
    string login;

public:
    User() = default;    
    User(string login) : idUser(++userCount), login(login) {}
    User(int idUser) : idUser(max(++userCount, idUser)){}
    User(int idUser, string login) : idUser(max(++userCount, idUser)), login(login) {}
    User(const User&) = default;
    ~User() = default;

    int getIdUser() const { return idUser; }
    User& setIdUser(int);

    virtual void printInfo() const = 0;
};

#endif