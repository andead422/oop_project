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
    Film(const Film& film) = default;
    ~Film() = default;

    int getIdF() { return idFilm; }
    int getRate() { return rate; }
    string getGenre() { return genre; }
    string getTitle() { return titleFilm; }
    
    Film& setRate(int rate) { this->rate = rate; return *this; }
    Film& setIdFilm(int idFilm) { this->idFilm = idFilm; return *this; }
    Film& setGenre(string genre) { this->genre = genre; return *this; }
    Film& setTilte(string titleFilm) { this->titleFilm = titleFilm; return *this; }

    Film& operator =(const Film& film);

protected:
    // arr getMovieData(int idFilm);

    //s porno
    virtual int rateFilm(int idFilm) = 0;
};


class FilmViewer: public Film {
    string imdbId;

public:
    FilmViewer() = default;
    FilmViewer(int idFilm, string titleFilm, string genre, double userRate, string imdbId): Film(idFilm, titleFilm, genre, userRate), imdbId(imdbId) {}
    FilmViewer(const FilmViewer& filmV) = default;
    ~FilmViewer() = default;

    string getImdbId() { return imdbId; }

    FilmViewer& setImdbId(string imdbId) { this->imdbId = imdbId; return *this; }

    FilmViewer& operator =(const FilmViewer& filmViewer);
    //getFilmImage();

private: 
    int rateFilm(int idFilm) override;
};


class FilmAdmin: public Film {
public:
    FilmAdmin() = default;
    FilmAdmin(int idFilm, string titleFilm, string genre, double medRate): Film(idFilm, titleFilm, genre, medRate) {}
    FilmAdmin(const FilmAdmin& filmA) = default;
    ~FilmAdmin() = default;

private: 
    int rateFilm(int idFilm) override;
};