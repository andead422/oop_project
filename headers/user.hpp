#include "film.hpp"

using std::vector;

class User {
    int idUser;
    static int userCount;

public:
    User(): idUser(userCount++) {}
    //User(int idUser): idUser(idUser) {}
    User(User& user): idUser(user.idUser) {}
    ~User() {}

    int getIdU() { return idUser; }
    //User& setIdU(int idUser) { this->idUser = idUser; return *this; }
};


class Viewer: public User {
    int age;
    char sex;
    vector<FilmViewer> ratedFilms;

public:
    Viewer() {}
    Viewer(int age, char sex, vector<FilmViewer> ratedFilms): age(age), sex(sex), ratedFilms(ratedFilms) {}
    Viewer(Viewer& viewer): User(viewer),
                            age(viewer.age), sex(viewer.sex), ratedFilms(viewer.ratedFilms) {}
    ~Viewer() {}

    int getAge() { return age; }
    char getSex() { return sex; }
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