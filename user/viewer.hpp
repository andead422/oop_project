#ifndef VIEWER_H
#define VIEWER_H

#include "user.hpp"
#include "../film/film_viewer.hpp"

class Viewer: public User {
    int age;
    char sex;
    vector<FilmViewer> ratedFilms;

    //vector[genre]<pair<count, 0 rate>>
    vector<pair<int, int>> Genres = vector(database.getGenresNumber(), pair(0,0));

public:
    Viewer() = default;
    Viewer(int age, char sex): age(age), sex(sex) {}   
    Viewer(int age, char sex, vector<FilmViewer>& ratedFilms): age(age), sex(sex), ratedFilms(ratedFilms) {}
    Viewer(const Viewer&) = default;
    ~Viewer() = default;

    int getAge() const { return age; }
    char getSex() const { return sex; }
    vector<FilmViewer> getRatedFilms() const { return ratedFilms; }

    Viewer& setAge(int age) { this->age = age; return *this; }
    Viewer& setSex(char sex) { this->sex = sex; return *this; }
    Viewer& setRatedFilms(vector<FilmViewer>& ratedFilms) { this->ratedFilms = ratedFilms; return *this; }
    Viewer& setRatedFilm(FilmViewer& ratedFilm) { addToSet(ratedFilms, ratedFilm); return *this; }
    vector<pair<int, int>> getGenresStats() { return Genres; }

    void rateFilm(FilmViewer&, double);
    FilmViewer generateNewFilm();
    bool checkGenres(FilmViewer&);

    operator string()const;
    friend std::ostream& operator << (std::ostream&, const Viewer&);

private:
    void incrementRatedGenres(FilmViewer&, double);
    bool checkSeen(FilmViewer&) const;
    void printInfo() const;
};

#endif