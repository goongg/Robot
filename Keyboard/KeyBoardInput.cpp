#include "KeyboardInput.h"

#if BUILD_OPT == BUILD_OPT_PI
#include <ev.h>
KeyboardInput::KeyboardInput()
{
    int result = pthread_create(&thread_, NULL, &KeyboardInput::CheckKey_thread, this);
    if (result != 0) {
        std::cerr << "Failed to create thread: " << strerror(result) << std::endl;
    }
    while(1);
}
KeyboardInput::~KeyboardInput() {
    pthread_join(thread_, NULL);
}
void* KeyboardInput::CheckKey_thread(void* arg) {
    KeyboardInput* instance = static_cast<KeyboardInput*>(arg);
    while (1) {
        // 1ms 대기
        usleep(1000);
        char buf[10];
        ssize_t n = read(0, buf, sizeof(buf) - 1);
        if (n > 0) 
        {
            buf[n] = '\0';
            for(int i =0; i<4; i++)
                KeyboardState[i]=0;

            if (buf[0] == 'W') KeyboardState[STATE_U]=1;
            else if (buf[0] == 'A') KeyboardState[STATE_L]=1;
            else if (buf[0] == 'D') KeyboardState[STATE_R]=1;
            else if (buf[0] == 'S') KeyboardState[STATE_D]=1;

            if (n > 1) {
                if (buf[1] == 'W') KeyboardState[STATE_U]=1;
                else if (buf[1] == 'A') KeyboardState[STATE_L]=1;
                else if (buf[1] == 'D') KeyboardState[STATE_R]=1;
                else if (buf[1] == 'S') KeyboardState[STATE_D]=1;
            }
        }  
    }
}
#endif

#if BUILD_OPT == BUILD_OPT_WINDOW
#include <iostream>
KeyboardInput::KeyboardInput()
{
    thread_ = CreateThread(NULL, 0, &KeyboardInput::CheckKey_thread, this, 0, NULL);
    if (thread_ == NULL) {
        std::cerr << "Failed to create thread" << std::endl;
    }
    while(1);
}

KeyboardInput::~KeyboardInput()
{
    if (thread_ != NULL) {
        CloseHandle(thread_);
    }
}

DWORD WINAPI KeyboardInput::CheckKey_thread(LPVOID lpParam)
{
    KeyboardInput* instance = static_cast<KeyboardInput*>(lpParam);
    while(1)
    {
        Sleep(1);        
        std::lock_guard<std::mutex> lock(instance->arrayMutex);
        for (int i = 0; i < 4; ++i) {        
            instance->KeyboardState[i]=0;
        }
        
        if (GetAsyncKeyState('W') & 0x8000){
           instance->KeyboardState[STATE_U]=1;
            std::cout << "W\n";
        }
        if (GetAsyncKeyState('D') & 0x8000){
            instance->KeyboardState[STATE_R]=1;
            std::cout << "D\n";
        }
        if (GetAsyncKeyState('A') & 0x8000) 
        {
            instance->KeyboardState[STATE_L]=1;
            std::cout << "A\n";
        }
        if (GetAsyncKeyState('S') & 0x8000) 
        {
            instance->KeyboardState[STATE_D]=1;
            std::cout << "S\n";
        }
    }
    return 0;
}
#endif

int main()
{
    KeyboardInput t;
}