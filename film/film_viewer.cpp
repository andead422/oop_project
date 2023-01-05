#include "film_viewer.hpp"

FilmViewer& FilmViewer::operator=(const FilmViewer& other) { 
    filmGenres = other.filmGenres; 
    rate = other.rate; 
    idFilm = other.idFilm;
    return *this; 
}

//виводить інформацію необхідну для оцінки
void FilmViewer::printFilmInfoToRate() {
    // parse image;
    cout << database->getFilmTitleYear(idFilm) << endl;
}

//виводить фільм як рекомендацію
void FilmViewer::printFilmInfoToRecommend() {
    //parse image
    cout << database->getFilmTitleYear(idFilm) << endl;    
}


