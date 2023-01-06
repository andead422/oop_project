#include "film_admin.hpp"

FilmAdmin::FilmAdmin(int idFilm): Film(idFilm) {
    title = database->getFilmTitleYear(idFilm);
    rate = database->getFilmRate(idFilm);
    picture = "parsed";
    overview = "parsed";
    director = database->getFilmDirector(idFilm);
    genres = database->getFilmGenres(idFilm);
    cast = database->getFilmCast(idFilm);
}

//оператор приведення типу до string
FilmAdmin::operator string() const {
    string output;
    output += title + " (" + to_string(year) + ")\n"; 
    output += "Rate: " + to_string(rate) + "\n";
    output += "Genres: " + to_string(genres) + "\n";
    output += "Director: " + director + "\n";
    output += "Cast: " + to_string(cast) + "\n";
    output += "Overview: " + overview + "\n";
    output += "Picture: " + picture;

    return output;
}

void FilmAdmin::printInfo() const {
    cout << (string)*this;
}

std::ostream& operator << (std::ostream& out, const FilmAdmin& film) {
    out << (string) film;
    return out;
}
