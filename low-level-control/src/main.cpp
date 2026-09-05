#include <Arduino.h>
#include <SCServo.h>

#include "servo.hpp"
#include "motor.hpp"
#include "drive.hpp"
#include "manipulator.hpp"

//==================================================
// Front Driver
//==================================================

Motor frontLeft(PA0, PB0, PA1);
Motor frontRight(PC1, PC0, PA4);

//==================================================
// Rear Driver
//==================================================

Motor backLeft(PB11, PB12, PB14);
Motor backRight(PA7, PB6, PB13);

//==================================================
// Robot Drive
//==================================================

Drive robot(frontLeft, frontRight, backLeft, backRight);

bool enabled = false;

const int SPEED = 255;


const unsigned long DRIVE_TIMEOUT_MS = 200;

unsigned long lastDriveCommandTime = 0;
bool robotMoving = false;

//==================================================
// Bus Servos
//==================================================

HardwareSerial ServoSerial(PC9, PC8);

SMS_STS sts;

ChassisServo chassis(&sts, 1, 2);

//==================================================

void setup()
{
    Serial.begin(115200);

    ServoSerial.begin(1000000);

    sts.pSerial = &ServoSerial;

    chassis.begin();

    manipulatorBegin();

    frontLeft.begin();
    frontRight.begin();
    backLeft.begin();
    backRight.begin();

    robot.stop();

    Serial.println();
    Serial.println("========== ROBOT READY ==========");
    Serial.println("X : Enable/Disable motors");
    Serial.println("Hold WASD : Drive");
    Serial.println("Q : Stop");
    Serial.println("R/F : Chassis");
    Serial.println("E : Toggle Torque");
    Serial.println();
    Serial.println("Manipulator:");
    Serial.println("U/J : Base");
    Serial.println("I/K : Shoulder");
    Serial.println("O/L : Elbow");
    Serial.println("Y/H : Wrist");
    Serial.println("N : Home");
    Serial.println("P : Print Pose");
    Serial.println("1-5 Save");
    Serial.println("6-0 Recall");
    Serial.println("===============================");
}

void loop()
{
    while (Serial.available() > 0)
    {
        char cmd = toupper(Serial.read());

        switch (cmd)
        {
            case 'X':
                enabled = !enabled;

                if (enabled)
                {
                    Serial.println("Motors ENABLED");
                }
                else
                {
                    robot.stop();
                    robotMoving = false;
                    Serial.println("Motors DISABLED");
                }
                break;

            case 'W':
                if (enabled)
                {
                    robot.forward(SPEED);

                    lastDriveCommandTime = millis();
                    robotMoving = true;
                }
                break;

            case 'S':
                if (enabled)
                {
                    robot.backward(SPEED);

                    lastDriveCommandTime = millis();
                    robotMoving = true;
                }
                break;

            case 'A':
                if (enabled)
                {
                    robot.turnLeft(SPEED);

                    lastDriveCommandTime = millis();
                    robotMoving = true;
                }
                break;

            case 'D':
                if (enabled)
                {
                    robot.turnRight(SPEED);

                    lastDriveCommandTime = millis();
                    robotMoving = true;
                }
                break;

            case 'Q':
                robot.stop();
                robotMoving = false;

                Serial.println("Stop");
                break;

            case 'R':
                chassis.raise();

                Serial.print("Position = ");
                Serial.println(chassis.getPosition());
                break;

            case 'F':
                chassis.lower();

                Serial.print("Position = ");
                Serial.println(chassis.getPosition());
                break;

            case 'E':
                chassis.toggleTorque();

                Serial.print("Position = ");
                Serial.println(chassis.getPosition());

                if (chassis.torqueEnabled())
                {
                    Serial.println("Torque ON");
                }
                else
                {
                    Serial.println("Torque OFF");
                }

                break;

            default:
                manipulatorCommand(cmd);
                break;
        }
    }

    // Automatically stop when WASD commands stop arriving.
    if (
        enabled &&
        robotMoving &&
        millis() - lastDriveCommandTime >= DRIVE_TIMEOUT_MS
    )
    {
        robot.stop();
        robotMoving = false;
    }
}