#ifndef IOPlatform_H
    #define IOPlatform_H
    
class iIOPlatform
{
    public: 
        virtual void setGPIOValue(int pin, int value)=0;
        virtual void setPwmDutyCycle(int pwm, int dutyCycle)=0;

    private:
};

#endif