#include "SchoolSchedules.h"
#include "SchoolTimetable.h"
#include "PixelFont.h"
#include <iostream>
#include <string>


#ifdef _WIN32
#define CHSET system("chcp 65001")
#else
#define CHSET
#endif


int main(int argc, char *argv[]) {
    // 欢迎光临～
    CHSET;
    PixelFont::printWord("welcome", 2);
    //
    std::string SchedulesPath, TimetablePath;
    std::cout << "请将*校历*文件拖进这个窗口（或者把路径粘进来也行）：" << std::endl;
    getline(std::cin, TimetablePath);
    if(TimetablePath.find_last_of(' ') == TimetablePath.size() - 1) TimetablePath.pop_back(); // 去掉末尾多余的空格
    SchoolTimetable schoolTimetable(TimetablePath);
    
    std::cout << std::endl << "这是你的校历：" << std::endl;
    schoolTimetable.display();
    std::cout << std::endl;

    std::cout << "请将*课表*文件拖进这个窗口（或者把路径粘进来也行）：" << std::endl;
    getline(std::cin, SchedulesPath);
    if(SchedulesPath.find_last_of(' ') == SchedulesPath.size() - 1) SchedulesPath.pop_back(); // 去掉末尾多余的空格

    SchoolSchedules timetable(SchedulesPath, schoolTimetable);
    
    if(!timetable.export_ics()){
        std::cout << "成功输出" << std::endl;
        getc(stdin);
    }

    return 0;
}
