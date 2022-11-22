#ifndef viewer
#define viewer

#include "user.hpp"
#include "../film/film_viewer.hpp"


class Viewer: public User {
    int age;
    char sex;
    vector<FilmViewer> ratedFilms;

public:
    Viewer() = default;
    Viewer(int age, char sex, vector<FilmViewer>& ratedFilms): age(age), sex(sex), ratedFilms(ratedFilms) {}
    Viewer(const Viewer&) = default;
    ~Viewer() = default;

    int getAge() { return age; }
    char getSex() { return sex; }
    vector<FilmViewer> getRatedFilms() { return ratedFilms; }

    Viewer& setAge(int age) { this->age = age; return *this; }
    Viewer& setSex(char sex) { this->sex = sex; return *this; }
    Viewer& setRatedFilms(vector<FilmViewer>& ratedFilms) { this->ratedFilms = ratedFilms; return *this; }

    void rateFilm(FilmViewer&);

private:
    bool checkSeen(FilmViewer&);
};

#endif