#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>

class GamePad  {
public:
    GamePad();
    ~GamePad();
    unsigned short getButtonState() ;
    void getJoystickState(int* posX, int* posY) ;
    int getTriggerState(bool isRightTrigger) ;

private:
};

GamePad::GamePad() {
    int fd;
    fd = open("/dev/input/js0", O_RDONLY);
    if (fd == -1) {
        std::cerr << "Unable to open joystick device." << std::endl;
        close(fd);        
        return;
    }
    close(fd);
}

GamePad::~GamePad() {
}

unsigned short GamePad::getButtonState() {
    js_event js;
    ssize_t bytesRead;
    int fd;
    fd = open("/dev/input/js0", O_RDONLY);
    bytesRead = read(fd, &js, sizeof(js_event));
    if (bytesRead == -1) {
        std::cerr << "Error reading joystick input." << std::endl;
         close(fd);        
        return 1;
    }

    // Check if it's an event for button press or release
    if ((js.type & JS_EVENT_BUTTON) && js.value == 1) {
        return (1 << js.number); // Button index is zero-based
    }
    close(fd);
    return 0;
}

void GamePad::getJoystickState(int* posX, int* posY) {
    js_event js;
    ssize_t bytesRead;
    int fd;
    fd = open("/dev/input/js0", O_RDONLY);
    bytesRead = read(fd, &js, sizeof(js_event));
    if (bytesRead == -1) {
        close(fd);        
    }

    // Check if it's an event for joystick movement
    if (js.type & JS_EVENT_AXIS) {
        if (js.number == 0) {
            *posX = js.value;
        } else if (js.number == 1) {
            *posY = js.value;
        }
    }
}

int GamePad::getTriggerState(bool isRightTrigger) {
    js_event js;
    ssize_t bytesRead;
    int fd;
    fd = open("/dev/input/js0", O_RDONLY);    
    bytesRead = read(fd, &js, sizeof(js_event));
    if (bytesRead == -1) {
        close(fd);        
    }

    // Check if it's an event for trigger movement
    if (js.type & JS_EVENT_AXIS) {
        if (isRightTrigger && js.number == 4) {
            return js.value;
        } else if (!isRightTrigger && js.number == 5) {
            return js.value;
        }
    }
        close(fd);
    return 0;
}





#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include </usr/include/linux/joystick.h>

 

int joy_fd, num_of_axis=0, num_of_buttons=0, x;
int axis[3], 
char *button=NULL, name_of_joystick[80];

struct js_event js;
int Left_Forward;
int Left_Reverse;
int Right_Forward;
int Right_Reverse;

 

void Joystick(void)
{   
	 joy_fd= open("/dev/input/js0", O_RDONLY);    
     read(joy_fd, &js, sizeof(struct js_event));       // 조이스틱 상태를 읽어오는 부분
     switch (js.type & ~JS_EVENT_INIT)
     {
             case JS_EVENT_AXIS:
                     axis   [ js.number ] = js.value;
                     break;
             case JS_EVENT_BUTTON:
                     button [ js.number ] = js.value;
                     break;
             case JS_EVENT_INIT:
                     button [ js.number ] = js.value;
                     break;           
     }

     Left_Forward = axis[0];
     Left_Reverse = axis[1];
    
     if( num_of_axis > 2 )   
     Right_Forward = axis[2];
     if( num_of_axis > 3 )
     Right_Reverse = axis[3];
    
     printf("X: %6d  ", axis[0] );
     printf("Y: %6d  ", axis[1] );
 
     for( x=0 ; x<num_of_buttons ; ++x )
     for( x=0 ; x<8 ; ++x )
             printf("B%d: %d  ", x, button[x] );
     printf("\r");
     printf("\n");
     fflush(stdout);
}

int main() {
    GamePad gamePad;

    // Test the controller functions
    int posX = 0, posY = 0;
    unsigned short buttonState = 0;
    int rightTriggerState = 0, leftTriggerState = 0;
	std::cout<<"?";
    // Read joystick input in a loop (you may want to use threading to handle input asynchronously)
    while (true) {
		std::cout<<"?";
		
       Joystick();
        usleep(10000); // Sleep for 10 milliseconds to avoid busy-waiting
    }

    return 0;
}