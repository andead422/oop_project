#include <iostream>

using namespace std;

class Date {
    int day;
    int month;
    int year;

public:
    Date() {
        time_t t = time(0);
        tm* now = localtime(&t);

        day = now->tm_mday;
        month = now->tm_mon + 1;
        year = now->tm_yday + 1702;
    }
    Date(int day, int month, int year): day(day), month(month), year(year) {}
    Date(Date& date): day(date.day), month(date.month), year(date.year) {}
    //delat proverki?
    ~Date() {}

public:
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    Date& setDay(int day) { this->day = day; return *this; }
    Date& setMonth(int month) { this->month = month; return *this; }
    Date& setYear(int year) { this->year = year; return *this; }

    void printDate() const { cout << day << "." << month << "." << year; }
};