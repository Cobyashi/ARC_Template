#include "semiPIDTuner.h"
#include <cstdio>

/// @brief Sets the Values for both Drive_Distances and Turn_Distances
const int PIDTuner::DRIVE_DISTANCES[] = {3, 6, 12, 18, 24, 30, 36, 48, 72};
const int PIDTuner::NUM_DRIVE_DISTANCES = 9;
const int PIDTuner::TURN_DISTANCES[] = {5, 10, 30, 45, 90, 180, 270, 360};
const int PIDTuner::NUM_TURN_DISTANCES = 8;

/// @brief Constructor for PIDTuner Class
/// @param chassis Drive class 
PIDTuner::PIDTuner(Drive& chassis) : chassis(chassis){
    driveParameters.kP = 0.0f;
    driveParameters.kI = 0.0f;
    driveParameters.kD = 0.0f;
    driveParameters.settleError = 1.0f;
    driveParameters.timeToSettle = 200;
    driveParameters.endTime = 2500;

    turnParameters.kP = 0.0f;
    turnParameters.kI = 0.0f;
    turnParameters.kD = 0.0f;
    turnParameters.settleError = 1.0f;
    turnParameters.timeToSettle = 200;
    turnParameters.endTime = 2500;
}

/// @brief Determines if a button should fire during this cycle
/// @param h How many consecutive cycles the button has been held down for
/// @return true if the button should fire(or be pressed) during this cycle (initial press or consecutive intervals)
bool PIDTuner::shouldFire(int h) const {
    if (h == 1) return true; //intial press will fire
    if (h < 8) return false; //waits 8 cycles to make sure use wants to hold down button (40ms per, 320ms total wait time)
    if (h < 19) return (h % 5 == 0); //then fires every 5 cycles
    if (h < 38) return (h% 2 == 0); //faster cycle time, every 2 cycles
    return true;
}

/// @brief Returns current state of all buttons
/// Button returns true if it is being held and false if it is not.
/// @return A BtnSnapshot struct with all of the current buttons being pressed
PIDTuner::BtnSnapshot PIDTuner::rawButtons() {
    BtnSnapshot button;
    button.A = Controller1.ButtonA.pressing();
    button.B = Controller1.ButtonB.pressing();
    button.R1 = Controller1.ButtonR1.pressing();
    button.L1 = Controller1.ButtonL1.pressing();
    button.R2 = Controller1.ButtonR2.pressing();
    button.Up = Controller1.ButtonUp.pressing();
    button.Down = Controller1.ButtonDown.pressing();
    button.Left = Controller1.ButtonLeft.pressing();
    button.Right = Controller1.ButtonRight.pressing();
    return button;
}

/// @brief Returns if a button was just pressed during this loop or iteration
/// @return Returns a BtnSnapshot struct of buttons only pressed during this loop
PIDTuner::BtnSnapshot PIDTuner::edgeButtons() {
    BtnSnapshot current = rawButtons();
    BtnSnapshot edge;
    edge.A = current.A && !prevBtns.A;
    edge.B = current.B && !prevBtns.B;
    edge.R1 = current.R1 && !prevBtns.R1;
    edge.L1 = current.L1 && !prevBtns.L1;
    edge.R2 = current.R2 && !prevBtns.R2;
    edge.Up = current.Up && !prevBtns.Up;
    edge.Down = current.Down && !prevBtns.Down;
    edge.Left = current.Left && !prevBtns.Left;
    edge.Right = current.Right && !prevBtns.Right;
    prevBtns = current;
    return edge;
}

/// @brief Gets the current parameters depending on the currentMode
/// @return Returns reference to active parameter set to be able to be read or modified
PIDTuner::ParameterSet& PIDTuner::activeParams() {
    return (currentMode == MODE_DRIVE) ? driveParameters : turnParameters;
}

/// @brief Returns a string based on the currentMode
/// @return Returns DrivePID or TurnPID
const char* PIDTuner::modeLabel() const {
    return (currentMode == MODE_DRIVE) ? "DrivePID" : "TurnPID";
}

