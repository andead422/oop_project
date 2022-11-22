#include "film.hpp"

Film& Film::operator =(const Film& film) {
    idFilm = film.idFilm;
    titleFilm = film.titleFilm;
    genre = film.genre;
    rate = film.rate;
    
    return *this;
}
