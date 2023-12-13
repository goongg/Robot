#include <stdio.h>
#include <Motor.h>


Motor::Motor()
{}

Motor::~Motor()
{}
Motor::Motor(void (*_setPinVal)(int,int), void (*_setPwmDutyCycle)(int,int))
{

}
void Motor::move(int direct[8], int Speed)
{
    return;
};

