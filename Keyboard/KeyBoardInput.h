#ifndef KEYBOARD_INPUT_H
    #define KEYBOARD_INPUT_H


#define STATE_U 0
#define STATE_R 1
#define STATE_L 2
#define STATE_D 3

#if BUILD_OPT == BUILD_OPT_PI
    #include <pthread.h>

class KeyboardInput {
public:
    KeyboardInput();
    ~KeyboardInput();
    int KeyboardState[4];

private:
    pthread_t thread_;

    static void* CheckKey_thread(void* arg);
};

#endif

#if BUILD_OPT == BUILD_OPT_WINDOW
#include <windows.h>
#include <mutex>
#include "../GlobalFeature.h"

class KeyboardInput
{
    public:
        KeyboardInput();
        ~KeyboardInput();
        int KeyboardState[4];
 
    private:

    HANDLE thread_;    
    std::mutex arrayMutex;  
    static DWORD WINAPI CheckKey_thread(LPVOID lpParam);
};
#endif


#endif