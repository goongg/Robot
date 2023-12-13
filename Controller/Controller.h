#ifndef CONTROLLER_H
    #define CONTROLLER_H

#include <pthread.h>

class Controller {
public:
    Controller();
    ~Controller();
    void getKeystate(int *output);
private:
    int ButtonState[4];
    pthread_t thread_;
    static void* thread_Controller1ms(void* arg);
};

#endif

