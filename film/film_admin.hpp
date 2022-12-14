#ifndef FILM_ADMIN_H
#define FILM_ADMIN_H

#include "film.hpp"

class FilmAdmin: public Film {
    string title;
    double rate;
    string picture;
    string overview;
    string director;
    vector<int> genres;
    vector<string> cast;
public:
    FilmAdmin() = default;
    FilmAdmin(int idFilm);
    FilmAdmin(const FilmAdmin&) = default;
    ~FilmAdmin() = default;

    string getTitle() const { return title; }
    double getRate() const { return rate; }
    string getPicture() const { return picture; }
    string getOverview() const { return overview; }
    string getDirector() const { return director; }
    vector<int> getGenres() const { return genres; }
    vector<string> getCast() const { return cast; }

    Film& setTilte(string title) { this->title = title; return *this; }
    Film& setRate(double rate) { this->rate = rate; return *this; }
    Film& setPicture(string picture) { this->picture = picture; return *this; }
    Film& setOverview(string overview) { this->overview = overview; return *this; }
    Film& setDirector(string director) { this->director = director; return *this; }
    Film& setGenres(vector<int> genres) { this->genres = genres; return *this; }
    Film& setGenre(int genre) { addToSet(genres, genre); return *this; }
    Film& setCast(vector<string> cast) { this->cast = cast; return *this; }
    Film& setActor(string actor) { addToSet(cast, actor); return *this; }

    void printInfo() const;
    operator string() const;
    friend std::ostream& operator << (std::ostream&, const FilmAdmin&);
};

#endif