/// @brief Returns what distance are being used based on the currentMode
/// @return Returns a pointer to which distances are being used
const int* PIDTuner::activeDistances() const{
    return (currentMode == MODE_DRIVE) ? DRIVE_DISTANCES : TURN_DISTANCES;
}

/// @brief Gets the current number of distances in the current mode
/// @return Returns the number of distances in the current distance type being used (DRIVE_DISTANCES or TURN_DISTANCES) 
int PIDTuner::activeNumDistances() const{
    return (currentMode == MODE_DRIVE) ? NUM_DRIVE_DISTANCES : NUM_TURN_DISTANCES;
}

/// @brief Applies the Drive ad Turn parameters to the robot
void PIDTuner::applyParamsToChassis(){
    chassis.setDriveConstants(driveParameters.kP, driveParameters.kI, driveParameters.kD, driveParameters.settleError, driveParameters.timeToSettle, driveParameters.endTime);
    chassis.setTurnConstants(turnParameters.kP, turnParameters.kI, turnParameters.kD, turnParameters.settleError, turnParameters.timeToSettle, turnParameters.endTime);
}

/// @brief Opens the editor for the specific paramater chosen (P, I, D, settleError, settleTime, endTime)
void PIDTuner::openEditScreen() {
    ParameterSet& p = activeParams();
 
    switch (fieldSelector) {
        case 0:
            editLabel      = "P";
            editFloatValue   = p.kP;
            editFineStep   = 0.01f;
            editCoarseStep = 0.1f;
            editFloatMin   = 0.0f;
            editFloatMax   = 99.99f;
            currentScreen  = SCR_EDIT_FLOAT;
            break;
        case 1:
            editLabel      = "I";
            editFloatValue   = p.kI;
            editFineStep   = 0.0001f;
            editCoarseStep = 0.001f;
            editFloatMin   = 0.0f;
            editFloatMax   = 99.99f;
            currentScreen  = SCR_EDIT_FLOAT;
            break;
        case 2:
            editLabel      = "D";
            editFloatValue   = p.kD;
            editFineStep   = 0.01f;
            editCoarseStep = 0.1f;
            editFloatMin   = 0.0f;
            editFloatMax   = 99.99f;
            currentScreen  = SCR_EDIT_FLOAT;
            break;
        case 3:
            editLabel      = "Err";
            editFloatValue = p.settleError;
            editFineStep   = 0.05f;
            editCoarseStep = 0.5f;
            editFloatMin   = 0.0f;
            editFloatMax   = 99.99f;
            currentScreen  = SCR_EDIT_FLOAT;
            break;
        case 4:
            editLabel       = "Settle";
            editIntVal      = p.timeToSettle;
            editFineStepI   = 25;
            editCoarseStepI = 100;
            editIntMin      = 0;
            editIntMax      = 9999;
            currentScreen   = SCR_EDIT_INT;
            break;
        case 5:
            editLabel       = "End";
            editIntVal      = p.endTime;
            editFineStepI   = 25;
            editCoarseStepI = 100;
            editIntMin      = 0;
            editIntMax      = 9999;
            currentScreen   = SCR_EDIT_INT;
            break;
    }
 
    // Reset hold timers when entering any edit screen
    holdUp = holdDown = 0;
}

/// @brief Saves the current values to the parameters
void PIDTuner::saveEditScreen() {
    ParameterSet& p = activeParams();
    switch (fieldSelector) {
        case 0: p.kP           = editFloatValue; break;
        case 1: p.kI           = editFloatValue; break;
        case 2: p.kD           = editFloatValue; break;
        case 3: p.settleError  = editFloatValue; break;
        case 4: p.timeToSettle = editIntVal;     break;
        case 5: p.endTime      = editIntVal;     break;
    }
}

