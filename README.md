# ARC_Template

## Project Overview

This project is designed to create, program, and control a VEX Robotics robot for [specific purpose, e.g., a competitive challenge, autonomous task, or custom exploration]. The robot integrates a range of sensors, actuators, and control systems to perform various actions with precision and efficiency.

## Features

- **Autonomous Mode**: Completes tasks automatically based on pre-programmed logic.
- **Remote Control Mode**: Allows manual control for testing and competition purposes.
- **Sensor Integration**: Utilizes sensors (e.g., ultrasonic, gyro, color) to adapt to the environment.
- **Modular Code Structure**: Easy to update and expand for new challenges or added functionality.

## Technologies Used

- **VEX V5 Robotics System**: Hardware and motor components
- **VEX Coding Studio / VEXcode V5**: For programming and code deployment
- **Programming Language**: C++ for high-performance control and modularity

## Getting Started

### Prerequisites

- **VEX V5 Robotics System**: including VEX V5 Brain, motors, sensors, and controller.
- **Development Environment**: [VEXcode V5](https://www.vexrobotics.com/vexcode) (recommended) or VEX Coding Studio.
- **C++ Knowledge**: Familiarity with C++ is helpful for customizing and extending the code.

### Setup

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/Cobyashi/ARC_Template
   cd ARC_TEMPLATE
   ```
2. **Open Project in VEXcode**:
   - Launch VEXcode V5 and open the project directory.
3. **Configure Hardware**:
   - Set up motors, sensors, and other components on the robot, as detailed in the [Hardware Configuration](#hardware-configuration) section.
4. **Upload Code to the V5 Brain**:
   - Connect the V5 Brain to your computer via USB and upload the code from VEXcode.

## Hardware Configuration

- **Motors**: Describe each motor and its function, including port assignments.
- **Sensors**: List sensors used (e.g., ultrasonic sensor for distance, gyro for orientation) and their ports.
- **Controller**: Mapping of control buttons for manual operation.

## Code Structure

The code is organized into several modules:

- **main.cpp**: Entry point; initializes and controls the main program flow.
- **PID.cpp**: Functions for controlling the motors, including drive and actuator functions.
- **Sensors.cpp**: Functions for handling sensor input and data processing.
- **robot-config**: Code specifically for autonomous routines and behaviors.
- **Drive.cpp**: Handles manual control and maps controller buttons to actions.

### Key Functions

- `driveForward(int distance)`: Moves the robot forward by a specified distance.
- `turn(int angle)`: Turns the robot by a specified angle using the gyro sensor.
- `pickUpObject()`: Controls the robotic arm to pick up objects.

## Usage

### Running Autonomous Mode

1. Deploy the code to the robot.
2. Switch to **Autonomous Mode** on the V5 Brain.
3. Press the start button to initiate the pre-programmed tasks.

### Running Manual Mode

1. Deploy the code to the robot.
2. Switch to **Driver Control Mode**.
3. Use the V5 controller to navigate and control the robot.

## Troubleshooting

- **Connection Issues**: Ensure the USB connection to the V5 Brain is secure. Check VEXcode settings if the device is not detected.
- **Motor Malfunctions**: Verify motor port assignments in the code match the physical setup.
- **Sensor Errors**: Test individual sensors in VEXcode to ensure they are properly calibrated and connected.

## Roadmap

- [ ] Configure PIDs.
- [ ] Develop Odometry function for motor control.
- [ ] Add advanced pathfinding in autonomous mode.
- [ ] Integrate vision sensor for object detection.
- [ ] Implement enhanced error handling and diagnostics.

## Contributing

Contributions are welcome! Please fork the repository and create a pull request for any bug fixes, enhancements, or new features.

## License

This project is licensed under the MIT License – see the [LICENSE](LICENSE) file for details.

