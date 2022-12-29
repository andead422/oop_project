#include "film_admin.hpp"

FilmAdmin::FilmAdmin(int idFilm): Film(idFilm) {
    title = "database info";
    year = 0;
    rate = 0;
    picture = "database info";
    overview = "database info";
    director = "database info";
    genres = {"database info"};
    cast = {"database info"};
}


void FilmAdmin::rateFilm(int idFilm) {
    cout << "rateFilm(): FilmAdmin" << endl;
}

void FilmAdmin::printInfo() const { 
    cout << title << " (" << year << ")" << endl; 
    cout << "Rate: " << rate << endl;
    cout << "Genres: " << to_string(genres) << endl;
    cout << "Director: " << director << endl;
    cout << "Cast: " << to_string(cast) << endl;
    cout << "Overview: " << overview << endl;
    cout << "Picture: " << picture << endl;
}
