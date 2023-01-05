#ifndef ADMIN_H
#define ADMIN_H

#include "user.hpp"
#include "../film/film_admin.hpp"

class Administrator: User {
public:
    FilmAdmin seeFilmStats(int) const;
    Viewer seeUserStats(int);

private:
    bool authorization() const;
};

#endif