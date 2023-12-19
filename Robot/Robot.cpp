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
		setPwmDutyCycle(0, speed*10000);
	}
	else if(motor==0 && speed < 0)
	{
		setGPIOValue(23, 0);
		setGPIOValue(24, 1);
		setPwmDutyCycle(0, speed*(-10000));
	}	
	else if(motor==1 && speed > 0)
	{
		setGPIOValue(20, 1);
		setGPIOValue(21, 0);
		setPwmDutyCycle(1, speed*10000);
	}
	else if(motor==1 && speed < 0)
	{
		setGPIOValue(20, 0);
		setGPIOValue(21, 1);
		setPwmDutyCycle(1, speed*(-10000));
	}		
}

	int x, y;
	unsigned short but;

void Robot::drive()
{
	getJoystickState(&x, &y);
	int powerX;
	int powerY;
	but = getButtonState();
	printf("  \r");
	std::cout<<"\n x:"<<x<<" y:"<<y<<but<<"\n";
	fflush(stdout);
	
	if(y<-32000)
	{
		std::cout<<"run 100";
		motorControl(0,100);
		motorControl(1,100);		
	}
	else if(y<-20000)
	{
		std::cout<<"run 90";		
		motorControl(0,90);
		motorControl(1,90);				
	}
	else if(y<-10000)
	{
		std::cout<<"run 80";
		motorControl(0,80);
		motorControl(1,80);		
	}
	else if(y<-5000)
	{
		std::cout<<"run 70";
		motorControl(0,70);
		motorControl(1,70);				
	}

	if(x==0 && y ==0)
	{
		std::cout<<"stop";
		motorControl(0,0);
		motorControl(1,0);				
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
//		Sleep(1);
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
		usleep(10);
	}
}

void motorControl(int motor, int speed)
{
	
}
#endif