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
GamePad::GamePad() {
    fd = open("/dev/input/js0", O_RDONLY);
    if (fd == -1) {
        std::cerr << "Unable to open joystick device." << std::endl;
        // Handle error
    }
}

GamePad::~GamePad() {
    if (fd != -1) {
        close(fd);
    }
}

unsigned short GamePad::getButtonState() {
    js_event js;
    ssize_t bytesRead;

    bytesRead = read(fd, &js, sizeof(js_event));
    if (bytesRead == -1) {
        std::cerr << "Error reading joystick input." << std::endl;
    }

    if ((js.type & JS_EVENT_BUTTON) && js.value == 1) {
        return (unsigned short)(1 << js.number); 
    }

    return  (unsigned short)0;
}

void GamePad::getJoystickState(int* posX, int* posY) {
    js_event js;
    ssize_t bytesRead;

    bytesRead = read(fd, &js, sizeof(js_event));
    if (bytesRead == -1) {
        std::cerr << "Error reading joystick input." << std::endl;
    }

    if (js.type & JS_EVENT_AXIS) {
        if (js.number == 0) {
            *posX = js.value;
        } else if (js.number == 1) {
            *posY = js.value;
        }
    }

    return;
}
GamePad::GamePad() {
    if( ( joy_fd = open( JOY_DEV , O_RDONLY)) == -1 )
    {
        printf( "Couldn't open joystick\n" );
        return -1;
    }

    ioctl( joy_fd, JSIOCGAXES, &num_of_axis );
    ioctl( joy_fd, JSIOCGBUTTONS, &num_of_buttons );
    ioctl( joy_fd, JSIOCGNAME(80), &name_of_joystick );

    axis = (int *) calloc( num_of_axis, sizeof( int ) );
    button = (char *) calloc( num_of_buttons, sizeof( char ) );

    printf("Joystick detected: %s\n\t%d axis\n\t%d buttons\n\n"
        , name_of_joystick
        , num_of_axis
        , num_of_buttons );

    close( joy_fd );    /* too bad we never get here */

}

GamePad::~GamePad() {
    if (fd != -1) {
        close(fd);
    }
}

unsigned short GamePad::getButtonState() 
{
    unsigned short ret=0;
    for(int i =0; i<10; i++)
    {
        read(joy_fd, &js, sizeof(struct js_event));
        
        switch (js.type & ~JS_EVENT_INIT)
        {
            case JS_EVENT_BUTTON:
                button [ js.number ] = js.value;
                break;
        }
        printf("  \r");
    }

    for( x=0 ; x<4 ; ++x )
    {
        printf("B%d: %d  ", x, button[x] );
        ret |= button[x]&(0x01) << (x);
    }

    return ret;
}

void GamePad::getJoystickState(int* posX, int* posY) {

    for(int i =0; i<10; i++)
    {
        read(joy_fd, &js, sizeof(struct js_event));
        
        switch (js.type & ~JS_EVENT_INIT)
        {
            case JS_EVENT_AXIS:
                axis   [ js.number ] = js.value;
            break;
        }
    }
    /* print the results */
    printf( "X: %6d  Y: %6d  ", axis[0], axis[1] );
    printf("  \r");

    return;
}


#endif
