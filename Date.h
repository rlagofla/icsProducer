//
// Created by 金海林 on 2022/11/11.
//

#ifndef ICSPRODUCER_DATE_H
#define ICSPRODUCER_DATE_H


#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>

class Date {
// Member Data
private:
    int _year = 0;
    int _month = 0;
    int _day = 0;
    static constexpr int MAX_DAY[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
// Constructor
public:
    Date(int year, int month, int day) : _year(year), _month(month), _day(day) {}
    Date(const std::string& date) {
        std::istringstream y(date.substr(0, 4));
        y >> _year;
        std::istringstream m(date.substr(4, 2));
        m >> _month;
        std::istringstream d(date.substr(6, 2));
        d >> _day;
    }

// Member Functions
public:
    Date &setDate(int year, int month, int day) {
        _year = year;
        _month = month;
        _day = day;
        return *this;
    }
    std::string getDate() const {
        std::ostringstream date;
        date << _year << '/'
            << std::setw(2) << std::setfill('0') <<_month << '/'
            << std::setw(2) << std::setfill('0') << _day << std::flush;
        return date.str();
    }
    std::string get_icsDate() const {
        std::ostringstream date;
        date << _year
            << std::setw(2) << std::setfill('0') <<_month
            << std::setw(2) << std::setfill('0') << _day << std::flush;
        return date.str();
    }
    void addDay(int days);
    static Date addDay(const Date& date, int days) { Date newDate(date); newDate.addDay(days); return newDate; };
    bool isLegal() const;
};


#endif //ICSPRODUCER_DATE_H
