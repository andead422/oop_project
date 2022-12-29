#include "date.hpp"

// Date::Date() {
//     time_t t = time(0);
//     tm* now = localtime(&t);

//     day = now->tm_mday;
//     month = now->tm_mon + 1;
//     year = now->tm_year + 1900;
// }

std::istream& operator >> (std::istream& in, Date& date) {
    cout << "Date, Month, Year" << endl;
    in >> date.day >> date.month >> date.year;
    return in;
}
std::ostream& operator << (std::ostream& out, const Date& date) {
    out << "Day: " << date.getDay() << endl;
    out << "Month: " << date.getMonth() << endl;
    out << "Year: " << date.getYear() << endl;
    return out;
}
//пояснялка почему постфиксный оператор реализован именно так
/* Операторы версии префикс возвращают объект после того, как он был увеличен или уменьшен.
 В версии постфикс нам нужно возвращать объект до того, как он будет увеличен или уменьшен. И тут конфуз! 
 Если мы увеличиваем или уменьшаем объект, то мы не можем возвратить его до выполнения инкремента/декремента,
 так как операция увеличения/уменьшения уже произошла. С другой стороны, если мы возвращаем объект 
 до выполнения инкремента/декремента, то сама операция увеличения/уменьшения объекта не выполнится.

 Решением является использование временного объекта с текущим значением переменной-члена. 
 Тогда можно будет увеличить/уменьшить исходный объект, а временный объект возвратить обратно в caller. 
 Таким образом, caller получит копию объекта до того, как фактический объект будет увеличен или уменьшен, 
 и сама операция инкремента/декремента выполнится успешно.*/

Date& Date::operator++() {
    day++;
    return *this;
}

Date& Date::operator--() {
    day--;
    return *this;
}

Date Date::operator++(int) {
    Date temp = *this;
    day++;
    return temp;
}

Date Date::operator--(int) {
    Date temp = *this;
    day--;
    return temp;
}

int Date::leap_years() {
    int leap_years1;
    if(this->month > 2) {
        leap_years1 = floor(this->year/4) - floor(this->year/100) + floor(this->year/400);
    }
    if(this->month <= 2) {
        leap_years1 = floor((this->year-1)/4) - floor((this->year-1)/100) + floor((this->year-1)/400);
    }
    return leap_years1;

}

Date Date::operator + (Date temp)  {
    /*
    Date tmp;
    tmp.day = abs(this->day - temp.day);
    tmp.month = abs(this->month - temp.month);
    tmp.year = (this->year - temp.year);
    return tmp;
    */
   Date tmp;
   int overall_days_temp = 2000*365 + 31 + 1 + temp.leap_years();

   tmp.day = overall_days_temp;
   
   return tmp;
}

bool Date::operator == (const Date& other) {
    return ((this->day == other.day) == 1 && (this->month == other.month) == 1 && (this->year == other.year) == 1);
}
bool Date::operator != (const Date& another) {
    return !(*this == another);
}
bool Date::operator > (const Date& another) {
    if ((*this == another) == 1) return 0;
    else {
        if (this->year > another.year == 1) return 1;
        else {
            if (this->month > another.month == 1) return 1;
            else {
                if (this->day > another.day == 1) return 1;
                else return 0;
            }
        }
        }
}

bool Date::operator < (const Date& another) {
    return !(*this > another);
}