#include "servo.hpp"

ChassisServo::ChassisServo(SMS_STS *servoBus,
                           uint8_t leftID,
                           uint8_t rightID)
{
    sts = servoBus;

    leftServo = leftID;
    rightServo = rightID;

    currentPosition = 1120;
    torque = true;
}

void ChassisServo::begin()
{
    moveTo(currentPosition);
}

void ChassisServo::moveTo(int position)
{
    if(position < MIN_POS)
        position = MIN_POS;

    if(position > MAX_POS)
        position = MAX_POS;

    currentPosition = position;

    uint8_t ids[2] = { leftServo, rightServo };
    int16_t positions[2] = { currentPosition, currentPosition };
    uint16_t speeds[2] = { SPEED, SPEED };
    uint8_t accs[2] = { ACC, ACC };

    sts->SyncWritePosEx(ids, 2, positions, speeds, accs);
}

void ChassisServo::raise()
{
    moveTo(currentPosition + STEP);
}

void ChassisServo::lower()
{
    moveTo(currentPosition - STEP);
}

void ChassisServo::torqueOn()
{
    torque = true;

    sts->EnableTorque(leftServo,1);
    sts->EnableTorque(rightServo,1);
}

void ChassisServo::torqueOff()
{
    torque = false;

    sts->EnableTorque(leftServo,0);
    sts->EnableTorque(rightServo,0);
}

void ChassisServo::toggleTorque()
{
    if(torque)
        torqueOff();
    else
        torqueOn();
}

int ChassisServo::getPosition() const
{
    return currentPosition;
}

bool ChassisServo::torqueEnabled() const
{
    return torque;
}