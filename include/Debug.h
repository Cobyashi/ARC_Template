#pragma once

#include "vex.h"
#include <cstring>
#include <iostream>
#include <string>

class Debug
{
    private:

    brain Brain;
    std::ofstream data_log;
    const char* file;

    public:

    Debug(std::string file_name);
    ~Debug();

    char* stringToChar(std::string str);
    uint8_t* stringToUint8(std::string str);

    void log(std::string info);
    void error(std::string info);
    void warning(std::string info);
};