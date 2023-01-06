#include "admin.hpp"

//повертає User* адже це може буди як Admin так і Viewer
User* Administrator::seeUserStats(int id) const {
    int admin = database->checkAdmin(id);

    switch (admin) {
    case 1:
        return new Administrator(id);
        break;
    
    case 0:
        return new Viewer(id);
        break;

    case -1:
        cout << "There isn`t user with id: " << id << endl;
        break;
    }
    
}

//повертає User* адже це може буди як Admin так і Viewer
User* Administrator::seeUserStats(string login) const {
    //это с бд забирается и если админ то создаем админа если нет то вивера
    int admin = database->checkAdmin(login);

    switch (admin) {
    case 1:
        return new Administrator(login);
        break;
    
    case 0:
        return new Viewer(login);
        break;

    case -1:
        cout << "There isn`t user with login: " << login << endl;
        break;
    }
}

void Administrator::printInfo() const {
    cout << "Admin: yes" << endl;
    cout << "Login: " << login << endl;
    cout << "ID: " << getId() <<  endl;
}

void History::printUsers() {
    for(int ii = 0; ii < users.size(); ++ii) {
        cout << ii + 1 << ". ";
        users[ii]->printInfo();
        cout << endl;
    }
}