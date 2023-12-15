#ifndef RASP_SYSFS_H
    #define RASP_SYSFS_H

/* Port Setup */
#define PROT_GPI0_IN_23 23
#define PROT_GPI0_IN_24 24
#define PROT_GPI0_IN_20 20
#define PROT_GPI0_IN_21 21

#define PROT_PWM_0 20
#define PROT_PWM_1 21

#include <iIOPlatform.h>

class RaspSysfs : public iIOPlatform
{
    public:
        RaspSysfs();
        ~RaspSysfs();    
        void setGPIOValue(int pin, int value) override;
        void setPwmDutyCycle(int pwm, int dutyCycle) override;

    private:
        void initPort(void);
        void exportGPIO(int pin);
        void setGPIODirection(int pin, const char *direction);
        void setPWMPeriod(int pwm, int period);
        void exportPWM(int pwm);
        void enablePWM(int pwm);
};

#endif // #define RASP_SYSFS_H

