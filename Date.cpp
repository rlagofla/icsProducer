//
// Created by 金海林 on 2022/11/11.
//

#include "Date.h"

bool Date::isLegal() const {
    // month
    if(!(_month >= 1 && _month <= 12)) return false;
    // day
    if((_month == 2) && ((_year % 4 == 0 && _year % 100 != 0) || _year % 400 == 0)){
        if(!(_day >=1 && _day <= MAX_DAY[_month-1]+1)) return false;
    }else{
        if(!(_day >=1 && _day <= MAX_DAY[_month-1])) return false;
    }
    return true;
}

void Date::addDay(int days) {
    for(int i = 0; i < days; ++i) {
        ++_day;
        if (!isLegal()) {
            ++_month;
            _day = 1;
            if (!isLegal()) {
                ++_year;
                _month = 1;
            }
        }
    }
}

