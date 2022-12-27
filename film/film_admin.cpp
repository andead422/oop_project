#include "film_admin.hpp"

Film& FilmAdmin::setGenre(string genre) {
    if(findInVector(genres, genre) != -1) {
        genres.push_back(genre);
    }

    return *this;
}


void FilmAdmin::rateFilm(int idFilm) {
    cout << "rateFilm(): FilmAdmin" << endl;
}