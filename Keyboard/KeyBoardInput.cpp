#include "KeyBoardInput.h"
#include <iostream>

#if BUILD_OPT == BUILD_OPT_PI
KeyboardInput::KeyboardInput()
{
    int result = pthread_create(&thread_, NULL, &KeyboardInput::CheckKey_thread, this);
    if (result != 0) 
    {
          perror("Failed to create thread: ");
    }
}
KeyboardInput::~KeyboardInput() {
    pthread_join(thread_, NULL);
}
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

void* KeyboardInput::CheckKey_thread(void* arg) {

    KeyboardInput* instance = static_cast<KeyboardInput*>(arg);

   	char c;
	struct termios term;
    
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;    // non-canonical input ����
	term.c_lflag &= ~ECHO;      // �Է� �� �͹̳ο� ������ �ʰ�
	term.c_cc[VMIN] = 1;        // �ּ� �Է� ���� ũ��
	term.c_cc[VTIME] = 0;       //���� ���� �ð� (timeout)
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
    
	while (read(0, &c, sizeof(c)) > 0)
	{
		printf("input: %c\n", c);
        for (int i = 0; i < 4; ++i) {        
            instance->KeyboardState[i]=0;
        }
        
        if (c == 'W'){
           instance->KeyboardState[STATE_U]=1;
            std::cout << "W\n";
        }
        if (c == 'D'){
            instance->KeyboardState[STATE_R]=1;
            std::cout << "D\n";
        }
        if (c == 'A'){
            instance->KeyboardState[STATE_L]=1;
            std::cout << "A\n";
        }
        if (c == 'S'){
            instance->KeyboardState[STATE_D]=1;
            std::cout << "S\n";
        }        
        usleep(1000);        
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


#include "../InterfaceRaspi/Raspi_Itr.h"
int main()
{
     KeyboardInput KeyboardInput;

	Raspi_PortSetup();
    while(1)
    {
        usleep(1000);   
        if(KeyboardInput.KeyboardState[STATE_U]==1)
        {
                Raspi_setGPIOValue(PROT_INT_A1, 1);
                Raspi_setGPIOValue(PROT_INT_A2, 0);

                Raspi_setGPIOValue(PROT_INT_B1, 1);
                Raspi_setGPIOValue(PROT_INT_B2, 0);
        }
        if(KeyboardInput.KeyboardState[STATE_L]==1){
                Raspi_setGPIOValue(PROT_INT_A1, 0);
                Raspi_setGPIOValue(PROT_INT_A2, 0);

                Raspi_setGPIOValue(PROT_INT_B1, 1);
                Raspi_setGPIOValue(PROT_INT_B2, 0);            
        }
        if(KeyboardInput.KeyboardState[STATE_R]==1){

                Raspi_setGPIOValue(PROT_INT_A1, 1);
                Raspi_setGPIOValue(PROT_INT_A2, 0);

                Raspi_setGPIOValue(PROT_INT_B1, 0);
                Raspi_setGPIOValue(PROT_INT_B2, 0);            
        }
        if(KeyboardInput.KeyboardState[STATE_D]==1){        
  
                Raspi_setGPIOValue(PROT_INT_A1, 0);
                Raspi_setGPIOValue(PROT_INT_A2, 1);

                Raspi_setGPIOValue(PROT_INT_B1, 0);
                Raspi_setGPIOValue(PROT_INT_B2, 1);    
        }        
    }

}