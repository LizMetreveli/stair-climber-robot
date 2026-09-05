#ifndef MANIPULATOR_HPP
#define MANIPULATOR_HPP

#include <Arduino.h>
#include <Servo.h>

//==================================================
// Servo Objects
//==================================================

extern Servo base;
extern Servo shoulder;
extern Servo elbow;
extern Servo wrist;

//==================================================
// Functions
//==================================================

void manipulatorBegin();

void manipulatorCommand(char cmd);

void home();

void printPose();

#endif