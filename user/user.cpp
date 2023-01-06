#include "user.hpp"

int User::userCount = 0;

// void User::printInfo() const {
//     cout << "Login: " << login << endl;
//     cout << "ID: " << getIdUser() <<  endl;
// }


//встановлює новий id для юзера лише у випадку якщо він вільний
User& User::setIdUser(int id) {
    if (id > userCount) {
        idUser = id;
    }

    return *this;
}
