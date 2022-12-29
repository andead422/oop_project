#include "user.hpp"

User& User::setIdU(int id) {
    if (id > userCount) {
        idUser = id;
    }

    return *this;
}
