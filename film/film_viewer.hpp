#ifndef FILM_VIEWER_H
#define FILM_VIEWER_H

#include "film.hpp"

// DBConnect database;

class FilmViewer: public Film {
    vector<int> filmGenres;

    //map<genre, pair<count, 0 rate>>
    static vector<pair<int, int>> Genres;
    //map<id_film, rate>
    static map<int, double> Recommended;
    static int FilmsNumber;
    
public:
    FilmViewer();
    FilmViewer(int idFilm): Film(idFilm),
                            filmGenres(database->getFilmGenres(idFilm)) {}
    FilmViewer(const FilmViewer&) = default;
    FilmViewer(FilmViewer&&) = default;
    ~FilmViewer() = default;

    vector<int> getFilmGenres() const { return filmGenres; }
    map<int, double> getRecommendedStats() const { return Recommended; }
    vector<pair<int, int>> getGenresStats() const { return Genres; }
    static int getFilmsNumber() { return FilmsNumber; }

    FilmViewer& setfilmGenres( vector<int> filmGenres ) { this->filmGenres = filmGenres; return *this; }
    FilmViewer& setfilmGenre( int filmGenre ) { addToSet(filmGenres, filmGenre); return *this; }

    void rateFilm(int) override;

    bool operator == (const FilmViewer& other) const { return filmGenres == other.filmGenres; }
    FilmViewer& operator=(const FilmViewer& other) { filmGenres == other.filmGenres; return *this; }

private:
    bool checkMap() const;
    void incrementRated(int);
};

#endif