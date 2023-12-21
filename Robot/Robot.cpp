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
	if(motor==0 && speed == 0)
	{
		setGPIOValue(23, 0);
		setGPIOValue(24, 0);
		setPwmDutyCycle(0, 0);
	}
	else if(motor==1 && speed == 0)
	{
		setGPIOValue(20, 0);
		setGPIOValue(21, 0);		
		setPwmDutyCycle(1, 0);
	}
	
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
	int speedA=0;
	int speedB=0;
	getJoystickState(&x, &y);
	//but = getButtonState();
	y *= -1;

	if(y>25000)
	{
		speedA=100;
		speedB=100;												
		
		if(x>=8000)
		{
			speedA=100;
			speedB=90;						
		}
		else if(x<-8000)
		{
			speedA=90;
			speedB=100;									
		}
	}
	else if( y>10000 && y<=25000)
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
		else if(x<-15000)
		{
			speedB += 20;
		}					
		else if(x < -10000)
		{
			speedB += 15;
		}	
	
	}
	else// if(y<=10000 && y > -31000)
	{
		if(x<=5000 && x>=-5000)
		{
			speedA=0;
			speedB=0;
		}
		else if(x>25000)
		{
			speedA = 100;
			speedB = 0;			
		}	
		else if(x > 10000)
		{
			speedA = 95;
			speedB=0;						
		}	
		else if(x>5000)
		{
			speedA = 90;			
			speedB=0;									
		} 
		else if(x<-15000)
		{
			speedB = 100;
			speedA=0;				
		}					
		else if(x < -10000)
		{
			speedB = 95;
			speedA=0;							
		}	
		else if(x<-5000)
		{
			speedB= 90;		
			speedA=0;								
		} 		
	}
	//else
	//{
	//	speedA=100;
	//	speedB=100;												
		
	//	if(x>=8000)
	//	{
	//		speedA=100;
	//		speedB=80;						
	//	}
	//	else if(x<-8000)
	//	{
	//		speedA=80;
	//		speedB=100;									
	//	}		
	//	speedB *= -1;	
	//	speedA *= -1;				
	//}
	
	std::cout<<"x:"<<x<<" y:"<<y<<" Speed:"<<speedA <<", "<<speedB;
	printf("  \r");
	fflush(stdout);
	
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
	}
}



#else
#include <unistd.h>
Robot::Robot(iController* _Controller, iIOPlatform* _IoModule)
{
	Controller= _Controller;
	IoModule = _IoModule;

	motorControl(0,100);
	motorControl(1,-100);

	while(1)
	{
		drive();	
	}
}

void motorControl(int motor, int speed)
{
	
}
#endif