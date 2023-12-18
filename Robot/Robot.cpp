#include "Robot.h"
#include <iostream>

unsigned short Robot::getButtonState()
{
	return Controller->getButtonState();
}
void Robot::getJoystickState(int* posX, int* posY)
{
	Controller->getJoystickState(posX, posY);
}
void Robot::setGPIOValue(int pin, int value)
{
	IoModule->setGPIOValue(pin, value);
}
void Robot::setPwmDutyCycle(int pwm, int dutyCycle)
{
	IoModule->setPwmDutyCycle(pwm, dutyCycle);
}

void Robot::drive()
{
	int x, y;
	unsigned short but;
	getJoystickState(&x, &y);
	//std::cout<<"\n"<<x<<" "<<y<<"\n";
	int powerX;
	int powerY;
	but = getButtonState();
	//std::cout<<"\n"<<but<<"\n";
	if(x>=32767)
	{
//		setGPIOValue();
	}
	
	
//	if(x>=)
}

#ifdef _WIN32 // Windows
    #include <Windows.h>
Robot::Robot(iController* _Controller, iIOPlatform* _IoModule)
{
	Controller= _Controller;
	IoModule = _IoModule;
	
	while(1)
	{
		drive();	
		Sleep(1);
	}
}

void motorControl(int motor, int speed)
{
		
}
#else
#include <unistd.h>
Robot::Robot(iController* _Controller, iIOPlatform* _IoModule)
{
	Controller= _Controller;
	IoModule = _IoModule;
	
	while(1)
	{
		drive();	
		usleep(1000);
	}
}

void motorControl(int motor, int speed)
{
	
}
#endif