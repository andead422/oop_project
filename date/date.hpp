#ifndef DATE_H
#define DATE_H

#include "../includes.hpp"

class Date {
    int day;
    int month;
    int year;

public:
    Date();
    Date(int day, int month, int year): day(day), month(month), year(year) {}
    Date(Date&) = default;
    //delat proverki?
    ~Date() = default;

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    Date& setDay(int day) { this->day = day; return *this; }
    Date& setMonth(int month) { this->month = month; return *this; }
    Date& setYear(int year) { this->year = year; return *this; }

    void printDate() const { cout << day << "." << month << "." << year; }
};

#endif