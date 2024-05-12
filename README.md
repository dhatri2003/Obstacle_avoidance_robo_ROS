# Obstacle-Avoidance Robot using rosserial_python, Arduino, and Ultrasonic Sensor

## Description
This project focuses on building an obstacle-avoidance robot using Arduino UNO, Ultrasonic Sensor, and rosserial_python for ROS integration. The robot is designed to navigate autonomously in its environment while avoiding obstacles.

## Components
- Arduino UNO
- HC-SR04 Ultrasonic Sensor
- SG90 Micro Servo Motor
- L289N Motor Driver
- 12V DC Motors
- Li-ion Cells
- Breadboard

## Installation and Setup
1. Install the necessary libraries for Arduino:
   - Servo.h
   - ros.h
   - std_msgs/Int8.h

2. Connect the hardware components as per the provided circuit diagram.

3. Upload the provided Arduino code to the Arduino UNO board.

4. Install rosserial_python for ROS integration.

## Usage
1. Power on the Arduino-powered robot.

2. Ensure that the ROS environment is set up and running.

3. Run the rosserial_python node to establish communication between Arduino and ROS.

4. Monitor the published data using `rostopic echo chatter` to observe the distance readings.

5. Test the robot in an environment with obstacles to observe its obstacle-avoidance behavior.


