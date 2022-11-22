#ifndef film_admin
#define film_admin

#include "film.hpp"

class FilmAdmin: public Film {
public:
    FilmAdmin() = default;
    FilmAdmin(int idFilm, string titleFilm, string genre, double medRate): Film(idFilm, titleFilm, genre, medRate) {}
    FilmAdmin(const FilmAdmin&) = default;
    ~FilmAdmin() = default;

private: 
    int rateFilm(int idFilm) override;
};

#endif