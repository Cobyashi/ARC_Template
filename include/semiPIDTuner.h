#pragma once
#include "vex.h"
#include "drive.h"
class PIDTuner {
    public:
        explicit PIDTuner(Drive& chassis);
        void run();
    private:
        Drive& chassis;
        
        //Default Parameters of the semiPID Tuner
        struct ParameterSet {
            float kP = 0.0f;
            float kI = 0.0f;
            float kD = 0.0f;
            float settleError = 1.0f;
            int timeToSettle = 250;
            int endTime = 3000;
        };

        ParameterSet driveParameters;
        ParameterSet turnParameters;

        //UI Setup
        enum Screen {SCR_MAIN, SCR_EDIT_FLOAT, SCR_EDIT_INT};
        enum Mode {MODE_DRIVE, MODE_TURN};

        Screen currentScreen = SCR_MAIN;
        Mode currentMode = MODE_DRIVE;

        //Fields on main controller screen (P, I, D, settleError, settleTime, endTime)
        int fieldSelector = 0;

        //Which direction the robot will drive
        bool testGoForward = true;

        //Setup for drive distances(in) and turn distances(deg), adjustable in semiPIDTuner.cpp
        static const int DRIVE_DISTANCES[];
        static const int NUM_DRIVE_DISTANCES;
        static const int TURN_DISTANCES[];
        static const int NUM_TURN_DISTANCES;
        int distIndx = 3;

        //SCR_EDIT_FLOAT values
        float editFloatValue = 0.0f;
        float editFineStep = 0.01f;
        float editCoarseStep = 0.1f;
        float editFloatMin = 0.0f;
        float editFloatMax = 99.99f;

        //SCR_EDIT_INT values
        int editIntVal = 0;
        int editFineStepI = 25;
        int editCoarseStepI = 100;
        int editIntMin = 0;
        int editIntMax = 9999;

        //labels on edit screen
        const char* editLabel = "";

        //hold timers
        int holdUp = 0;
        int holdDown = 0;

        //Tells if the user is holding down the up or down arrow when adjusting values
        bool shouldFire(int holdCount) const;

        //All the buttons used
        struct BtnSnapshot {bool A, B, R1, L1, R2, Up, Down, Left, Right;};
        
        //Stores buttons from previous loop, used for detecting new button presses
        BtnSnapshot prevBtns = {};
        //Returns buttons that were pressed just this loop
        BtnSnapshot edgeButtons();
        //Returns current state of all buttons, true while a button is held down
        BtnSnapshot rawButtons();

        //Returns drive or turn paramter set 
        ParameterSet& activeParams();
        //Return a string for current mode (DrivePID or TurnPID)
        const char* modeLabel() const;

        //Points to which distance array is currently active (DRIVE_DISTANCES, TURN_DISTANCES)
        const int* activeDistances() const;
        //Returns what number of values the current array is (NUM_DRIVE_DISTANCEs, NUM_TURN_DISTANCES)
        int activeNumDistances() const;

        //Applies the paramters to the robot chassis before the robot drives, both drive and turn
        void applyParamsToChassis();

        //Opens edit screen for a paramter
        void openEditScreen();
        //Saves the values into the current paramter set
        void saveEditScreen();

        //Draws main screen on Controller
        void drawMain();
        //Draws Edit FLoat Screen on Contoller for parameters P, I, D, or settleError
        void drawEditFloat();
        //Draws Edit Int Screen on Controlller for parameters settleTime and endTime 
        void drawEditInt();

        void exportCurrentProfile();

        
        //Runs the actual Drive Test
        void runTest();

};