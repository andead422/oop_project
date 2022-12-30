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

std::ostream& operator << (std::ostream& out, const FilmAdmin& film) {
    out << (string) film;
    return out;
}
