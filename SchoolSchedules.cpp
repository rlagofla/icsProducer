//
// Created by 金海林 on 2022/10/12.
//

#include "SchoolSchedules.h"
#include "Date.h"
#include <string>
#include <fstream>
#include <sstream>


int SchoolSchedules::export_ics(const std::string& path) {
    std::ofstream output(path);
    output << "BEGIN:VCALENDAR\n"
              "VERSION:2.0" << std::endl;
    
    int cnt = 1;
    for(const auto& schedule : _table){
        output << "BEGIN:VEVENT" << std::endl;
        output << "UID:fromRlagofla" << cnt << std::endl;
        // SUMMARY
		auto cell = schedule.at(0);
		if(cell.empty()) cell = "Lorem";
        output << "SUMMARY:" << cell << std::endl;
		// Time Duration
            // 星期几
		cell = schedule.at(1);
		int NoWeek = atoi(cell.c_str()) == 0 ? 1 : atoi(cell.c_str());
            // 几节到几节
		cell = schedule.at(2);
		if(cell.empty()) cell = "1 2";
        std::istringstream lessonDuration(cell);
        int beginLesson, endLesson;
        lessonDuration >> beginLesson >> endLesson;
            // 几周到几周
		cell = schedule.at(5);
		if(cell.empty()) cell = "1 21";
        std::istringstream weekDuration(cell);
        int beginWeek, endWeek;
        weekDuration >> beginWeek >> endWeek;
            // 开始时间
        auto beginDate = Date::addDay(_schoolTimetable.firstWeek, (beginWeek - 1) * 7);
        beginDate.addDay(NoWeek - 1);
            // 结束时间
        auto endDate = Date::addDay(_schoolTimetable.firstWeek, endWeek * 7 - 1);
            // INTERVAL
		cell = schedule.at(6);
		if(cell.empty()) cell = "1";
        output << "DTSTART:" << beginDate.get_icsDate() << 'T'
               << _schoolTimetable.getSTART(beginLesson - 1) << std::endl;
        output << "DTEND:" << beginDate.get_icsDate() << 'T'
               << _schoolTimetable.getEND(endLesson - 1) << std::endl;
        output << "RRULE:FREQ=" << "WEEKLY" << ';'
            << "INTERVAL=" << cell << ';'
            << "UNTIL=" << endDate.get_icsDate() << "T000000" << std::endl;
        // ALARM
        cell = schedule.at(3);
        if(cell.empty()) goto JUMP;
        output << "BEGIN:VALARM\n"
                  "TRIGGER;RELATED=START:-PT" << cell << 'M' << std::endl;
        output << "END:VALARM" << std::endl;
        JUMP:
        // LOCATION
        output << "LOCATION:" << schedule.at(4) << std::endl;
        // DESCRIPTION
        output << "DESCRIPTION:" << schedule.at(7) << std::endl
               << "END:VEVENT" << std::endl;
        ++cnt;
    }


    output << "END:VCALENDAR" << std::flush;
    output.close();
	std::cout << "\nfile locate at \'" << path << '\'' << std::endl;
    return 0;
}
