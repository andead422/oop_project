#include "film_viewer.hpp"


int FilmViewer::rateFilm(int idFilm) {
    //parilka
}

FilmViewer& FilmViewer::operator =(const FilmViewer& filmViewer) {
    Film::operator =(filmViewer);
    imdbId = filmViewer.imdbId;

    return *this;
}