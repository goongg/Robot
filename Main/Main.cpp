#include <iostream>
#include "Robot.h"

#include "../Controller/Src/GamePad.h"
#include "../IOPlatform/Src/RaspSysfs.h"

int main()
{

	std::cout <<"Start Robot System\n";
	GamePad _8bitdo;
	RaspSysfs raspberyPi4B;
	
	Robot Robot(&_8bitdo, &raspberyPi4B);
	
	return 0;
}