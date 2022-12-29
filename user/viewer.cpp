#include "viewer.hpp"

// //map<genre, pair<count, 0 rate>>
// vector<pair<int, int>> Viewer::Genres(database.getGenresNumber(), {0,0});

bool Viewer::checkSeen(FilmViewer&) const {
    return true;
}

Viewer::operator string() const {
    string output;
    output += getIdUser() + "\n"; 
    output += "Age: " + to_string(age) + "\n";
    output += "Sex: ";
    (sex == 'm') ? output += "male\n" : output += "female\n";
    output += "Rated films:\n" + to_string(ratedFilms, "\n");

    return output;
}

void Viewer::printInfo() const {
    cout << (string) *this;
}

void Viewer::incrementRatedGenres(FilmViewer& film, double rate) {
    for (int ii = 0; ii < film.getFilmGenresSize(); ++ii) {
        if (rate == 0) {
            Genres[film.getFilmGenre(ii)].second++;
        }
        else {
            Genres[film.getFilmGenre(ii)].first++;
        }
    }
}


void Viewer::rateFilm(FilmViewer& film, double rate) {
    incrementRatedGenres(film, rate);

    if (rate != 0) {
        film.setFilmRate(rate);
        ratedFilms.push_back(*new FilmViewer(film));
    }
}

FilmViewer Viewer::generateNewFilm() {
    int idFilm;

    while(1) {
        idFilm = rand() % (FilmViewer::getFilmsNumber() + 1);
        FilmViewer temp(idFilm);

        if(checkGenres(temp)) temp;
    }
}

bool Viewer::checkGenres(FilmViewer& film) {
    for (int ii = 0; ii < film.getFilmGenresSize(); ++ii) {
        if (Genres[film.getFilmGenre(ii)].first > 3 || Genres[film.getFilmGenre(ii)].second > 3) {
            return false;
        }
    }

    return true;
}

std::ostream& operator << (std::ostream& out, const Viewer& viewer) {
    out << (string) viewer;
    return out;
}