#include "film_viewer.hpp"

FilmViewer& FilmViewer::operator=(const FilmViewer& other) { 
    filmGenres = other.filmGenres; 
    rate = other.rate; 
    idFilm = other.idFilm;
    return *this; 
}


void FilmViewer::printFilmInfoToRate() {
    // parse image;
    cout << database->getFilmTitleYear(idFilm) << endl;
}

//наитийно она будет отличаться от той что выше
void FilmViewer::printFilmInfoToRecommend() {
    //parse image
    cout << database->getFilmTitleYear(idFilm) << endl;    
}


