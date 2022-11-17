#include "film.hpp"

using std::vector;

class User {
protected:
    int idUser;

public:
    int getIdU() { return idUser; }
};


class Viewer: public User {
    int age;
    char sex;
    vector<FilmViewer> ratedFilms;

public:
    int getAge() { return age; }
    char getASex() { return sex; }
    vector<FilmViewer> getRatedFilms() { return ratedFilms; }

    Viewer& setAge(int age) { this->age = age; return *this; }
    Viewer& setSex(char sex) { this->sex = sex; return *this; }
    Viewer& setRatedFilms(vector<FilmViewer> ratedFilms) { this->ratedFilms = ratedFilms; return *this; }

    void rateFilm(FilmViewer&);

private:
    bool checkSeen(FilmViewer&);
};


class Administrator: User {
public:
    bool addFilm(int);
    void removeFilm(int);
    Film seeFilmStats(int);
    Viewer seeViewerStats(int);

private:
    bool authorization();
};