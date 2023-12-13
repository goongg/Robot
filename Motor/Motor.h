#ifndef MOTOR_H
    #define MOTOR_H

class Motor
{
    public:
        Motor();
        Motor(void (*_setPinVal)(int,int), void (*_setPwmDutyCycle)(int,int));
        ~Motor();
        void move(int direct[8], int Speed);
        void *setPinValue(int pin, int value);
        void *setPwmDutyCycle(int pwm, int dutyCycle);
};

 #endif