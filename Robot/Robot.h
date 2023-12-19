#ifndef ROBBOT_H
    #define ROBBOT_H
	
#include <iController.h>
#include <iIOPlatform.h>

class Robot
{
	public:
		Robot(iController* _Controller, iIOPlatform* _IoModule);
	private:
		iController* Controller;	
		iIOPlatform* IoModule;
				
		/*Contoller*/
		unsigned short getButtonState();
		void getJoystickState(int* posX, int* posY);

		/*IoPaltform*/		
		void setGPIOValue(int pin, int value);
		void setPwmDutyCycle(int pwm, int dutyCycle);

		void drive();
		void motorControl(int motor, int speed);
};


#endif