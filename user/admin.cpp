#include "admin.hpp"

//повертає User* адже це може буди як Admin так і Viewer
template<typename T>
User* Administrator::seeUserStats(T biom) const {
    //это с бд забирается и если админ то создаем админа если нет то вивера
    int admin = database->checkAdmin(biom);

    switch (admin) {
    case 1:
        return new Administrator(biom);
        break;
    
    case 0:
        return new Viewer(biom);
        break;

    case -1:
        cout << "There isn`t user: " << biom << endl;
        break;
    }

    return NULL;
}

template User* Administrator::seeUserStats<int>(int) const;
template User* Administrator::seeUserStats<string>(string) const;

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