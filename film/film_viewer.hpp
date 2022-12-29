#ifndef FILM_VIEWER_H
#define FILM_VIEWER_H

#include "film.hpp"

// DBConnect database;

class FilmViewer: public Film {
    double rate = 0;
    vector<int> filmGenres;
    static int FilmsNumber;
    
public:
    FilmViewer() = default;
    FilmViewer(int idFilm): Film(idFilm),
                            filmGenres(database.getFilmGenres(idFilm)) {}
    FilmViewer(const FilmViewer&) = default;
    FilmViewer(FilmViewer&&) = default;
    ~FilmViewer() = default;

    double getFilmRate() const { return rate; }
    vector<int> getFilmGenres() const { return filmGenres; }
    int getFilmGenre(int ii) const { return filmGenres[ii]; }
    int getFilmGenresSize() const { return filmGenres.size(); }
    static int getFilmsNumber() { return FilmsNumber; }

    FilmViewer& setfilmGenres( vector<int> filmGenres ) { this->filmGenres = filmGenres; return *this; }
    FilmViewer& setfilmGenre( int filmGenre ) { addToSet(filmGenres, filmGenre); return *this; }
    FilmViewer& setFilmRate(double rate) { this->rate = rate; return *this; }

    bool operator == (const FilmViewer& other) const { return filmGenres == other.filmGenres; }
    FilmViewer& operator=(const FilmViewer& other) { filmGenres == other.filmGenres; return *this; }
};

string to_string(FilmViewer film);

#endif