#ifndef CONTROLLER_H
    #define CONTROLLER_H
    

class iController 
{
    public:
        virtual unsigned short getButtonState()=0;
        virtual void getJoystickState(int* posX, int* posY, int* posR, int* posL) =0;
    private:
};

#endif

