#include "viewer.hpp"

// //map<genre, pair<count, 0 rate>>
// vector<pair<int, int>> Viewer::genres(database.getGenresNumber(), {0,0});

Viewer::operator string() const {
    string output;
    output += getIdUser() + "\n"; 
    output += "Age: " + to_string(age) + "\n";
    output += "Sex: ";
    (sex == 'M') ? output += "male\n" : output += "female\n";
    output += "Rated films:\n" + to_string(ratedFilms, "\n");

    return output;
}


void Viewer::printInfo() const {
    cout << (string) *this;
}


void Viewer::incrementRatedGenres(FilmViewer& film, double rate) {
    for (int ii = 0; ii < film.getFilmGenresSize(); ++ii) {
        if (rate == 0) {
            genres[film.getFilmGenre(ii) - 1].second++;
        }
        else {
            genres[film.getFilmGenre(ii) - 1].first++;
        }
    }
}


void Viewer::rateFilm(FilmViewer& film, double rate) {
    incrementRatedGenres(film, rate);

    if (rate != 0) {
        film.setFilmRate(rate);
        ratedFilms.push_back(*new FilmViewer(film));
    }
}


FilmViewer Viewer::generateNewFilm() {
    int idFilm;

    while(1) {
        FilmViewer temp = database->getRandFilm();
        if(checkGenres(temp)) return temp;
    }
}


bool Viewer::checkGenres(FilmViewer& film) {
    for (int ii = 0; ii < film.getFilmGenresSize(); ++ii) {
        if (genres[film.getFilmGenre(ii) - 1].first < 2 && genres[film.getFilmGenre(ii) - 1].second < 2) {
            return true;
        }
    }

    return false;
}


std::ostream& operator << (std::ostream& out, const Viewer& viewer) {
    out << (string) viewer;
    return out;
}


std::istream& operator >> (std::istream& in, Viewer& viewer) {
    while(1) {
        cout << "Enter age and sex(m/f):" << endl;

        cout << "Age: ";
        in >> viewer.age;

        cout << "Sex: ";
        in >> viewer.sex;
        viewer.sex = (char)toupper(viewer.sex);

        if (viewer.sex == 'M' || viewer.sex == 'F') break;

        cout << "Invalid input!" << endl << endl;
    }
    return in;
}


bool Viewer::checkNumberOfRecommendations() const {
    for (int ii = 0; ii < genres.size(); ++ii) {
        if (genres[ii].first < 2 && genres[ii].second < 2) {
            return true;
        }
    }

    return false;
}


void Viewer::rateFilms() {
    cout << "Rate film: " << endl << endl;
    int ii = 0;
    do {
        FilmViewer filmViewer = generateNewFilm();
        filmViewer.printFilmInfoToRate();

        int rate;
        cout << "Rate from 0 to 5 with step 0,5: ";
        cin >> rate;

        rateFilm(filmViewer, rate);
        cout << to_string(filmViewer) << endl << endl;
    //} while(checkNumberOfRecommendations());
    } while(++ii < 2);
}


map<int, double> Viewer::getMapRatedFilms() const {
    map<int, double> output;
    
    for(int ii = 0; ii < ratedFilms.size(); ++ii){
        output[ratedFilms[ii].getId()] = ratedFilms[ii].getFilmRate();
    }

    return output;
}
