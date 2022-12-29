#include "film_viewer.hpp"

//map<genre, pair<count, 0 rate>>
vector<pair<int, int>> FilmViewer::Genres(database->getGenresNumber(), {0,0});
//map<id_film, rate>
map<int, double> FilmViewer::Recommended;
int FilmViewer::FilmsNumber(database->getFilmsNumber());


bool FilmViewer::checkMap() const {
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
        idFilm = rand() % (FilmsNumber + 1);
        filmGenres = database->getFilmGenres(idFilm);
    } while(!checkMap());

    setId(idFilm);

    //picture and title wiil be parsed by UI functions?
}

void FilmViewer::rateFilm(int rate) {
    incrementRated(rate);
    Recommended[this->getId()] = rate;
}

