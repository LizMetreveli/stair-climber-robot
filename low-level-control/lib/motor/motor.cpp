#include "motor.hpp" 

Motor:: Motor(uint8_t in1, uint8_t in2, uint8_t pwm){ 
    in1Pin =in1; 
    in2Pin = in2; 
    pwmPin = pwm; 
}

void Motor:: begin(){ 

    pinMode(in1Pin, OUTPUT); 
    pinMode(in2Pin, OUTPUT); 
    pinMode(pwmPin, OUTPUT);

    stop(); 
}

void Motor:: forward() { 
    
    digitalWrite(in1Pin, HIGH); 
    digitalWrite(in2Pin, LOW); 
}

void Motor:: backward() { 
    digitalWrite(in1Pin, LOW); 
    digitalWrite(in2Pin, HIGH);
} 

void Motor:: stop(){ 
    digitalWrite(in1Pin, LOW); 
    digitalWrite(in2Pin, LOW); 
    analogWrite(pwmPin, 0);
}

int Motor::getSpeed()
{
    return currentSpeed;
}

void Motor::setSpeed(int speed)
{
    speed = constrain(speed, -255, 255);
    currentSpeed = speed;

    if (speed > 0)
    {
        forward();
        analogWrite(pwmPin, speed);
    }
    else if (speed < 0)
    {
        backward();
        analogWrite(pwmPin, -speed);
    }
    else
    {
        stop();
    }
}