/// @brief Draws the Main Controller Screen
void PIDTuner::drawMain() {
    ParameterSet& p = activeParams();
    static const char* NAMES[6] = {"P", "I", "D", "Err", "Settle", "End"};
 
    Controller1.Screen.clearScreen();
 
    // Row 1: mode + distance
    Controller1.Screen.setCursor(1, 1);
    const int* distances = activeDistances();
    const char* unit = (currentMode == MODE_DRIVE) ? "in" : "deg";
    Controller1.Screen.print("%s [%d %s]", modeLabel(), distances[distIndx], unit);
 
    // Row 2: currently selected field with its value
    Controller1.Screen.setCursor(2, 1);
    if (fieldSelector <= 3) {
        float vals[4] = { p.kP, p.kI, p.kD, p.settleError };
        Controller1.Screen.print("%s  %.4f", NAMES[fieldSelector], (double)vals[fieldSelector]);
    } else {
        int vals[2] = { p.timeToSettle, p.endTime };
        Controller1.Screen.print("%s %d", NAMES[fieldSelector], vals[fieldSelector - 4]);
    }
 
    // Row 3: hints
    //Controller1.Screen.setCursor(2,15);
    Controller1.Screen.print(" R2=Run, B=Save");
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("A=Edit UD=%s LR=sel", unit);
}

/// @brief Draws the Screen when Editing a Float Variable (P, I, D, or settleError)
void PIDTuner::drawEditFloat() {
    Controller1.Screen.clearScreen();
 
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Edit %s", editLabel);
    Controller1.Screen.print(" B = Save");
 
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("%.4f", (double)editFloatValue);
 
    if (strncmp(editLabel, "I", 1) == 0){
        Controller1.Screen.print("  UD=%.4f",
                             (double)editFineStep);  
        Controller1.Screen.setCursor(3, 1);
        Controller1.Screen.print("Hold UD=%.3f ",
                             (double)editCoarseStep); 
    }else{
        Controller1.Screen.print("  UD=%.2f",
                             (double)editFineStep);  
        Controller1.Screen.setCursor(3, 1);
        Controller1.Screen.print("Hold UD=%.1f ",
                             (double)editCoarseStep);  
    }
    
}

/// @brief Draw the Screen when Editing a Int Variable (settleTime or endTime)
void PIDTuner::drawEditInt() {
    Controller1.Screen.clearScreen();
 
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Edit %s", editLabel);
    Controller1.Screen.print("   B = Save");
 
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("%d ms", editIntVal);
    
    Controller1.Screen.print("  UD=%dms",
                             editFineStepI);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("Hold UD=%dms",
                              editCoarseStepI);
}

/// @brief Exports the current selected PID profile as one line for Drive.cpp
void PIDTuner::exportCurrentProfile() {
    ParameterSet& p = activeParams();
    const int* distances = activeDistances();

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Exported current");
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("Check terminal");

    if (currentMode == MODE_DRIVE) {
        printf("\nPID(%.4ff, %.4ff, %.4ff, %.4ff, %.1ff, %.1ff),  // %d inches\n",
               p.kP, p.kI, p.kD, p.settleError,
               (float)p.timeToSettle, (float)p.endTime,
               distances[distIndx]);
    } else {
        printf("\nPID(%.4ff, %.4ff, %.4ff, %.4ff, %.1ff, %.1ff),  // %d degrees\n",
               p.kP, p.kI, p.kD, p.settleError,
               (float)p.timeToSettle, (float)p.endTime,
               distances[distIndx]);
    }

    wait(1200, msec);
}

/// @brief Gets the currentMode and drives or turns the robot in the correct direction
void PIDTuner::runTest() {
    applyParamsToChassis();
    
    const int* distances = activeDistances();
    float dist   = (float)distances[distIndx];
    float target = testGoForward ? dist : -dist;
    testGoForward = !testGoForward;
 
    const char* unit = (currentMode == MODE_DRIVE) ? "in" : "deg";
 
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("%s test", modeLabel());
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("Target: %.1f %s", (double)target, unit);
 
    if (currentMode == MODE_DRIVE) {
        if (chassis.getOdomType() != NO_ODOM){
            chassis.driveDistanceWithOdom(target);   
        }else{
            chassis.driveDistance(target);
        }
    } else {
        chassis.turn(target);
    }
 
    chassis.brake();
 
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Done!");
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("Next: %s %.0f %s",
                             testGoForward ? "FWD" : "BWD",
                             (double)dist, unit);
    wait(1200, msec);
}

