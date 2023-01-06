#ifndef ADMIN_H
#define ADMIN_H

#include "user.hpp"
#include "../film/film_admin.hpp"
#include "viewer.hpp"

class Administrator: public User {
public:
    Administrator() = default;
    Administrator(string login) : User(login) {}
    Administrator(int idUser) : User(idUser) {}
    Administrator(int idUser, string login) : User(idUser, login) {}
    Administrator(const Administrator& admin) = default;
    ~Administrator() = default;

    FilmAdmin seeFilmStats(int id) const { return FilmAdmin(id); }
    User* seeUserStats(int) const;
    User* seeUserStats(string) const;
    
    void printInfo() const;
    bool isAdmin() const { return 1; }
};


class History {
    vector<User*> users;
    vector<FilmAdmin> films;

public:
    History() = default;
    History(const History& hist): users(hist.users), films(hist.films) {}
    ~History() = default; 

    vector<User*> getUsers() { return users; }
    vector<FilmAdmin> getFilms() { return films; }

    History& addUserP(User* userP) { users.push_back(userP); return *this; }
    History& addUser(FilmAdmin film) { films.push_back(film); return *this; }

    void printUsers();
};

#endif