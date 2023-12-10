#include <stdio.h>
#include "../GlobalFeature.h"
#include "../InterfaceRaspi/Raspi_Itr.h"
#include "../Keyboard/KeboardInput.h"
class MotorControl 
{
    int dx, dy, weight_x, weight_y;
    void move();
    void input();
};


