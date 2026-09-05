# ROS2 Stair-Climbing Mobile Robot

A tracked mobile robot designed and built as an original solution for an advanced robotics course. The robot combines an articulated tracked chassis, a multi-DOF robotic manipulator, embedded motor control, and ROS2-based software to complete mobility and object-manipulation tasks.

This was a **collaborative engineering project**, with responsibilities divided between chassis design, manipulator design, and software/electronics development and integration.

## Project Overview

The robot was designed from the ground up to navigate a challenging course while performing both mobility and manipulation tasks.

The system consists of:

* Tracked mobile platform driven by four DC motors
* Articulated chassis for navigating obstacles and changes in terrain
* Multi-DOF robotic manipulator
* STM32-based low-level motor and actuator control
* Raspberry Pi 4 running ROS2
* Camera-based visual sensing
* ROS2 nodes for camera streaming and visual processing
* Keyboard-based remote control and system coordination

## Hardware

### Computing & Control

* **Raspberry Pi 4** — ROS2 host and high-level processing
* **STM32 Nucleo-F091RC** — embedded motor and actuator control

### Drivetrain

* **4× JGA25-371 DC geared motors**
* **2× L298N dual H-bridge motor drivers**
* Rubber track assemblies
* Custom articulated chassis

### Chassis Articulation

* **Feetech STS3215-C001 servo**
* Hinged chassis mechanism designed for obstacle traversal

### Robotic Manipulator

* **3× MG90S micro servos**
* High-torque servo for base rotation
* Custom arm and gripper mechanism

### Vision

* Camera connected to the Raspberry Pi
* ROS2 camera publisher
* Computer-vision processing for challenge-specific visual tasks

### Power

* **11.1 V LiPo battery** for drivetrain and actuators
* Separate power supply for the Raspberry Pi

## Software

The software stack was developed around **ROS2**, with the Raspberry Pi handling high-level communication and vision processing and the STM32 handling low-level hardware control.

Software developed for the project includes:

* ROS2 camera publishing
* Keyboard-based robot control
* DC motor control
* Chassis articulation control
* Manipulator control
* Camera stream management
* Computer-vision processing
* Traffic-light detection using YOLOv8n
* QR-code detection and processing
* Communication between the Raspberry Pi and embedded control hardware

## Original Design

The robot is an **original design developed specifically for the Advanced Robotics Challenge**, rather than an implementation of an existing robotic platform.

The team developed the mechanical architecture around the requirements of the challenge, including the tracked drivetrain, articulated chassis, and manipulator configuration. The electronics and software were then developed and integrated around the mechanical platform to create a complete robotic system.

Design decisions were iteratively tested and modified throughout development based on the robot's performance on physical obstacles and challenge tasks.

## Team & Contributions

This project was completed collaboratively by a three-person engineering team.

### Elizaveti Metreveli — Software, Electronics & System Integration

* Developed software and control code
* Implemented ROS2 functionality
* Programmed embedded motor and actuator control
* Developed camera and computer-vision functionality
* Integrated the Raspberry Pi and STM32 control systems
* Integrated electronics with the mechanical subsystems
  
### Pedro Yudi Watanabe — Chassis & Mechanical Design

* Designed and developed the tracked chassis
* Developed the articulated chassis mechanism
* Mechanical fabrication and assembly
* Chassis testing and iterative improvements

### Anu-Ujin Enkhbayar — Manipulator Design

* Designed and developed the robotic manipulator
* Developed the arm and gripper mechanism
* Mechanical fabrication and assembly
* Manipulator testing and iterative improvements

### Patipat Wiriyakijja - Fabrication & Testing
Contributed to mechanical fabrication and assembly
Participated in system testing and troubleshooting
Supported iterative improvements during robot development
Contributed to overall project integration and development

All team members contributed to the overall robot concept, integration, testing, and development.

## Technologies

`ROS2` · `Python` · `C/C++` · `STM32` · `Raspberry Pi` · `Computer Vision` · `YOLOv8` · `Embedded Systems` · `Robotics` · `Motor Control`

## Media

## Media


![Robot side view](media/robot%20side.jpg)

![Robot front view](media/robot%20front.jpg)

## Acknowledgements

Developed as part of the Advanced Robotics Challenge at the **Kyoto University of Advanced Science, Faculty of Engineering**.
