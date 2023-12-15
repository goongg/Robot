#ifdef _WIN32 // Windows
#include "GamePad.h"

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
#else


#endif
