#include "includes.hpp"

using std::string;

class Film {
    int idFilm;
    string titleFilm;
    int genre;

public:
    int getIdF() { return idFilm; }
    string getTitle() { return titleFilm; }
    int getGenre() { return genre; }
};


class FilmViewer: public Film {
    double userRate;
    string imdbId;

public:
    FilmViewer& setUserRate(double userRate) { this->userRate = userRate; return *this; }

    double getUserRate() { return userRate; }
    string getImdbId() { return imdbId; }
    //getFilmImage();
};


class FilmAdmin: public Film {
    double medRate;

public:
    double getMedRate() { return medRate; }
};