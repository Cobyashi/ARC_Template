#include "Odom.h"

/// @brief Constructor for odometry with two forward rotation sensors
/// @param forwardRightWheelDiameter Right side forward rotation wheel diameter
/// @param forwardLeftWheelDiameter Left side forward rotation wheel diameter
/// @param lateralWheelDiameter Lateral rotation wheel diameter
/// @param forwardRightRotationDistance Distance the forward right wheel is from the center (in)
/// @param forwardLeftRotationDistance Distance the forward left wheel is from the center (in)
/// @param lateralRotationDistance Distance the lateral wheel is from the center (in)
Odom::Odom(float forwardRightWheelDiameter, float forwardLeftWheelDiameter, float lateralWheelDiameter, float forwardRightRotationDistance, float forwardLeftRotationDistance, float lateralRotationDistance){
    this->forwardRightWheelDiameter = forwardRightWheelDiameter;
    this->forwardLeftWheelDiameter = forwardLeftWheelDiameter;
    this->lateralWheelDiameter = lateralWheelDiameter;
}

/// @brief Constructor for odometry with one forward rotation sensor
/// @param forwardWheelDiameter Forward rotation wheel diameter 
/// @param lateralWheelDiameter Lateral rotation wheel diameter
/// @param forwardRotationDistance Distance the forward wheel is from the center (in)
/// @param lateralRotationDistance Distance the lateral wheel is from the center (in)
Odom::Odom(float forwardWheelDiameter, float lateralWheelDiameter, float forwardRotationDistance, float lateralRotationDistance){
    this->forwardRightWheelDiameter = forwardWheelDiameter;
    this->lateralWheelDiameter = lateralWheelDiameter;
    this->forwardRightRotationDistance = forwardRotationDistance;
    this->lateralRotationDistance = lateralRotationDistance;
}


/// @brief Sets all rotation degrees to 0.0
void Odom::resetRotation(){
    forwardDegreesL = 0.0;
    forwardDegreesR = 0.0;
    lateralDegrees = 0.0;
}

//Accessors
float Odom::getXPosition(){ return xPosition; }
float Odom::getYPosition(){ return yPosition; }
float Odom::getHeading(){ return heading;}
float Odom::getForwardRightDegrees(){ return forwardDegreesR; }
float Odom::getForwardLeftDegrees(){ return forwardDegreesL; }
float Odom::getLateralDegrees(){ return lateralDegrees; }

//Mutators
void Odom::setPosition(float xPosition, float yPosition, float heading = 0.0){
    this->xPosition = xPosition;
    this->yPosition = yPosition;
    this->heading = heading;
}
void Odom::setHeading(float heading){
    this->heading = heading;
}
void Odom::setForwardRightDegrees(float forwardDegreesR){
    this->forwardDegreesR = forwardDegreesR;
}
void Odom::setForwardLeftDegrees(float forwardDegreesL){
    this->forwardDegreesL = forwardDegreesL;
}
void Odom::setLateralDegrees(float lateralDegrees){
    this->lateralDegrees = lateralDegrees;
}


