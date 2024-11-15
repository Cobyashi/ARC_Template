#include "Debug.h"

    
    /// @brief Logs info to debug file 
    /// @param info The information written into the debug file
    void Debug::log(char* info)
    {
        uint8_t* bitInfo;
        std::ofstream data;
        data.open("test.txt", std::ios::app);
        // if(data.is_open())
        //     data << "Testing...";
        // else    
        //     Brain.Screen.print("Error opening file");
        // data.close();

        // Brain.Screen.print("Done");


        bitInfo = reinterpret_cast<uint8_t*>(info);

        Brain.SDcard.savefile("test.txt", bitInfo, 'utf-8');
        if(!Brain.SDcard.isInserted()){
            Brain.Screen.print("SD Card not inserted");
        }
        if(!Brain.SDcard.exists("test.txt")){
            Brain.Screen.print("File does not exist");
        }


        //Brain.SDcard.savefile("test.txt", bitInfo, sizeof(bitInfo));
        Brain.Screen.print("  Hopefully saved to file");


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