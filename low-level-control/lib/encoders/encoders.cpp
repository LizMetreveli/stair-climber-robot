#include "encoders.hpp"

Encoder::Encoder(uint8_t pinA, uint8_t pinB)
{
    _pinA = pinA;
    _pinB = pinB;
    count = 0;
}

void Encoder::begin()
{
    pinMode(_pinA, INPUT_PULLUP);
    pinMode(_pinB, INPUT_PULLUP);

    lastA = digitalRead(_pinA);
}

void Encoder::update()
{
    bool A = digitalRead(_pinA);

    if (A != lastA)
    {
        if (digitalRead(_pinB) != A)
            count--;
        else
            count++;

        lastA = A;
    }
}

long Encoder::getCount()
{
    return count;
}

void Encoder::reset()
{
    count = 0;
}