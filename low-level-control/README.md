# Low-Level Control

Embedded control software for the STM32 Nucleo-F091RC used in the ROS2 tracked mobile robot.

The controller provides low-level control of the robot's drivetrain, servo-actuated chassis, and robotic manipulator. It was developed using **PlatformIO** with the **Arduino framework** and interfaces with the Raspberry Pi running the higher-level ROS2 system.

## Features

* Four-motor drivetrain control
* Servo-actuated chassis control
* Robotic manipulator control
* Serial communication with the Raspberry Pi
* Modular motor, servo, drive, and manipulator control functions
* Encoder and PID control modules prepared for future closed-loop control

## Hardware

* **STM32 Nucleo-F091RC**
* **4× JGA25-371 DC geared motors**
* **2× L298N dual H-bridge motor drivers**
* **Feetech STS3215-C001 servo**
* **MG90S servos**
* High-torque manipulator base servo

## Prototype Implementation

The final prototype used **open-loop motor control**. Although encoder and PID functionality was developed as part of the software structure, these features were **not implemented in the final physical prototype**.

The existing encoder and PID modules provide a foundation for future development of closed-loop velocity or position control.

## Development Environment

* PlatformIO
* Arduino framework
* C/C++
* STM32 Nucleo-F091RC

## Project Context

This software forms the low-level control layer of the **ROS2 Stair-Climbing Mobile Robot** developed for the Advanced Robotics Challenge.

Higher-level ROS2 control and computer-vision functionality runs separately on a Raspberry Pi 4.