/// @brief Main loop that runs and keeps the program in the PID Tuner
/// Main controller of all button presses
void PIDTuner::run() {
    bool redraw = true;
    int maxDist;
 
    while (true) {
        BtnSnapshot edge = edgeButtons();
        BtnSnapshot raw  = rawButtons();
        bool changed     = false;
        
 
        switch (currentScreen) {
 
            // ── MAIN ──────────────────────────────────────────────────────
            case SCR_MAIN:
                    if (edge.R2) { runTest(); redraw = true; break; }
                    if (edge.B) { exportCurrentProfile(); redraw = true; break; }

                    // Move field selection — clamped
                    if (edge.Left   && fieldSelector > 0) { fieldSelector--; changed = true; }
                    if (edge.Right && fieldSelector < 5) { fieldSelector++; changed = true; }

                    // Cycle distance — clamped
                    maxDist = activeNumDistances();
                    if (edge.Up && distIndx < maxDist - 1) { distIndx++; changed = true; }
                    if (edge.Down  && distIndx > 0) { distIndx--; changed = true; }

                    // Switch mode
                    if (edge.R1) {
                        currentMode = MODE_DRIVE;
                        if (distIndx >= NUM_DRIVE_DISTANCES)
                            distIndx = NUM_DRIVE_DISTANCES -1;
                        changed = true;
                    }
                    if (edge.L1) {
                        currentMode = MODE_TURN;
                        if (distIndx >= NUM_TURN_DISTANCES)
                            distIndx = NUM_TURN_DISTANCES -1;
                        changed = true;
                    }
                
                    // Open edit screen
                    if (edge.A) { openEditScreen(); redraw = true; break; }
                
                    if (changed) redraw = true;
                    if (redraw)  { drawMain(); redraw = false; }
                    break;
                
            // ── EDIT FLOAT ────────────────────────────────────────────────
            case SCR_EDIT_FLOAT:
                // Increment hold timers for held buttons, reset if released
                holdUp   = raw.Up   ? holdUp   + 1 : 0;
                holdDown = raw.Down ? holdDown + 1 : 0;
 
                if (shouldFire(holdUp)) {
                    if (holdUp < 30){
                        editFloatValue += editFineStep;
                    }else{
                        editFloatValue += editCoarseStep;
                    }
                    if (editFloatValue > editFloatMax) editFloatValue = editFloatMax;
                    changed = true;
                }
                if (shouldFire(holdDown)) {
                    if (holdDown < 30){
                        editFloatValue -= editFineStep;
                    }else{
                        editFloatValue -= editCoarseStep;
                    }
                    if (editFloatValue < editFloatMin) editFloatValue = editFloatMin;
                    changed = true;
                }
 
                if (edge.B) {
                    saveEditScreen();
                    currentScreen = SCR_MAIN;
                    redraw = true;
                    break;
                }
 
                if (changed) redraw = true;
                if (redraw)  { drawEditFloat(); redraw = false; }
                break;
 
            // ── EDIT INT ──────────────────────────────────────────────────
            case SCR_EDIT_INT:
                holdUp   = raw.Up   ? holdUp   + 1 : 0;
                holdDown = raw.Down ? holdDown + 1 : 0;
 
                if (shouldFire(holdUp)) {
                    if (holdUp < 30){
                        editIntVal += editFineStepI;
                    }else{
                        editIntVal += editCoarseStepI;
                    }
                    if (editIntVal > editIntMax) editIntVal = editIntMax;
                    changed = true;
                }
                if (shouldFire(holdDown)) {
                    if (holdDown < 30){
                        editIntVal -= editFineStepI;
                    }else{
                        editIntVal -= editCoarseStepI;
                    }
                    if (editIntVal < editIntMin) editIntVal = editIntMin;
                    changed = true;
                }

 
                if (edge.B) {
                    saveEditScreen();
                    currentScreen = SCR_MAIN;
                    redraw = true;
                    break;
                }
 
                if (changed) redraw = true;
                if (redraw)  { drawEditInt(); redraw = false; }
                break;
        }
 
        wait(40, msec); // ~25 polls per second
    }
}
