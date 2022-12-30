#include "film_viewer.hpp"

int FilmViewer::FilmsNumber(database->getFilmsNumber());

FilmViewer& FilmViewer::operator=(const FilmViewer& other) { 
    filmGenres = other.filmGenres; 
    rate = other.rate; 
    idFilm = other.idFilm;
    return *this; 
}

void FilmViewer::printFilmInfoToRate() {
    // parse image;
    cout << database->getFilmName(idFilm) << " (" << database->getFilmYear(idFilm) << ")" << endl;
}

//наитийно она будет отличаться от той что выше
void FilmViewer::printFilmInfoToRecommend() {
    //parse image
    cout << database->getFilmName(idFilm) << " (" << database->getFilmYear(idFilm) << ")" << endl;
    
}


