#include <stdio.h>
#include "../GlobalFeature.h"
#include "../InterfaceRaspi/Raspi_Itr.h"

#include "Motor_Control.h"
#include "../Keyboard/KeyboardInput.h"

class MotorControl 
{
    public:
        void move();
        KeyboardInput Input;
};

void MotorControl::move()
{
    if( Input.KeyboardState[STATE_U]=1);

}

