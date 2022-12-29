#include "film_viewer.hpp"

int FilmViewer::FilmsNumber(database->getFilmsNumber());

FilmViewer& FilmViewer::operator=(const FilmViewer& other) { 
    filmGenres = other.filmGenres; 
    rate = other.rate; 
    idFilm = other.idFilm;
    return *this; 
}

