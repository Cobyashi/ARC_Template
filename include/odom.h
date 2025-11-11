#pragma once

#include "util.h"

class Odom
{
    private:
        //Variables to hold the degrees turned
        float lateralDegrees;
        float forwardDegreesR;
        float forwardDegreesL;

        //Variables to store the current position and heading
        float xPosition;
        float yPosition;
        float heading;
    
    public:
        //Wheel diameters for the odometry pods
        float forwardRightWheelDiameter;
        float forwardLeftWheelDiameter;
        float lateralWheelDiameter;

        //Distance the odometry wheels are from the center of the robot
        float forwardRightRotationDistance;
        float forwardLeftRotationDistance;
        float lateralRotationDistance;

        //Variables for two pods at 45
        //In inches
        float wheelDiameter45;
        float leftRotationDistance;
        float rightRotationDistance;

        Odom();
        Odom(float forwardRightWheelDiameter, float forwardLeftWheelDiameter, float lateralWheelDiameter, float forwardRightRotationDistance, float forwardLeftRotationDistance, float lateralRotationDistance);
        Odom(float forwardWheelDiameter, float lateralWheelDiameter, float forwardRotationDistance, float lateralRotationDistance);
        Odom(float wheelDiameter45, float leftRotationDistance, float rightRotationDistance);

        void resetRotation();

        //Accessors
        float getXPosition();
        float getYPosition();
        float getHeading();

        float getLateralDegrees();
        float getForwardRightDegrees();
        float getForwardLeftDegrees();

        //Mutators
        void setPosition(float xPosition, float yPosition, float heading);
        void setHeading(float heading);

        void setForwardRightDegrees(float forwardDegreesR);
        void setForwardLeftDegrees(float forwardDegreesL);
        void setLateralDegrees(float lateralDegrees);

        //Updaters
        void updatePositionTwoForward(float currentForwardRightPosition, float currentForwardLeftPosition, float currentLateralPosition);
        void updatePositionOneForward(float currentForwardPosition, float currentLateralPosition, float headingGyro);
        void updatePositionTwoAt45(float currentLeftDegrees, float currentRightDegrees, float headingGyro);

};