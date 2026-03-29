#include "pidTests.h"

/// @brief Test short drive distances of less than 10 inches. Both forwards and backwards movements.
// This test will drive a total of 10 inches forward. It alternates between going backwards and forwards.
/// Ex: 10 forward, then 10 back, then 9 forward, then 9 back, ..., until it gets to 1 forward and 1 back.
/// @param chassis Reference to the drivetrain class to used to control the robots movement.
void smallDrivingTest(Drive& chassis){
  if (chassis.getOdomType() != NO_ODOM){
    for (int d = 10; d < 0; d--){
      chassis.driveDistanceWithOdom(d);
      chassis.driveDistanceWithOdom(-d);
    }
  }else{
    for (int d = 10; d < 0; d--){
      chassis.driveDistance(d);
      chassis.driveDistance(-d);
    }
  }
}

/// @brief Test longer drive distances between 10 and 72 inches. Both forwards and backwards movements.
// This test will drive a total of 72 inches forward (3 vex tiles). It alternates between going backwards and forwards.
/// Ex: 10 forward, then 10 back, then 16 forward, then 16 back, and so on...
/// @param chassis Reference to the drivetrain class to used to control the robots movement.
void largeDrivingTest(Drive& chassis){
  if (chassis.getOdomType() != NO_ODOM){
    for (int d = 10; d < 72; d+= 6){
      chassis.driveDistanceWithOdom(d);
      chassis.driveDistanceWithOdom(-d);
    }
  }else{
    for (int d = 10; d < 72; d+= 6){
      chassis.driveDistance(d);
      chassis.driveDistance(-d);
    }
}
}

/// @brief Test a mixed combination of different drive distances. Both forwards and backwards movements.
/// These movements are randomly generated will move an absolute max of 48 inches forward and backwards.
/// So make sure to have 48 inches behind and in front of the vex robot.
/// @param chassis Reference to the drivetrain class to used to control the robots movement.
void mixedDrivingTest(Drive& chassis, int numberOfMoves){
  int currentDistance =0, maxDistance = 48;
  srand(time(nullptr));
  if (chassis.getOdomType() != NO_ODOM){
    for (int i=0; i < numberOfMoves; i++){
      int move = (rand() % 97) - 48; //rand() % 97 = 0-96; -48 = possibility of -48 to 48

      if (currentDistance + move > maxDistance){
        move = maxDistance - currentDistance;
      }
      if (currentDistance + move < -maxDistance){
        move = -maxDistance - currentDistance;
      }
      if (move != 0){
        std::cout << "Moving from " << currentDistance << " to " << currentDistance + move << "." << std::endl;
        chassis.driveDistanceWithOdom(move);
        currentDistance += move;
      }else{
        std::cout << "Skipped a move because move distance equalled 0." << std::endl;
      }
    }

  }else{
    for (int i=0; i < numberOfMoves; i++){
      int move = (rand() % 97) - 48; //rand() % 97 = 0-96; -48 = possibility of -48 to 48

      if (currentDistance + move > maxDistance){
        move = maxDistance - currentDistance;
      }
      if (currentDistance + move < -maxDistance){
        move = -maxDistance - currentDistance;
      }
      if (move != 0){
        std::cout << "Moving from " << currentDistance << " to " << currentDistance + move << "." << std::endl;
        chassis.driveDistance(move);
        currentDistance += move;
      }else{
        std::cout << "Skipped a move because move distance equalled 0." << std::endl;
      }
    }
}
}

/// @brief Test short turn distances of less than 10 degrees. Both left and right movements.
/// @param chassis Reference to the drivetrain class to used to control the robots movement.
void smallTurningTest(Drive& chassis){
  for (int d = 10; d > 0; d--){
      chassis.turnToAngle(d);
      chassis.turnToAngle(-d);
    }
}

/// @brief Test long turn distances between 10 degrees and 180 degrees. Both left and right movements.
/// @param chassis Reference to the drivetrain class to used to control the robots movement.
void largeTurningTest(Drive& chassis){
  for (int d = 10; d < 180; d+= 10){
      chassis.driveDistanceWithOdom(d);
      chassis.driveDistanceWithOdom(-d);
    }
}

/// @brief Test a mixed combination of different turn distances. Both left and right movements.
/// These numbers are rondomly generated and will turn to any angle from 0-360. 
/// @param chassis Reference to the drivetrain class to used to control the robots movement.
void mixedTurningTest(Drive& chassis, int numberOfMoves){
  int currentAngle =0;
  srand(time(nullptr));
    for (int i=0; i < numberOfMoves; i++){
      int move = (rand() % 361); 

      if (currentAngle == move){
        std::cout << "Turning from " << currentAngle << " degrees to " << move << "." << std::endl;
        chassis.turnToAngle(move);
        currentAngle = move;
      }else{
        std::cout << "Skipped a move because turn distance equalled 0." << std::endl;
      }
    }
}