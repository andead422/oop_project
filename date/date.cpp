#include "date.hpp"

Date::Date() {
    time_t t = time(0);
    tm* now = localtime(&t);

    day = now->tm_mday;
    month = now->tm_mon + 1;
    year = now->tm_year + 1900;
}