#ifndef DRIVE_HPP
#define DRIVE_HPP

#include <Arduino.h>
#include "motor.hpp"

class Drive
{
public:
    Drive(Motor &lf, Motor &rf, Motor &lr, Motor &rr);

    void forward(int speed);
    void backward(int speed);
    void turnLeft(int speed);
    void turnRight(int speed);
    void stop();

private:
    Motor &leftFront;
    Motor &rightFront;
    Motor &leftRear;
    Motor &rightRear;
};

#endif