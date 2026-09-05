#ifndef SERVO_HPP
#define SERVO_HPP

#include <Arduino.h>
#include <SCServo.h>

class ChassisServo
{
public:
    ChassisServo(SMS_STS *servoBus,
                 uint8_t leftID,
                 uint8_t rightID);

    void begin();

    void raise();
    void lower();

    void torqueOn();
    void torqueOff();
    void toggleTorque();

    void moveTo(int position);

    int getPosition() const;
    bool torqueEnabled() const;

private:
    SMS_STS *sts;

    uint8_t leftServo;
    uint8_t rightServo;

    int currentPosition;

    bool torque;

    static constexpr int MIN_POS = 400;     
    static constexpr int MAX_POS = 2000;    
    static constexpr int STEP     = 80;

    static constexpr int SPEED = 1500;
    static constexpr int ACC   = 50;
};

#endif