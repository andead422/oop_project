#ifndef FILM_H
#define FILM_H

#include "../includes.hpp"

using std::string;

class Film {
    int idFilm;

public:
    Film() = default;
    Film(int idFilm) : idFilm(idFilm) {};
    Film(const Film&) = default;
    Film(Film&&) = default;
    ~Film() = default;

    int getId() const { return idFilm; }
    Film& setId(int idFilm) { this->idFilm = idFilm; return *this; }

    Film& operator =(const Film& filmOper) { idFilm = filmOper.idFilm; return *this; }

protected:
    // arr getMovieData(int idFilm);

    //в общем если хранить обьекты дочерних классов в указателе на батькивськый(меньше памяти) то смысл имеет  
    virtual void rateFilm(int) = 0;
};

#endif