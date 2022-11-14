//
// Created by 金海林 on 2022/10/12.
//

#include "SchoolTimetable.h"
#include <iostream>
#include <iomanip>

void SchoolTimetable::display() {
    for(const auto& lesson : _table){
        if(lesson.front().size() > 2) break;
        std::cout << "第" << std::setw(2) << lesson.at(0) << "节："
            << lesson.at(1)[0] << lesson.at(1)[1] << ":"
            << lesson.at(1)[2] << lesson.at(1)[3]
            << " -- "
            << lesson.at(2)[0] << lesson.at(2)[1] << ":"
            << lesson.at(2)[2] << lesson.at(2)[3] << std::endl;
    }
    std::cout << firstWeek.getDate() << std::endl;
}
