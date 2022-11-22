#ifndef film_viewer
#define film_viewer

#include "film.hpp"

class FilmViewer: public Film {
    string imdbId;

public:
    FilmViewer() = default;
    FilmViewer(int idFilm, string titleFilm, string genre, double userRate, string imdbId): Film(idFilm, titleFilm, genre, userRate), imdbId(imdbId) {}
    FilmViewer(const FilmViewer&) = default;
    FilmViewer(FilmViewer&&) = default;
    ~FilmViewer() = default;

    string getImdbId() { return imdbId; }

    FilmViewer& setImdbId(string imdbId) { this->imdbId = imdbId; return *this; }

    FilmViewer& operator =(const FilmViewer& filmViewer);
    //getFilmImage();

private: 
    int rateFilm(int idFilm) override;
};

#endif