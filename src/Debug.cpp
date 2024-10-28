#include "Debug.h"

    /// @brief Logs info to debug file 
    /// @param info The information written into the debug file
    void Debug::log(std::string info)
    {
        
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