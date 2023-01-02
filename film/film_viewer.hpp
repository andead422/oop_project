#ifndef FILM_VIEWER_H
#define FILM_VIEWER_H

#include "film.hpp"

// DBConnect database;

class FilmViewer: public Film {
    double rate = 0;
    vector<int> filmGenres;
    
public:
    FilmViewer() = default;
    FilmViewer(int idFilm): Film(idFilm),
                            filmGenres(database->getFilmGenres(idFilm)) {}
    FilmViewer(const FilmViewer&) = default;
    FilmViewer(FilmViewer&&) = default;
    ~FilmViewer() = default;

    double getFilmRate() const { return rate; }
    vector<int> getFilmGenres() const { return filmGenres; }
    int getFilmGenre(int ii) const { return filmGenres[ii]; }
    int getFilmGenresSize() const { return filmGenres.size(); }

    FilmViewer& setfilmGenres( const vector<int>& filmGenres ) { this->filmGenres = filmGenres; return *this; }
    FilmViewer& setfilmGenre( const int filmGenre ) { addToSet(filmGenres, filmGenre); return *this; }
    FilmViewer& setFilmRate(const double rate) { this->rate = rate; return *this; }

    void printFilmInfoToRate();
    void printFilmInfoToRecommend();

    bool operator == (const FilmViewer& other) const { return filmGenres == other.filmGenres && idFilm == other.idFilm && rate == other.rate; }
    FilmViewer& operator=(const FilmViewer& other);
};

inline string to_string(const FilmViewer& film) { return to_string(film.getId()) + ": " + to_string(film.getFilmRate()); }

#endif