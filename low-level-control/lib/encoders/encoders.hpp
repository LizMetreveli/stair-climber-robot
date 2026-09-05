#ifndef ENCODERS_HPP
#define ENCODERS_HPP

#include <Arduino.h>

class Encoder
{
public:
    Encoder(uint8_t pinA, uint8_t pinB);

    void begin();

    void update();

    long getCount();

    void reset();

private:
    uint8_t _pinA;
    uint8_t _pinB;

    volatile long count;
    bool lastA;
};

#endif