/// @brief Updates the coordinate position of the robot with two forward rotation sensors and one lateral
/// @param currentForwardRightPosition Forward right rotation degrees
/// @param currentForwardLeftPosition Forward left rotation degrees
/// @param currentLateralPosition Lateral rotation degrees
void Odom::updatePositionTwoForward(float currentForwardRightDegrees, float currentForwardLeftDegrees, float currentLateralDegrees){
    //Get current positions based on rotation sensors
    float currentForwardRightPosition = currentForwardRightDegrees/360.0*(M_PI*forwardRightWheelDiameter);
    float currentForwardLeftPosition = currentForwardLeftDegrees/360.0*(M_PI*forwardLeftWheelDiameter);
    float currentLateralPosition = currentLateralDegrees/360.0*(M_PI*lateralWheelDiameter);

    //Get positions since last update
    float oldForwardRightPosition = getForwardRightDegrees()/360.0*(M_PI*forwardRightWheelDiameter);
    float oldForwardLeftPosition = getForwardLeftDegrees()/360.0*(M_PI*forwardLeftWheelDiameter);
    float oldLateralPosition = getLateralDegrees()/360.0*(M_PI*lateralWheelDiameter);

    //Get the change based on rotations
    float deltaForwardRight = currentForwardRightPosition - oldForwardRightPosition;
    float deltaForwardLeft = currentForwardLeftPosition - oldForwardLeftPosition;
    float deltaLateral = currentLateralPosition-oldLateralPosition;

    //Gives answer in radians
    float deltaY;
    float deltaX;
    float deltaHeading = (deltaForwardLeft-deltaForwardRight)/(forwardLeftRotationDistance+forwardRightRotationDistance);
    
    if(deltaHeading==0.0){
        deltaX=deltaLateral;
        deltaY=deltaForwardRight;
    }else{
        deltaY = 2.0*((deltaForwardRight/deltaHeading)+forwardRightRotationDistance)*sin(deltaHeading/2.0);
        deltaX = 2.0*((deltaLateral/deltaHeading)+lateralRotationDistance)*sin(deltaHeading/2.0);
    }

    //Update x and y positions and heading
    setPosition((deltaX+getXPosition()), (deltaY+getYPosition()), ((deltaHeading*180.0/M_PI)+getHeading()));

    //Update variables to store new location information
    setForwardLeftDegrees(currentForwardLeftPosition);
    setForwardRightDegrees(currentForwardRightPosition);
    setLateralDegrees(currentLateralPosition);

}

/// @brief Updates the coordinate position of the robot with one forward and one lateral rotation sensor
/// @param currentForwardPosition Forward rotation degrees
/// @param currentLateralPosition Lateral rotation degrees
/// @param headingGyro Heading in degrees
void Odom::updatePositionOneForward(float currentForwardDegrees, float currentLateralDegrees, float headingGyro){
    //Get current positions based on rotation sensors
    float currentForwardPosition = currentForwardDegrees/360.0*(M_PI*forwardRightWheelDiameter);
    float currentLateralPosition = currentLateralDegrees/360.0*(M_PI*lateralWheelDiameter);

    //Get positions since last update
    float oldForwardPosition = getForwardRightDegrees()/360.0*(M_PI*forwardRightWheelDiameter);
    float oldLateralPosition = getLateralDegrees()/360.0*(M_PI*lateralWheelDiameter);

    //Get the change based on rotations
    float deltaForward = currentForwardPosition - oldForwardPosition;
    float deltaLateral = currentLateralPosition-oldLateralPosition;

    //Gives answer in radians
    float deltaY;
    float deltaX;

    float deltaHeading = headingGyro-getHeading();

    if(fabs(deltaHeading) == 0){
        deltaY=deltaForward;
        deltaX=deltaLateral;
    }else{
        deltaY = 2.0*((deltaForward/degToRad(deltaHeading))+forwardRightRotationDistance)*sin(degToRad(deltaHeading)/2.0);
        deltaX = 2.0*((deltaLateral/degToRad(deltaHeading))+lateralRotationDistance)*sin(degToRad(deltaHeading)/2.0);
    }

    //Update x and y positions and heading
    float avgHeading = degToRad(getHeading()+deltaHeading/2.0);
    float globalDeltaX = deltaX * cos(avgHeading) - deltaY * sin(avgHeading);
    float globalDeltaY = deltaX * sin(avgHeading) + deltaY * cos(avgHeading);
    setPosition((globalDeltaX+getXPosition()), (globalDeltaY+getYPosition()), headingGyro);
    
    //Update variables to store new location information
    setForwardRightDegrees(currentForwardDegrees);
    setLateralDegrees(currentLateralDegrees);
    setHeading(headingGyro);
}