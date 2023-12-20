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
	//but = getButtonState();
	printf("  \r");
	std::cout<<"x:"<<x<<" y:"<<y<<" ";
	fflush(stdout);
	y *= -1;
	int speedA, speedB;
	if(y>25000)
	{
		if(x<5000 && -x>5000)
		{
			speedA=100;
			speedB=100;			
		}
		else if(x>=500)
		{
			speedA=100;
			speedB=90;						
		}
		else if(x<-500)
		{
			speedA=90;
			speedB=100;									
		}
	}
	else if( y>2500 && y<=25000)
	{
		speedA= 80;
		speedB= 80;	
		if(x>15000)
		{
			speedA += 20;
		}	
		else if(x > 10000)
		{
			speedA += 15;
		}	
		else if(x>5000)
		{
			speedA += 5;			
		} 
		else if(x<-15000)
		{
			speedB += 20;
		}					
		else if(x < -10000)
		{
			speedB += 15;
		}	
		else if(x<-5000)
		{
			speedB += 5;			
		} 		
	}
	else if (y<=2500 && y>=-2500)
	{
		if(x<=2500 && x>=-2500)
		{
			speedA=0;
			speedB=0;
		}
		else if(x>15000)
		{
			speedA = 90;
		}	
		else if(x > 10000)
		{
			speedA = 85;
		}	
		else if(x>5000)
		{
			speedA = 80;			
		} 
		else if(x<-15000)
		{
			speedB = 90;
		}					
		else if(x < -10000)
		{
			speedB = 85;
		}	
		else if(x<-5000)
		{
			speedB= 80;			
		} 		
	}
	
	
	motorControl(0,speedA);
	motorControl(1,speedB);				
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
	}
}

void motorControl(int motor, int speed)
{
	
}
#endif