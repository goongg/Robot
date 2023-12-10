#include <stdio.h>
#include "../GlobalFeature.h"
#include "../InterfaceRaspi/Raspi_Itr.h"
#include "KeyBoardInput.h"
#include "string.h"

#if BUILD_OPT == BUILD_OPT_PI
    #include <ev.h>
#else if BUILD_OPT == BUILD_OPT_WINDOW
    #include <Windows.h>
#endif

class KeyboardInput
{
    void Init();
    void CheckKeyboardState();
    public:
        int KeyboardState[4];

};

#if BUILD_OPT == BUILD_OPT_PI
void KeyboardInput::CheckKeyboardState()
{
    char buf[10];
    ssize_t n = read(0, buf, sizeof(buf) - 1);
    if (n > 0) {
        buf[n] = '\0';
        memset(KeyboardState, , 0, sizeof(KeyboardState));        
        // 여덟 방향으로의 이동 조합 처리
        if (buf[0] == 'w') KeyboardState[STATE_U]=1;
        else if (buf[0] == 's') dy = 1;
        else if (buf[0] == 'a') dx = -1;
        else if (buf[0] == 'd') dx = 1;

        if (n > 1) {
            // 특별한 키 조합이 있는 경우 추가 처리
            if (buf[1] == 'w') dy = -1;
            else if (buf[1] == 's') dy = 1;
            else if (buf[1] == 'a') dx = -1;
            else if (buf[1] == 'd') dx = 1;
        }
    }  
}
#else if BUILD_OPT == BUILD_OPT_WINDOW
void KeyboardInput::CheckKeyboardState()
{
    memset(KeyboardState, 0, 4);        

    if (GetAsyncKeyState('W') & 0x8000)
        KeyboardState[STATE_U]=1;
    
    if (GetAsyncKeyState('D')) & 0x8000) 
        KeyboardState[STATE_R]=1;

    if (GetAsyncKeyState('A') & 0x8000) 
        KeyboardState[STATE_L]=1;

    if (GetAsyncKeyState('S') & 0x8000) 
        KeyboardState[STATE_D]=1;
}
#endif 