#ifndef DATE_H
#define DATE_H

#include "../includes.hpp"

class Date {
    int day;
    int month;
    int year;

    static int days[];
public:
    Date();
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

    Date operator + (const Date&) const;
    
    bool operator == (const Date& other) const { return this->day == other.day && this->month == other.month && this->year == other.year; }
    bool operator != (const Date& another) const { return !(*this == another); }

    //простіше порівнюівати кількості днів
    bool operator > (const Date& another) const { return numDays() > another.numDays(); }
    bool operator < (const Date& another) const { return !(*this > another); }

    friend std::istream& operator >> (std::istream&, Date&);
    friend std::ostream& operator << (std::ostream&, const Date&);
    
    void printDate() const { cout << day << "." << month << "." << year; }

private:
    //рахує кількість днів
    int numDays() const { return day + culcDaysInMonthsNum() + year * 365; }
    int culcDaysInMonthsNum() const;

    
    int mod12(int) const;
    // Date numDaysToDate(int) const;
    // int numDaysToMonth(int) const;
};

#endif