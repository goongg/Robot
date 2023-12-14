#ifndef CONTROLLER_H
    #define CONTROLLER_H
    

class iController 
{
    public:
        virtual unsigned short getBottrnState()=0;
        virtual void getJoyStickState(int* posX, int* posY) =0;
    private:
};

#endif

