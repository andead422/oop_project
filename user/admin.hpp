#ifndef admin
#define admin

#include "user.hpp"
#include "../film/film_admin.hpp"

class Administrator: User {
public:
    bool addFilm(int);
    void removeFilm(int);
    FilmAdmin seeFilmStats(int);
    // Viewer seeViewerStats(int);

private:
    bool authorization();
};

#endif