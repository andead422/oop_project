#include "user.hpp"

int User::userCount = 0;

//встановлює новий id для юзера лише у випадку якщо він вільний
User& User::setIdUser(int id) {
    if (id > userCount) {
        idUser = id;
    }

    return *this;
}
