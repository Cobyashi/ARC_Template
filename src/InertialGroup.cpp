#include "InertialGroup.h"

    /// @brief Creates a inertial sensor group
    /// @tparam The inertial sensors 
    template <typename... Args>
    inertial_group::inertial_group(vex::inertial &i1, Args &... i2)
    {
        group.push_back(i1);
        group.push_back(i2 ... );
    }

    /// @brief Calibrates all of the inertial sensors within the inertial group
    void inertial_group::calibrate()
    {
        for(int i = 0; i < group.size(); i++)
            group.at(i).calibrate();
    }

    /// @brief Checks to see if any of the inertial sensors are calibrating
    /// @return Returns true if the inertial sensors are still calibrating
    bool inertial_group::isCalibrating()
    {
        for(int i = 0; i < group.size(); i++)
            if(group.at(i).isCalibrating()) return true;

        return false;
    }

    /// @brief Resets the Heading of the inertial sensors to 0
    void inertial_group::resetHeading()
    {
        for(int i = 0; i < group.size(); i++)
            group.at(i).resetHeading();
    }

    /// @brief Sets the inertial sensors heading to a new value
    /// @param value The new heading of the inertial sensors
    /// @param units The rotation unit for the angle
    void inertial_group::setHeading(float value, vex::rotationUnits units)
    {
        for(int i = 0; i < group.size(); i++)
            group.at(i).setHeading(value, units);
    }

    //Returns the average heading of the inertial sensors and returns a degree in integers
    //Find a way to work with more than two sensors
    float inertial_group::heading()
    {
        // Gets Average rotation of the inertial sensor group
        float output = 0;
        for(int i = 0; i < group.size(); i++)
            output += group.at(i).rotation();
        output = output / group.size();

        //Converts the rotation into terms of 0 to 360
        output = fmod(output, 360.0);
        if(output < 0) 
            output += 360.0;
        
        return output;
    }

    /// @brief reset the rotation angle of the inertial sensors to 0
    void inertial_group::resetRotation()
    {
        for(int i = 0; i < group.size(); i++)
            group.at(i).resetRotation();
    }

    /// @brief et the inertial sensors rotation to angle
    /// @param value The new absolute rotation angle for the inertial sensors
    /// @param units The rotation unit for the angle
    void inertial_group::setRotation(float value, vex::rotationUnits units)
    {
        for(int i = 0; i < group.size(); i++)
            group.at(i).setRotation(value, units);
    }

    /// @brief Gets the absolute angle (yaw angle without limits) of the inertial sensors
    /// @return The rotation value of the inertial sensors in deg
    float inertial_group::rotation()
    {
        // Gets Average rotation of the inertial sensor group
        float output = 0;
        for(int i = 0; i < group.size(); i++)
            output += group.at(i).rotation();
        return output / group.size();
    }

    /// @brief Gets the inertial sensors raw acceleration data in G
    /// @param type the inertial sensors axis to use
    /// @return Calue of the specified inertial sensors axis
    float inertial_group::acceleration(vex::axisType type)
    {
        float output = 0;
        for(int i = 0; i < group.size(); i++)
            output += group.at(i).acceleration(type);
        return output / group.size();
    }

    /// @brief Determines whether or not the inertial sensors in the inertial group are installed
    /// @return Returns false if one or more interial sensors are not installed. Returns true if all inertial sensors are installed
    bool inertial_group::installed()
    {
        for(int i = 0; i < group.size(); i++)
            if(!group.at(i).installed()) return false;

        return true;
    }