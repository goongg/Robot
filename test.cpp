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
        return 1;
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
        std::cerr << "Error reading joystick input." << std::endl;
        close(fd);        
        return;
    }

    // Check if it's an event for joystick movement
    if (js.type & JS_EVENT_AXIS) {
        if (js.number == 0) {
            *posX = js.value;
        } else if (js.number == 1) {
            *posY = js.value;
        }
    }
        close(fd);
}

int GamePad::getTriggerState(bool isRightTrigger) {
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

int main() {
    GamePad gamePad;

    // Test the controller functions
    int posX = 0, posY = 0;
    unsigned short buttonState = 0;
    int rightTriggerState = 0, leftTriggerState = 0;

    // Read joystick input in a loop (you may want to use threading to handle input asynchronously)
    while (true) {
        buttonState = gamePad.getButtonState();
        std::cout << "Button State: " << buttonState << std::endl;

        gamePad.getJoystickState(&posX, &posY);
        std::cout << "Joystick Position: X=" << posX << ", Y=" << posY << std::endl;

        rightTriggerState = gamePad.getTriggerState(true);
        leftTriggerState = gamePad.getTriggerState(false);
        std::cout << "Right Trigger State: " << rightTriggerState << std::endl;
        std::cout << "Left Trigger State: " << leftTriggerState << std::endl;

        usleep(10000); // Sleep for 10 milliseconds to avoid busy-waiting
    }

    return 0;
}