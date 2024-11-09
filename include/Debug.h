#pragma once

#include "vex.h"
#include <fstream>
#include <vector>

class Debug
{
    private:

    brain Brain;
    std::ofstream data_log;
    std::string file;

    public:

    Debug(std::string file_name, std::vector<std::string> column_names);
    ~Debug();

    int add_data(std::vector<double> row);
    void log(std::string info);
    void error(std::string info);
    void warning(std::string info);
};