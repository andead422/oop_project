#include "date.hpp"

int Date::days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//для місяців треба ділення по модулю але аби нуль це 12
int Date::mod12(int a) const { 
    if (a % 12 == 0) return 12;
    else return a % 12; 
}

//поточна дата
Date::Date() {
    time_t t = time(0);
    tm* now = localtime(&t);

    day = now->tm_mday;
    //бо місяці від 0
    month = now->tm_mon + 1;
    year = now->tm_year + 1900;
}

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
 В версии постфикс нам нужно возвращать объект до того, как он будет увеличен или уменьшен. И тут конфуз! *олала*
 Если мы увеличиваем или уменьшаем объект, то мы не можем возвратить его до выполнения инкремента/декремента,
 так как операция увеличения/уменьшения уже произошла. С другой стороны, если мы возвращаем объект 
 до выполнения инкремента/декремента, то сама операция увеличения/уменьшения объекта не выполнится.

 Решением является использование временного объекта с текущим значением переменной-члена. 
 Тогда можно будет увеличить/уменьшить исходный объект, а временный объект возвратить обратно в caller. 
 Таким образом, caller получит копию объекта до того, как фактический объект будет увеличен или уменьшен, 
 и сама операция инкремента/декремента выполнится успешно.*/

//+1 день, із врахуванням варіанту збільшення місяця, року
Date& Date::operator++() {
    day++;
    if (day > days[month - 1]) {
        day = 1;

        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
    return *this;
}

//-1 день, із врахуванням варіанту зменшення місяця, року
Date& Date::operator--() {
    day--;
    if (day == 0) {
        month--;
        if (month == 0) {
            month = 12;
            year--;
        }

        //ставимо останній день вже попереднього місяця
        day = days[month - 1];
    }
    return *this;
}

Date Date::operator++(int) {
    Date temp = *this;
    ++(*this);
    return temp;
}

Date Date::operator--(int) {
    Date temp = *this;
    --(*this);
    return temp;
}

Date Date::operator + (const Date& temp) const { 
    //об'єкт який будемо повертати
    Date output;

    //можна було обійтись без змінної дня, але заради більшої читабельності коду хай буде
    int sDay = this->day + temp.day,
        sMonth = this->month + temp.month,
        sYear = this->year + temp.year;
    
    //надлишкові дні переносимо у місяці
    if(sDay > days[mod12(sMonth) - 1]) {
        output.day = sDay % days[mod12(sMonth) - 1];
        sMonth++;
    } 
    else {
        output.day = sDay;
    }

    output.month = mod12(sMonth);

    //надлишкові місяці переносимо у роки
    output.year = sYear + (sMonth - output.month) / 12;

    return output;
}

//рахує кількість днів до поточного місяця
int Date::culcDaysInMonthsNum() const {
    int summ;

    for (int ii = 0; ii < month; ++ii) {
        summ += days[ii];
    }

    return summ;
}

// Date Date::numDaysToDate(int num) const {
//     Date output;

//     //-1 бо 31.12.2022 це не 2023 хоча з початку року пройшло 365 днів
//     output.year = (num - 1) / 365;
//     num -= 365*output.year;

//     output.month = numDaysToMonth(num);
//     output.day = num - output.culcDaysInMonthsNum();

//     return output;
// }

// int numDaysToMonth(int num) const {
//     //рік починається з першого місяця
//     int month = 1;

//     //строга нерівність адже 31.12 це не 00.01
//     while(num > days[month - 1]) {
//         num -= days[month - 1];
//         month++;
//     }

//     return month;
// }


