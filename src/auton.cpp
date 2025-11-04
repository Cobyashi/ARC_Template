#include "auton.h"

void setDriveConstants()
{
    //
    chassis.setDriveConstants(5, 0.01, 10, 0.5, 300, 3000);

    chassis.setTurnConstants(.4, .03, 3
                            , 0.5, 300, 3000);
}