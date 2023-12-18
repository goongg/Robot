#include "Robot.h"


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
	getJoystickState(&x, &y);
	
	int powerX;
	int powerY;
	
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
Robot::Robot(iController* _Controller, iIOPlatform* _IoModule)
{
	Controller= _Controller;
	IoModule = _IoModule;
	
	while(1)
	{
		drive();	
		ussleep(1000);
	}
}

void motorControl(int motor, int speed)
{
	
}
#endif