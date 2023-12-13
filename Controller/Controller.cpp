#include <termios.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <Controller.h>

#define STATE_U 0
#define STATE_R 1
#define STATE_L 2
#define STATE_D 3
#define BUTTON_SIZE 4

Controller::Controller()
{
    int result = pthread_create(&thread_, NULL, &Controller::thread_Controller1ms, this);
    if (result != 0) 
    {
          perror("Failed to create thread: ");
    }
}
Controller::~Controller() {
    pthread_join(thread_, NULL);
}

Controller::getKeystate(int *output)
{
    for(int i=0; i<BUTTON_SIZE; i++)
        output[i] = ButtonState[i];
};

void* Controller::thread_Controller1ms(void* arg) {

    Controller* instance = static_cast<Controller*>(arg);

   	char c;
	struct termios term;
    
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;    
	term.c_lflag &= ~ECHO;      
	term.c_cc[VMIN] = 1;        
	term.c_cc[VTIME] = 0;       
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
    
	while (read(0, &c, sizeof(c)) > 0)
	{
		printf("input: %c\n", c);
        for (int i = 0; i < 4; ++i) {        
            instance->ButtonState[i]=0;
        }
        
        if (c == 'W'){
           instance->ButtonState[STATE_U]=1;
            std::cout << "W\n";
        }
        if (c == 'D'){
            instance->ButtonState[STATE_R]=1;
            std::cout << "D\n";
        }
        if (c == 'A'){
            instance->ButtonState[STATE_L]=1;
            std::cout << "A\n";
        }
        if (c == 'S'){
            instance->ButtonState[STATE_D]=1;
            std::cout << "S\n";
        }        
        usleep(1000);        
    }
}