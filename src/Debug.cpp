#include "../include/Debug.h"

Debug::Debug(std::string file_name, std::vector<std::string> column_names)
{
    file = file_name;

    if (Brain.SDcard.isInserted())
    {
        data_log.open(file, std::ofstream::out | std::ofstream::trunc);
        
        //Label column names
        data_log << "Time, ";
        for (int i = 0; i < column_names.size() - 1; i++)
            data_log << column_names.at(i) << ", ";

        data_log << column_names.at(column_names.size() - 1) << "\n";
        data_log.close();
    }
}

Debug::~Debug() 
{
    data_log.close();
}

int Debug::add_data(std::vector<double> row) 
{
    if (Brain.SDcard.isInserted())
    {
        data_log.open(file, std::ofstream::app);

        if(!data_log.is_open())
            return 2;

        data_log << Brain.timer(vex::timeUnits::sec) << ", ";

        for (int i = 0; i < row.size() - 1; i++)
            data_log << row.at(i) << ", ";

        data_log << row.at(row.size() - 1) << "\n";
        data_log.close();
        return 1;
    }

    return 2;
}

/// @brief 
/// @param info 
void Debug::error(std::string info)
{

    Brain.Screen.setPenColor(white);
    Brain.Screen.setFillColor(red);
    Brain.Screen.drawRectangle(240, 130, 100, 50);
}

/// @brief 
/// @param info 
void Debug::warning(std::string info)
{

}