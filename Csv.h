//
// Created by 金海林 on 2022/9/16.
//

#ifndef ICSPRODUCER_CSV_H
#define ICSPRODUCER_CSV_H


#include <vector>
#include <string>

class Csv {
// Type Alias
public:
    using Row = std::vector<std::string>;
    using Table = std::vector<Row>;
// Member Data
public:
    Table _table;
    std::string _path;
	std::string _errMSG = "out of range";
// Constructors
public:
    Csv(const std::string& path): _path(path) { read_csv(path); format_csv(); }
    Csv() = default;
// Member Functions
public:
    int read_csv(const std::string& path);
    const std::string& at(Table::difference_type row, Row::difference_type col) const;
    const Row& getRow(Table::size_type index) const {
        auto itTable = _table.begin();
        return *(itTable + index);
    };
    const std::string getPath() const { return _path; };
    void display_csv();
    Table::size_type rowSize() const { return _table.size(); };
    static Row::size_type colSize(const Row& row) { return row.size(); };
private:
    void format_csv();
};


#endif //ICSPRODUCER_CSV_H
