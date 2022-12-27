#ifndef film_admin
#define film_admin

#include "film.hpp"

class FilmAdmin: public Film {
    string title;
    double rate;
    string picture;
    string overview;
    string crew;
    vector<string> genres;
    vector<string> cast;
public:
    FilmAdmin() = default;
    FilmAdmin(int idFilm, string titleFilm, string genre, double medRate): Film(idFilm) {}
    FilmAdmin(const FilmAdmin&) = default;
    ~FilmAdmin() = default;

    vector<string> getGenres() { return genres; }
    string getTitle() { return title; }
    
    Film& setGenres(string genre) { this->genres = genres; return *this; }
    Film& setGenre(string genre);
    Film& setTilte(string title) { this->title = title; return *this; }

private: 
    void rateFilm(int idFilm) override;
};

#endif