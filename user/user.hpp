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
    User(): idUser(++userCount) {}
    User(string login) : idUser(database->getUserId(login)), login(login) {}
    User(int idUser) : idUser(idUser), login(database->getUserLogin(idUser)){}
    User(int idUser, string login) : idUser(max(++userCount, idUser)), login(login) {}
    User(const User&) = default;
    ~User() = default;

    int getId() const { return idUser; }
    string getLogin() const { return login; }

    User& setId(int);
    User& setLogin(string login) { this->login = login; return *this; }

    virtual void printInfo() const = 0;
    virtual bool isAdmin() const = 0;
};

#endif