#include "Sensors.h"

    //INERTIAL GROUP CONSTRUCTOR
    inertial_group::inertial_group(inertial * sensorArray, int arraySize)
    {
        sensors = sensorArray;
        size = arraySize;
    }

    /// @brief Calibrates all of the inertial sensors within the inertial group
    void inertial_group::calibrate()
    {
        for(int i = 0; i < size; i++)
            sensors[i].calibrate();
    }

    /// @brief Checks to see if any of the inertial sensors are calibrating
    /// @return Returns true if the inertial sensors are still calibrating
    bool inertial_group::isCalibrating()
    {
        for(int i = 0; i < size; i++)
        {
            if(sensors[i].isCalibrating())
                return true;
        }
        return false;
    }

    /// @brief Resets the Heading of the inertial sensors to 0
    void inertial_group::resetHeading()
    {
        for(int i = 0; i < size; i++)
            sensors[i].resetHeading();
    }

    /// @brief Sets the inertial sensors to a new heading
    /// @param heading The new heading for the sensors
    /// @param unit The rotation unit for the angle
    void inertial_group::setHeading(float heading, rotationUnits unit)
    {
        for(int i = 0; i < size; i++)
            sensors[i].setHeading(heading, unit);
    }

    //Returns the average heading of the inertial sensors and returns a degree in integers
    //Find a way to work with more than two sensors
    float inertial_group::getHeading()
    {
        float output = 0;

        //Gets the average rotation of the sensors
        for(int i = 0; i < size; i++)
            output = sensors[i].rotation(degrees);
        output = output / size;

        //Converts the rotation into terms of 0 to 360
        output = fmod(output, 360.0);
        if(output < 0) output += 360.0;
        
        return output;
    }   

    /// @brief Resets the rotation of the sensors to 0
    void inertial_group::resetRotation()
    {
        for(int i = 0; i < size; i++)
            sensors[i].resetRotation();
    }

    /// @brief Sets the rotation of the inertial sensors to the given rotation
    /// @param rotation The new absolute angle value of the inertial sensors
    /// @param units The rotation unit for the angle
    void inertial_group::setRotation(float rotation, rotationUnits units)
    {
        for(int i = 0; i < size; i++)
            sensors[i].setRotation(rotation, units);
    }

    /// @brief Gets the absolute angle of the inertial sensor in deg
    /// @param unit The unit of measurement used for the inertial sensor
    /// @return Returns the specified value depending on the given unit
    float inertial_group::getRotation(rotationUnits units)
    {
        float totalRotation = 0;

        for(int i = 0; i < size; i++)
            totalRotation += sensors[i].rotation(units);

        return totalRotation / size;
    }

    /// @brief Gets the acceleration of a specific axis of the Inertial Sensors
    /// @param axis the inertial sensor axis to use
    /// @return value of the inertial sensor access acceleration
    float inertial_group::acceleration(axisType axis)
    {
        float output = 0;

        for(int i = 0; i < size; i++)
            output = sensors[i].acceleration(axis);

        return output / size;
    }