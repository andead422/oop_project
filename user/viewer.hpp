#ifndef VIEWER_H
#define VIEWER_H

#include "user.hpp"
#include "../film/film_viewer.hpp"

class Viewer: public User {
    int age;
    char sex;
    vector<FilmViewer> ratedFilms;

    //vector[genre]<pair<count 0.5+ rates, count 0 rates>>
    vector<pair<int, int>> genres = vector(database->getGenresNumber(), pair(0,0));

public:
    Viewer() = default;
    Viewer(int);
    Viewer(string);
    Viewer(string login, int age, char sex): User(login), age(age), sex((char)toupper(sex)) {}   
    Viewer(int age, char sex, vector<FilmViewer>& ratedFilms): age(age), sex((char)toupper(sex)), ratedFilms(ratedFilms) {}
    Viewer(const Viewer&) = default;
    ~Viewer() = default;

    int getAge() const { return age; }
    char getSex() const { return sex; }
    vector<FilmViewer> getRatedFilms() const { return ratedFilms; }
    map<int, double> getMapRatedFilms() const;

    Viewer& setAge(int age) { this->age = age; return *this; }
    Viewer& setSex(char sex) { this->sex = (char)toupper(sex); return *this; }
    Viewer& setRatedFilms(vector<FilmViewer>& ratedFilms) { this->ratedFilms = ratedFilms; return *this; }
    Viewer& setRatedFilm(FilmViewer& ratedFilm) { addToSet(ratedFilms, ratedFilm); return *this; }
    vector<pair<int, int>> getGenresStats() { return genres; }

    void rateFilm(FilmViewer&, double);
    // FilmViewer generateNewFilm();
    // bool checkGenres(FilmViewer&);

    operator string()const;
    friend std::ostream& operator << (std::ostream&, const Viewer&);
    friend std::istream& operator >> (std::istream&, Viewer&);
    // bool checkNumberOfRecommendations() const;
    void rateFilms();
    bool checkSeen(FilmViewer& film) const { return findInVector(ratedFilms, film) != -1; }
    
    void printInfo() const;
    bool isAdmin() const  { return 0; }
private:
    void incrementRatedGenres(FilmViewer&, double);
    
};

#endif