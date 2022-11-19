#include "../includes.hpp"

using std::string;

class Film {
    int idFilm;
    string titleFilm;
    int genre;
    int rate;

public:
    Film(): rate(rateFilm()) {}
    Film(int idFilm, string titleFilm, int genre, int rate): idFilm(idFilm), titleFilm(titleFilm), genre(genre), rate(rate) {}
    Film(Film& film): idFilm(film.idFilm), titleFilm(film.titleFilm), genre(film.genre), rate(film.rate) {}
    ~Film() {}

    int getIdF() { return idFilm; }
    string getTitle() { return titleFilm; }
    int getGenre() { return genre; }
    int getRate() { return rate; }

    Film& setIdFilm(int idFilm) { this->idFilm = idFilm; return *this; }
    Film& setIdFilm(int genre) { this->genre = genre; return *this; }
    Film& setIdFilm(int rate) { this->rate = rate; return *this; }
    Film& setIdFilm(string titleFilm) { this->titleFilm = titleFilm; return *this; }

protected:
    virtual int rateFilm() = 0;
};


class FilmViewer: public Film {
    string imdbId;

public:
    FilmViewer() {}
    FilmViewer(int idFilm, string titleFilm, int genre, double userRate, string imdbId): Film(idFilm, titleFilm, genre, userRate),
                                                                                         imdbId(imdbId) {}
    FilmViewer(FilmViewer& filmV): Film(filmV),
                                   imdbId(filmV.imdbId) {}
    ~FilmViewer() {}

    string getImdbId() { return imdbId; }

    FilmViewer& setImdbId(string imdbId) { this->imdbId = imdbId; return *this; }

    //getFilmImage();

private: 
    int rateFilm();
};


class FilmAdmin: public Film {
public:
    // FilmAdmin() {}
    // FilmAdmin(int idFilm, string titleFilm, int genre, double medRate): Film(idFilm, titleFilm, genre, medRate) {}
    // FilmAdmin(FilmAdmin& filmA) : Film(filmA) {}
    // ~FilmAdmin() {}

private: 
    int rateFilm();
};