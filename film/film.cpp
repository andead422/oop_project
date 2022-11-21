#include "film.hpp"

Film& Film::operator =(const Film& film) {
    idFilm = film.idFilm;
    titleFilm = film.titleFilm;
    genre = film.genre;
    rate = film.rate;
    
    return *this;
}

int FilmViewer::rateFilm(int idFilm) {
    //parilka
}

int FilmAdmin::rateFilm(int idFilm) {
    cout << "rate film";

    return 0;
}

FilmViewer& FilmViewer::operator =(const FilmViewer& filmViewer) {
    Film::operator =(filmViewer);
    imdbId = filmViewer.imdbId;

    return *this;
}