#include "admin.hpp"

void Administrator::addFilm(int) const {

}

void Administrator::removeFilm(int) const {
    
}

FilmAdmin Administrator::seeFilmStats(int id) const {
    return FilmAdmin(id);
}

// Viewer Administrator::seeViewerStats(int) {

// }

bool Administrator::authorization() const {
    return true;
}