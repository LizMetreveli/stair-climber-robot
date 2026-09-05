#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor
{
private:
    // Add your motor control pins here
    // Example:
    // uint8_t in1Pin;
    // uint8_t in2Pin;
    // uint8_t pwmPin;   // You'll need this later if ENA/ENB are connected
    uint8_t in1Pin;
    uint8_t in2Pin; 
    uint8_t pwmPin; 



public:
    // Constructor
    Motor(uint8_t in1Pin, uint8_t  in2Pin, uint8_t pwm); 


    // Initialize hardware
    void begin();


    // Basic motion
    void forward();
    void backward();
    void stop();

    // Combined command
    void setSpeed(int speed);

    // Optional helper
    int getSpeed();

private:

    // Store the current commanded speed
    int currentSpeed;
};

#endif