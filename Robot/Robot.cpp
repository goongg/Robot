#include "Robot.h"

Robot::Robot(iController* _Controller, iIOPlatform* _IoModule)
{
	Controller= _Controller;
	IoModule = _IoModule;
	
	while(1)
	{
		drive();
		
		Sleep()	
	}
	
}


unsigned short Robot::getButtonState()
{}
void Robot::getJoystickState(int* posX, int* posY)
{}
void Robot::setGPIOValue(int pin, int value)
{}
void Robot::setPwmDutyCycle(int pwm, int dutyCycle)
{}
void Robot::drive()
{}