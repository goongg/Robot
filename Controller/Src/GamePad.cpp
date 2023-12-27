#include "GamePad.h"


#ifdef _WIN32 // Windows
GamePad::GamePad(){
    if (XInputGetState(0, nullptr) != ERROR_SUCCESS) {
    }
}

GamePad::~GamePad(){
}

unsigned short GamePad::getButtonState()
{
    for(int i =0; i<10; i++)
    {
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        if (XInputGetState(0, &state) == ERROR_SUCCESS) {
            return state.Gamepad.wButtons;
        }
    }    

    return 0;
}

void GamePad::getJoystickState(int* posX, int* posY) {

    for(int i =0; i<10; i++)
    {
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        if (XInputGetState(0, &state) == ERROR_SUCCESS) {
            std::cout << "Left Joystick X: " << state.Gamepad.sThumbLX << std::endl;
            std::cout << "Left Joystick y: " << state.Gamepad.sThumbLY << std::endl;
            *posX = state.Gamepad.sThumbLX;
            *posY = state.Gamepad.sThumbLY; 
            return;
        }
    }
}
#else


#define JOY_DEV "/dev/input/js0"
#include <unistd.h>

GamePad::GamePad() {
	
	num_of_axis=0;
	num_of_buttons=0;
		
	while( ( joy_fd = open( JOY_DEV , O_RDONLY))  == -1){
		printf( "Couldn't open joystick\n" );
		usleep(100000);
	}
	
	printf( "\n==Success open joystick!==\n" );
	
	ioctl( joy_fd, JSIOCGAXES, &num_of_axis );
	ioctl( joy_fd, JSIOCGBUTTONS, &num_of_buttons );
	ioctl( joy_fd, JSIOCGNAME(80), &name_of_joystick );

	axis = (int *) calloc( num_of_axis, sizeof( int ) );
	button = (char *) calloc( num_of_buttons, sizeof( char ) );

	if(num_of_axis[0]=='N')
	{
		num_of_axis=0;
		num_of_buttons=0;
			
		while( ( joy_fd = open( JOY_DEV , O_RDONLY))  == -1){
			printf( "Couldn't open joystick\n" );
			usleep(100000);
		}
		
		printf( "\n==Success open joystick!==\n" );
		
		ioctl( joy_fd, JSIOCGAXES, &num_of_axis );
		ioctl( joy_fd, JSIOCGBUTTONS, &num_of_buttons );
		ioctl( joy_fd, JSIOCGNAME(80), &name_of_joystick );
	
		axis = (int *) calloc( num_of_axis, sizeof( int ) );
		button = (char *) calloc( num_of_buttons, sizeof( char ) );
			
		printf("Joystick detected: %s\n\t%d axis\n\t%d buttons\n\n"
			, name_of_joystick
			, num_of_axis
			, num_of_buttons );		
	}
	else
	{
		printf("Joystick detected: %s\n\t%d axis\n\t%d buttons\n\n"
			, name_of_joystick
			, num_of_axis
			, num_of_buttons );		
	}
}

GamePad::~GamePad() {
    if (joy_fd != -1) {
        close(joy_fd);
    }
}

unsigned short GamePad::getButtonState() 
{
    unsigned short ret=0;
    //for(int i =0; i<10; i++)
    //{
		read(joy_fd, &js, sizeof(struct js_event));
		
        switch (js.type & ~JS_EVENT_INIT)
		{
			case JS_EVENT_BUTTON:
				button [ js.number ] = js.value;
				break;
        }
//	    printf("  \r");
    	for( x=0 ; x<4 ; ++x )
    	{
//        	printf("B%d: %d  ", x, button[x] );
//			fflush(stdout);
	        ret |= button[x]&(0x01) << (x);
    	}		
    //}


    return ret;
}

void GamePad::getJoystickState(int* posX, int* posY) {

    //for(int i =0; i<10; i++)
    //{
		read(joy_fd, &js, sizeof(struct js_event));
		
        switch (js.type & ~JS_EVENT_INIT)
		{
			case JS_EVENT_AXIS:
				axis   [ js.number ] = js.value;
			break;
        }
		/* print the results */
//		printf( "X: %6d  Y: %6d  ", axis[0], axis[1] );
//    	printf("  \r");
		fflush(stdout);		
		*posX = axis[0];
		*posY = axis[1];
    //}

    return;
}

#endif
