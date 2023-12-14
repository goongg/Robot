#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <xinput.h>
#include <iController.h>

#ifdef _WIN32 // Windows
    #include <Windows.h>
#endif

class GamePad : public iController{
public:
    GamePad();
    ~GamePad();
    unsigned short getBottrnState() override;
    void getJoyStickState(int* posX, int* posY) override;    

private:
    XINPUT_STATE state;   
};

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
