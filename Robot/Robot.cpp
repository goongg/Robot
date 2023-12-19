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

void Robot::motorControl(int motor, int speed)
{
	if(motor==0 && speed > 0)
	{
		setGPIOValue(23, 1);
		setGPIOValue(24, 0);
		setPwmDutyCycle(0, speed);
	}
	else if(motor==0 && speed < 0)
	{
		setGPIOValue(23, 0);
		setGPIOValue(24, 1);
		setPwmDutyCycle(0, speed*(-1));
	}	
	else if(motor==1 && speed > 0)
	{
		setGPIOValue(20, 1);
		setGPIOValue(21, 0);
		setPwmDutyCycle(1, speed);
	}
	else if(motor==1 && speed < 0)
	{
		setGPIOValue(20, 0);
		setGPIOValue(21, 1);
		setPwmDutyCycle(1, speed*(-1));
	}		
}

void Robot::drive()
{
	int x, y;
	unsigned short but;
	getJoystickState(&x, &y);
	std::cout<<"\n"<<x<<" "<<y<<"\n";
	int powerX;
	int powerY;
	but = getButtonState();
	std::cout<<"\n"<<but<<"\n";
	fflush(stdout);
	
	if(x>=32000)
	{
		motorControl(0,100);
		motorControl(1,100);		
	}	
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