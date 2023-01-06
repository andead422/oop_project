#include "viewer.hpp"
#define LIMIT 1 //потрібна для налаштування кількості фільмів що оцінює viewer

Viewer::operator string() const {
    string output;
    output += "Login: " + login + "\n"; 
    output += "ID: " + to_string(getIdUser()) + "\n"; 
    output += "Age: " + to_string(age) + "\n";
    output += "Sex: ";
    (sex == 'M') ? output += "male\n" : output += "female\n";
    output += "Rated films:\n" + to_string(ratedFilms, "\n");

    return output;
}


void Viewer::printInfo() const {
    cout << "Admin: no" << endl;
    cout << (string) *this;
}

//збільшення відповідних лічильників для всіх жанрів оціненого viewer-ом фільму
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

//встановлює фільму оцінку від юзера
void Viewer::rateFilm(FilmViewer& film, double rate) {
    incrementRatedGenres(film, rate);

    if (rate != 0) {
        film.setFilmRate(rate);
        ratedFilms.push_back(*new FilmViewer(film)); //додаємо фільм до списку оцінених юзером
    }
}


FilmViewer Viewer::generateNewFilm() {
    int idFilm;

    while(1) {
        FilmViewer temp(database->getRandomFilm());
        if(checkGenres(temp)) return temp;
    }
}


bool Viewer::checkGenres(FilmViewer& film) {
    for (int ii = 0; ii < film.getFilmGenresSize(); ++ii) {
        if (genres[film.getFilmGenre(ii) - 1].first < LIMIT && genres[film.getFilmGenre(ii) - 1].second < LIMIT) {
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

        cout << "Login: ";
        in >> viewer.login;        

        cout << "Age: ";
        in >> viewer.age;

        cout << "Sex: ";
        in >> viewer.sex;
        viewer.sex = (char)toupper(viewer.sex);

        if ((viewer.sex == 'M' || viewer.sex == 'F') && viewer.age >= 0) break;

        cout << "Invalid input!" << endl << endl;
    }
    return in;
}

//перевірка чи всі жанри заповнено 
bool Viewer::checkNumberOfRecommendations() const {
    for (int ii = 0; ii < genres.size(); ++ii) {
        if (genres[ii].first < LIMIT && genres[ii].second < LIMIT) {
            return true;
        }
    }

    return false;
}

//процес надання юзеру фільмів для встановлення оцінок
void Viewer::rateFilms() {
    cout << "Rate film: " << endl << endl;
    int ii = 0;
    do {
        FilmViewer filmViewer = generateNewFilm();
        filmViewer.printFilmInfoToRate();

        double rate;
        do{
            cout << "Rate from 0 to 5 with step 0.5: ";
            cin >> rate;
            if(((rate - (int)rate == 0) || (rate - (int)rate == 0.5)) && rate <= 5 && rate >= 0) break;
            else {
                cout << "Invalid input!" << endl;
            }

        } while(1);

        rateFilm(filmViewer, rate);
        cout << to_string(filmViewer) << endl << endl;
    } while(checkNumberOfRecommendations());
}

//переведення масиву у зручний для обробки формат: map<id_film, rate>
map<int, double> Viewer::getMapRatedFilms() const {
    map<int, double> output;
    
    for(int ii = 0; ii < ratedFilms.size(); ++ii){
        output[ratedFilms[ii].getId()] = ratedFilms[ii].getFilmRate();
    }

    return output;
}
