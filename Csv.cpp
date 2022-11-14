//
// Created by 金海林 on 2022/9/16.
//

#include "Csv.h"
#include <fstream>
#include <iostream>

int Csv::read_csv(const std::string& path) {
    std::ifstream input(path);
    if(!input.is_open()) return 1;
    std::string line;  // to store a line in the csv file
    while(getline(input, line)){
        int flag = 0;
        if(line.find('\r') != line.npos) flag = 1;
        // define the index of which is part of content
        auto right = line.find(',');
        auto left = right - right;
        Row row;
        for( ; right != line.npos; left = right + 1, right = line.find(',', left)) {
            row.push_back(line.substr(left, right-left));
        }
        row.push_back(line.substr(left, line.size()-left-flag));
        _table.push_back(row);
    }
    return 0;
}

const std::string& Csv::at(Table::difference_type row, Row::difference_type col) const { // start from 0
    auto itRow = _table.begin();
	if(row > rowSize() - 1) return _errMSG;
    itRow += row;
    auto itCol = itRow->begin();
	if(col > colSize(getRow(row)) - 1) return _errMSG;
    itCol += col;

    return *itCol;
}

void Csv::display_csv() {
    for(const auto& i : _table){
        for(const auto& j : i){
            std::cout << j << ",\t";
        }
        std::cout << std::endl;
    }
}

void Csv::format_csv() {
    int maxCol = 0;
    for(auto& i : _table) maxCol = i.size() > maxCol ? i.size() : maxCol;
    for(auto& i : _table) {
        int preSize = i.size();
        for(int j = 0; j < maxCol-preSize; ++j) i.push_back("");
    }
}
