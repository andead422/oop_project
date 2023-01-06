#include "admin.hpp"


FilmAdmin Administrator::seeFilmStats(int id) const {
    return FilmAdmin(id);
}

//повертає User* адже це може буди як Admin так і Viewer
User* Administrator::seeUserStats(int id) const {
    //это с бд забирается и если админ то создаем админа если нет то вивера
    return new Viewer(id);
}

//повертає User* адже це може буди як Admin так і Viewer
User* Administrator::seeUserStats(string login) const {
    //это с бд забирается и если админ то создаем админа если нет то вивера
    return new Viewer(login);
}

bool Administrator::authorization() const {
    return true;
}

void Administrator::printInfo() const {
    cout << "Admin: yes" << endl;
    cout << "Login: " << login << endl;
    cout << "ID: " << getIdUser() <<  endl;
}

void History::printUsers() {
    for(int ii = 0; ii < users.size(); ++ii) {
        cout << ii + 1 << ". ";
        users[ii]->printInfo();
        cout << endl;
    }
}