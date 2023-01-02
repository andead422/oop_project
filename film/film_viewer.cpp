#include "film_viewer.hpp"

FilmViewer& FilmViewer::operator=(const FilmViewer& other) { 
    filmGenres = other.filmGenres; 
    rate = other.rate; 
    idFilm = other.idFilm;
    return *this; 
}

inline string to_string(const FilmViewer& film) { return to_string(film.getId()) + ": " + to_string(film.getFilmRate()); }
