#ifndef ADMIN_H
#define ADMIN_H

#include "viewer.hpp"
#include "../film/film_admin.hpp"

class Administrator: User {
public:
    void addFilm(int) const;
    void removeFilm(int) const;
    FilmAdmin seeFilmStats(int id) const { return FilmAdmin(id); }
    Viewer seeViewerStats(int id) const { return Viewer(id); }

private:
    bool authorization() const;
};

#endif