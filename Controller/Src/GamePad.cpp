#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <iController.h>

#ifdef _WIN32 // Windows
    #include <Windows.h>
    #include <xinput.h>
#else

#endif

class GamePad : public iController{
public:
    GamePad();
    ~GamePad();
    unsigned short getBottrnState() override;
    void getJoyStickState(int* posX, int* posY) override;    

private:
#ifdef _WIN32 // Windows
    XINPUT_STATE state; 
#elif __linux__
    int fd;    
#endif
};

#ifdef _WIN32 // Windows
GamePad::GamePad(){
    if (XInputGetState(0, nullptr) != ERROR_SUCCESS) {
    }
}

GamePad::~GamePad(){
}

unsigned short GamePad::getBottrnState()
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

void GamePad::getJoyStickState(int* posX, int* posY) {

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


#elif __linux__
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
        return (1 << js.number); 
    }

    return 0;
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
}
#endif
