#include "film_viewer.hpp"

void FilmViewer::fillMap() {
    int genresNumber = database.getGenresNumber();

    //starts from 0?
    for (int ii = 0; ii <= genresNumber; ii++) {
        Genres[ii].first = 0;
        Genres[ii].second = 0;
    }
}

bool FilmViewer::checkMap() {
    for (int ii = 0; ii < filmGenres.size(); ++ii) {
        if (Genres[filmGenres[ii]].first > 3 || Genres[filmGenres[ii]].second > 3) {
            return false;
        }
    }

    return true;
}

void FilmViewer::incrementRated(int rate) {
    for (int ii = 0; ii < filmGenres.size(); ++ii) {
        if (rate == 0) {
            Genres[filmGenres[ii]].second++;
        }
        else {
            Genres[filmGenres[ii]].first++;
        }
    }
}

FilmViewer::FilmViewer() {
    int idFilm;

    do {
        idFilm = rand()%(FilmsNumber + 1);
        filmGenres = database.getFilmGenres(idFilm);
    } while(!checkMap());

    setId(idFilm);

    //picture and title wiil be parsed by UI functions?
}

void FilmViewer::rateFilm(int rate) {
    incrementRated(rate);
    Reccomended[this->getId()] = rate;

    //cout << "rateFilm(): FilmViewer" << endl;
}
