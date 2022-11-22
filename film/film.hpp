#ifndef film
#define film

#include "../includes.hpp"

using std::string;

class Film {
    int idFilm;
    string titleFilm;
    string genre;
    int rate;

public:
    Film() = default;
    Film(int idFilm) : idFilm(idFilm) {/*arr filmData = getMovieData(idFilm); titleFilm = filmData[0]; genre = filmData[1]; rate = rateFilm(idFilm)*/}
    Film(int idFilm, string titleFilm, string genre, int rate): idFilm(idFilm), titleFilm(titleFilm), genre(genre), rate(rate) {}
    Film(const Film&) = default;
    Film(Film&&) = default;
    ~Film() = default;

    int getIdF() { return idFilm; }
    int getRate() { return rate; }
    string getGenre() { return genre; }
    string getTitle() { return titleFilm; }
    
    Film& setRate(int rate) { this->rate = rate; return *this; }
    Film& setIdFilm(int idFilm) { this->idFilm = idFilm; return *this; }
    Film& setGenre(string genre) { this->genre = genre; return *this; }
    Film& setTilte(string titleFilm) { this->titleFilm = titleFilm; return *this; }

    Film& operator =(const Film& filmoperator);

protected:
    // arr getMovieData(int idFilm);

    //s porno
    virtual int rateFilm(int idFilm) = 0;
};

#endif