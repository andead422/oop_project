#include "film_viewer.hpp"

int FilmViewer::FilmsNumber(database.getFilmsNumber());


string to_string(FilmViewer film) {
    return to_string(film.getId()) + ": " + to_string(film.getFilmRate());
}

