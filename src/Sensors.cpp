#include "Sensors.h"

    /// @brief Constructor for inertial_group
    /// @param sensorArray An array of inertial sensors
    /// @param arraySize How many inertial sensors are in the array
    inertial_group::inertial_group(inertial * sensorArray, int arraySize)
    {
        sensors = sensorArray;
        size = arraySize;
    }

    template <typename... Args>
      inertial_group( vex::motor &m1, Args &... m2 ) : inertial_group() {
        _addMotor( m1 );
        _addMotor( m2... );
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
        //Sets the heading to an int since % only works with int
        int m1 = sensors[0].heading();
        int m2 = sensors[1].heading();
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print(m1);
        Brain.Screen.setCursor(2,1);
        Brain.Screen.print(m1);

        int d1 = (m2 - m1) % 360;
        int d2 = (m1 - m2) % 360;

        // if(d1 < d2)
        //     return m1 + (d1/2);
        // else
        //     return m2 + (d2/2);

        return d1 < d2 ? (m1+ (d1/2)) : (m2 + (d2/2));
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

    float inertial_group::acceleration(axisType axis)
    {
        return 0;
    }