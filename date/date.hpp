#ifndef DATE_H
#define DATE_H

#include "../includes.hpp"

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
        year = now->tm_year + 1900;
    }
    Date(int day, int month, int year): day(day), month(month), year(year) {}
    Date(const Date&) = default;
    //delat proverki?
    ~Date() = default;

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    Date& setDay(int day) { this->day = day; return *this; }
    Date& setMonth(int month) { this->month = month; return *this; }
    Date& setYear(int year) { this->year = year; return *this; }

    Date& operator ++();
    Date& operator --();

    Date operator ++(int);
    Date operator --(int);

    int leap_years();

    bool operator == (const Date& other);
    
    bool operator != (const Date& another);

    bool operator > (const Date& other);

    bool operator < (const Date& other);

    Date operator + (const Date& temp) const;

    friend std::istream& operator >> (std::istream& in, Date& date);
    friend std::ostream& operator << (std::ostream& out, const Date& date);
    
    void printDate() const { cout << day << "." << month << "." << year; }
};

#endif