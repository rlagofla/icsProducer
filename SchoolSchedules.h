//
// Created by 金海林 on 2022/10/12.
//

#ifndef ICSPRODUCER_SCHOOLSCHEDULES_H
#define ICSPRODUCER_SCHOOLSCHEDULES_H

#include "Csv.h"
#include "SchoolTimetable.h"
#include <string>
#include <vector>
#include <utility>


class SchoolSchedules: private Csv {
// Member Data
private:
     SchoolTimetable _schoolTimetable;
     Row::size_type _length = 8;
// Constructors
public:
    SchoolSchedules(const std::string& SchedulesPath, const std::string& TimetablePath)
        : Csv(SchedulesPath), _schoolTimetable(TimetablePath) { format_schedule(); }
    SchoolSchedules(const std::string& SchedulesPath, SchoolTimetable Timetable)
        : Csv(SchedulesPath), _schoolTimetable(std::move(Timetable)) { format_schedule(); }  // 编译器给我加的 move，我不会
// Member Functions
public:
    int export_ics() {
        std::string path = _path.substr(0, _path.size()-4);
        path += ".ics";
        return export_ics(path);
    };
    int export_ics(const std::string& path);
    void display_csv() { Csv::display_csv(); }
    void format_schedule() {
        auto colSize = _table.front().size();
        if(colSize < _length)
            for(auto& j : _table)
                for(int i = 0; i < _length-colSize; ++i)
                    j.push_back("");
    }
};


#endif //ICSPRODUCER_SCHOOLSCHEDULES_H
