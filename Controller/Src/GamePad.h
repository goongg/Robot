#ifndef GAMEPAD_H
    #define GAMEPAD_H
	
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <iController.h>

#ifdef _WIN32 // Windows
    #include <Windows.h>
    #include <xinput.h>
#else
    #include <fcntl.h>
    #include <unistd.h>
    #include <linux/joystick.h>
#endif
	
class GamePad : public iController
{
	public:
	    GamePad();
	    ~GamePad();
	    unsigned short getButtonState() override;
	    void getJoystickState(int* posX, int* posY) override;    
	
	private:
	#ifdef _WIN32 // Windows
	    XINPUT_STATE state; 
	#else
	    int fd;    
	#endif
};


#endif
	