#pragma once
#include "Drive.h"

    Drive::Drive(motor_group right_motor_drive, motor_group left_motor_drive, inertial & Gyro, float wheel_diameter, float wheel_ratio) : 
        right_motor_drive(right_motor_drive),
        left_motor_drive(left_motor_drive),
        Gyro(Gyro),
        wheel_diameter(wheel_diameter),
        wheel_ratio(wheel_ratio)
    {}

    //Setters
    void Drive::set_turn_constants(float turn_Kp, float turn_Ki, float turn_Kd, float turn_starti, float turn_settle, float turn_settle_error, float turn_max_voltage)
    {
        this->turn_Kp = turn_Kp;
        this->turn_Ki = turn_Ki;
        this->turn_Kd = turn_Kd;
        this->turn_starti = turn_starti;
        this->turn_settle = turn_settle;
        this->turn_settle_error = turn_settle_error;
        this->turn_max_voltage = turn_max_voltage;
    }

    void Drive::set_drive_constants(float drive_Kp, float drive_Ki, float drive_Kd, float drive_starti, float drive_settle, float drive_settle_error, float drive_max_voltage)
    {
        this->drive_Kp = drive_Kp;
        this->drive_Ki = drive_Ki;
        this->drive_Kd = drive_Kd;
        this->drive_starti = drive_starti;
        this->drive_settle = drive_settle;
        this->drive_settle_error = drive_settle_error;
        this->drive_max_voltage = drive_max_voltage;
    }

    void Drive::set_swing_constants(float swing_Kp, float swing_Ki, float swing_Kd, float swing_starti, float swing_settle, float swing_settle_error, float swing_max_voltage)
    {
        this->swing_Kp = swing_Kp;
        this->swing_Ki = swing_Ki;
        this->swing_Kd = swing_Kd;
        this->swing_starti = swing_starti;
        this->swing_settle = swing_settle;
        this->swing_settle_error = swing_settle_error;
        this->swing_max_voltage = swing_max_voltage;
    }

    void Drive::set_arch_constants(float arch_Kp, float arch_Ki, float arch_Kd, float arch_starti, float arch_settle, float arch_settle_error, float arch_max_voltage)
    {
        this->arch_Kp = arch_Kp;
        this->arch_Ki = arch_Ki;
        this->arch_Kd = arch_Kd;
        this->arch_starti = arch_starti;
        this->arch_settle = arch_settle;
        this->arch_settle_error = arch_settle_error;
        this->arch_max_voltage = arch_max_voltage;
    }

    void Drive::set_heading_constants(float heading_Kp, float heading_Ki, float heading_Kd, float heading_starti, float heading_settle, float heading_settle_error, float heading_max_voltage)
    {
        this->heading_Kp = heading_Kp;
        this->heading_Ki = heading_Ki;
        this->heading_Kd = heading_Kd;
        this->heading_starti = heading_starti;
        this->heading_settle = heading_settle;
        this->heading_settle_error = heading_settle_error;
        this->heading_max_voltage = heading_max_voltage;
    }

    //Returns the left motor drive position
    float Drive::get_left_drive_position()
    {
        return left_motor_drive.position(deg) * (wheel_ratio / 360 * pi() * wheel_diameter);
    }

    //Returns the right motor drive position
    float Drive::get_right_drive_position()
    {
        return right_motor_drive.position(deg) * (wheel_ratio / 360 * pi() * wheel_diameter);
    }

    //Drives with voltage
    void Drive::drive_with_voltage(float left_voltage, float right_voltage)
    {
        left_motor_drive.spin(forward, left_voltage, volt);
        right_motor_drive.spin(forward, right_voltage, volt);
    }

    //Brakes Drive train
    void Drive::brake_drive_train()
    {
        brake_drive_train(true, true);
    }

    //Brakes Specified drive train
    void Drive::brake_drive_train(bool left, bool right)
    {
        if(left)
            left_motor_drive.stop(hold);
        if(right)
            right_motor_drive.stop(hold);
    }

    //Turns to the given angle
    void Drive::turn_to_angle(float angle)
    {
        turn_to_angle(angle, turn_max_voltage);
    }

    //Turns to the given angle and limits the max voltage to turn_max_voltage
    void Drive::turn_to_angle(float angle, float turn_max_voltage)
    {
        //Creates a PID formula with the set constants
        PID turnPID(turn_Kp, turn_Ki, turn_Kd, turn_starti, turn_settle, turn_settle_error);

        //Loops through till the inertial sensor is facing the given angle
        while(!turnPID.isSettled())
        {
            float output = turnPID.compute(reduce_to_180s(angle - Gyro.heading()));
            output = clamp(output, -turn_max_voltage, turn_max_voltage);

            drive_with_voltage(output, -output);

            task::sleep(10);
        }

        current_heading = angle;
        
        brake_drive_train();
    }

    //Turns with the amount of angle given
    void Drive::turn_angle_amount(float angle)
    {
        turn_angle_amount(angle, turn_max_voltage);
    }

    //Turns with the amount of angle given and limits max voltage to turn_max_voltage
    void Drive::turn_angle_amount(float angle, float turn_max_voltage)
    {
        //Creates a PID formula with the set constants
        PID turnPID(turn_Kp, turn_Ki, turn_Kd, turn_starti, turn_settle, turn_settle_error);

        //Loops through till the inertial sensor is facing the given angle
        while(!turnPID.isSettled())
        {
            float output = turnPID.compute(reduce_to_180s(angle - Gyro.rotation()));
            output = clamp(output, -turn_max_voltage, turn_max_voltage);

            drive_with_voltage(output, -output);

            task::sleep(10);
        }

        current_heading = angle;
        
        brake_drive_train();
    }

    //Drives to the given distance
    void Drive::drive_distance(float distance)
    {
        drive_distance(distance, drive_max_voltage, heading_max_voltage);
    }

    //Drives to the given distance and limits the max voltage to drive_max_voltage and limits the heading voltage to heading_max_voltage
    void Drive::drive_distance(float distance, float drive_max_voltage, float heading_max_voltage)
    {
        //Creates the PID formulas with the set constants
        PID drivePID(drive_Kp, drive_Ki, drive_Kd, drive_starti, drive_settle, drive_settle_error);
        PID headingPID(heading_Kp, heading_Ki, heading_Kd, heading_starti, heading_settle, heading_settle_error);

        //Creates the starting position and the current position throughout of the drive trains
        float starting_position = (get_left_drive_position() + get_right_drive_position()) / 2.0;
        float current_position = starting_position;

        //Loops through till the given distance has been reached
        while(!drivePID.isSettled())
        {
            current_position = (get_left_drive_position() + get_right_drive_position()) / 2.0;
            float drive_output = drivePID.compute((distance + starting_position) - current_position);
            float heading_output = headingPID.compute(reduce_to_180s(current_heading - Gyro.heading()));

            drive_output = clamp(drive_output, -drive_max_voltage, drive_max_voltage);
            heading_output = clamp(heading_output, -heading_max_voltage, heading_max_voltage);

            drive_with_voltage(drive_output + heading_output, drive_output - heading_output);
            task::sleep(10);
        }

        brake_drive_train();

    }

    //Swings with left drive
    void Drive::left_swing_to_angle(float angle)
    {
        left_swing_to_angle(angle, swing_max_voltage);
    }

    //Swings with left drive and limits the max voltage to swing_max_voltage
    void Drive::left_swing_to_angle(float angle, float swing_max_voltage)
    {
        PID swingPID(swing_Kp, swing_Ki, swing_Kd, swing_starti, swing_settle, swing_settle_error);

        while(!swingPID.isSettled())
        {
            float output = swingPID.compute(reduce_to_180s(angle - Gyro.heading()));

            output = clamp(output, -swing_max_voltage, swing_max_voltage);

            left_motor_drive.spin(forward, output, volt);
            brake_drive_train(false, true);

            task::sleep(10);
        }

        brake_drive_train();

        current_heading = angle;
    }

    //Swings with right drive
    void Drive::right_swing_to_angle(float angle)
    {
        right_swing_to_angle(angle, swing_max_voltage);
    }

    //Swings with right drive and limits the max voltage to swing_max_voltage
    void Drive::right_swing_to_angle(float angle, float swing_max_voltage)
    {
        PID swingPID(swing_Kp, swing_Ki, swing_Kd, swing_starti, swing_settle, swing_settle_error);

        while(!swingPID.isSettled())
        {
            float output = swingPID.compute(reduce_to_180s(angle - Gyro.heading()));

            output = clamp(output, -swing_max_voltage, swing_max_voltage);

            right_motor_drive.spin(forward, output, volt);
            brake_drive_train(true, false);

            task::sleep(10);
        }

        brake_drive_train();

        current_heading = angle;
    }

    //Drives in an arch leftwards
    void Drive::drive_left_arch(float distance, float angle, float arch_speed)
    {
        drive_left_arch(distance, angle, arch_speed, arch_max_voltage);
    }

    //Drives in an arch leftwards and limits voltage to arch_max_voltage
    void Drive::drive_left_arch(float distance, float angle, float arch_speed, float arch_max_voltage)
    {
        PID left_archPID(arch_Kp, arch_Ki, arch_Kd, arch_starti, arch_settle, arch_settle_error);
        PID right_archPID(arch_Kp, arch_Ki, arch_Kd, arch_starti, arch_settle, arch_settle_error);

        float left_start_position = get_left_drive_position();
        float right_start_position = get_right_drive_position();
        float left_current_position = left_start_position;
        float right_current_position = right_start_position;

        while(!left_archPID.isSettled())
        {
            float left_current_position = get_left_drive_position();
            float right_current_position = get_right_drive_position();

            float left_output = left_archPID.compute(((distance / arch_speed) + left_start_position) - left_current_position);
            float right_output = right_archPID.compute((distance + right_start_position) - right_current_position);

            left_output = clamp(left_output, -arch_max_voltage, arch_max_voltage);
            right_output = clamp(right_output, -arch_max_voltage, arch_max_voltage);

            drive_with_voltage(left_output, right_output);
            task::sleep(10);
        }

        brake_drive_train();

        current_heading = Gyro.heading();
    }

    //Drives in an arch rightwards
    void Drive::drive_right_arch(float distance, float angle, float arch_speed)
    {
        drive_right_arch(distance, angle, arch_speed, arch_max_voltage);
    }

    //Drives in an arch rightwards and limits voltage to arch_max_voltage
    void Drive::drive_right_arch(float distance, float angle, float arch_speed, float arch_max_angle)
    {
        PID left_archPID(arch_Kp, arch_Ki, arch_Kd, arch_starti, arch_settle, arch_settle_error);
        PID right_archPID(arch_Kp, arch_Ki, arch_Kd, arch_starti, arch_settle, arch_settle_error);

        float left_start_position = get_left_drive_position();
        float right_start_position = get_right_drive_position();
        float left_current_position = left_start_position;
        float right_current_position = right_start_position;

        while(!left_archPID.isSettled())
        {
            float left_current_position = get_left_drive_position();
            float right_current_position = get_right_drive_position();

            float left_output = left_archPID.compute(((distance / arch_speed) + left_start_position) - left_current_position);
            float right_output = right_archPID.compute((distance + right_start_position) - right_current_position);

            left_output = clamp(left_output, -arch_max_voltage, arch_max_voltage);
            right_output = clamp(right_output, -arch_max_voltage, arch_max_voltage);

            drive_with_voltage(left_output, right_output);
            task::sleep(10);
        }

        brake_drive_train();

        current_heading = Gyro.heading();
    }

    //Drives distance and runs function during drive
    void Drive::drive_with_function(float distance, void (*func)())
    {
        drive_with_function(distance, func, drive_max_voltage);
    }

    //Drives distance and runs function during drive and limits max voltage to drive_max_voltage
    void Drive::drive_with_function(float distance, void (*func)(), float drive_max_voltage)
    {
        //Creates the PID formulas with the set constants
        PID drivePID(drive_Kp, drive_Ki, drive_Kd, drive_starti, drive_settle, drive_settle_error);
        PID headingPID(heading_Kp, heading_Ki, heading_Kd, heading_starti, heading_settle, heading_settle_error);

        //Creates the starting position and the current position throughout of the drive trains
        float starting_position = (get_left_drive_position() + get_right_drive_position()) / 2.0;
        float current_position = starting_position;

        //Loops through till the given distance has been reached
        while(!drivePID.isSettled())
        {
            current_position = (get_left_drive_position() + get_right_drive_position()) / 2.0;
            float drive_output = drivePID.compute((distance + starting_position) - current_position);
            float heading_output = headingPID.compute(reduce_to_180s(current_heading - Gyro.heading()));

            drive_output = clamp(drive_output, -drive_max_voltage, drive_max_voltage);
            heading_output = clamp(heading_output, -heading_max_voltage, heading_max_voltage);

            drive_with_voltage(drive_output + heading_output, drive_output - heading_output);

            func();

            task::sleep(10);
        }

        brake_drive_train();
    }

    //Turns to angle and runs function during turn
    void Drive::turn_with_function(float angle, void (*func)())
    {
        turn_with_function(angle, func, turn_max_voltage);
    }

    //Turns to angle and runs function during turn and limits max voltage to turn_max_voltage
    void Drive::turn_with_function(float angle, void (*func)(), float turn_max_voltage)
    {
        //Creates a PID formula with the set constants
        PID turnPID(turn_Kp, turn_Ki, turn_Kd, turn_starti, turn_settle, turn_settle_error);

        //Loops through till the inertial sensor is facing the given angle
        while(!turnPID.isSettled())
        {
            float output = turnPID.compute(reduce_to_180s(angle - Gyro.heading()));
            output = clamp(output, -turn_max_voltage, turn_max_voltage);

            drive_with_voltage(output, -output);

            task::sleep(10);
        }

        current_heading = angle;
        
        brake_drive_train();
    }