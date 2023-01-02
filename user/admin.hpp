#ifndef ADMIN_H
#define ADMIN_H

#include "user.hpp"
#include "../film/film_admin.hpp"

class Administrator: User {
public:
    void addFilm(int) const;
    void removeFilm(int) const;
    FilmAdmin seeFilmStats(int) const;
    // Viewer seeViewerStats(int);

private:
    bool authorization() const;
};

#endif