#ifndef film_viewer
#define film_viewer

#include "film.hpp"

class FilmViewer: public Film {
    vector<int> filmGenres;

    //map<genre, pair<count, 0 rate>>
    static map<int, pair<int, int>> Genres;
    //map<id_film, rate>
    static map<int, double> Reccomended;
    static int FilmsNumber;

public:
    FilmViewer();
    FilmViewer(int idFilm): Film(idFilm),
                            filmGenres(database.getFilmGenres(idFilm)) {}
    FilmViewer(const FilmViewer&) = default;
    FilmViewer(FilmViewer&&) = default;
    ~FilmViewer() = default;

    map<int, double> getStats() { return Reccomended; }

    void rateFilm(int) override;

private:
    void fillMap();
    bool checkMap();
    void incrementRated(int);
};

int FilmViewer::FilmsNumber = database.getFilmsNumber();

#endif