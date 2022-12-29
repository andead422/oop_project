#include "user.hpp"

int User::userCount = 0;

User& User::setIdU(int id) {
    if (id > userCount) {
        idUser = id;
    }

    return *this;
}
