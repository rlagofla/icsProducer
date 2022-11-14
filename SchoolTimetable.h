//
// Created by 金海林 on 2022/10/12.
//
// 类好多，我脑子转不过来了，没关系，agile software development，大不了以后改
// 这个类负责一天中的时间，不管年月日

#ifndef ICSPRODUCER_SCHOOLTIMETABLE_H
#define ICSPRODUCER_SCHOOLTIMETABLE_H

#include "Csv.h"
#include "Date.h"
#include <vector>


class SchoolTimetable: private Csv{
// Member Data
public:
    const Date firstWeek;
// Constructors
public:
    SchoolTimetable(const std::string& path): Csv(path), firstWeek(_table.back().front()) { }
// Member Functions
public:
    void display();
    std::string getSTART(Table::size_type index) { return getRow(index).at(1) + "00"; }
    std::string getEND(Table::size_type index) { return getRow(index).at(2) + "00"; }
    void display_csv() { Csv::display_csv(); }
};

#endif //ICSPRODUCER_SCHOOLTIMETABLE_H
