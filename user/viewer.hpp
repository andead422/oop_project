#ifndef VIEWER_H
#define VIEWER_H

#include "user.hpp"
#include "../film/film_viewer.hpp"


class Viewer: public User {
    int age;
    char sex;
    vector<FilmViewer> ratedFilms;

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

    //void rateFilm(FilmViewer&);

private:
    bool checkSeen(FilmViewer&) const;
};

#endif