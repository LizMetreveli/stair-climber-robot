#include "drive.hpp"

Drive::Drive(Motor &lf, Motor &rf, Motor &lr, Motor &rr)
    : leftFront(lf),
      rightFront(rf),
      leftRear(lr),
      rightRear(rr)
{
}

void Drive::forward(int speed)
{
    leftFront.setSpeed(speed);
    rightFront.setSpeed(speed);
    leftRear.setSpeed(speed);
    rightRear.setSpeed(speed);
}

void Drive::backward(int speed)
{
    leftFront.setSpeed(-speed);
    rightFront.setSpeed(-speed);
    leftRear.setSpeed(-speed);
    rightRear.setSpeed(-speed);
}

void Drive::turnLeft(int speed)
{
    leftFront.setSpeed(-speed);
    leftRear.setSpeed(-speed);

    rightFront.setSpeed(speed);
    rightRear.setSpeed(speed);
}

void Drive::turnRight(int speed)
{
    leftFront.setSpeed(speed);
    leftRear.setSpeed(speed);

    rightFront.setSpeed(-speed);
    rightRear.setSpeed(-speed);
}

void Drive::stop()
{
    leftFront.stop();
    rightFront.stop();
    leftRear.stop();
    rightRear.stop();
}