#include "film.hpp"

Film& Film::operator =(const Film& filmoperator) {
    idFilm = filmoperator.idFilm;
    titleFilm = filmoperator.titleFilm;
    genre = filmoperator.genre;
    rate = filmoperator.rate;
    
    return *this;
}
