#ifndef RASPI_ITR_H
    #define RASPI_ITR_H

/* Port Setup */
#define PROT_INT_A1 18   //GPIO18 PWM0 Pin12
#define PROT_INT_A2 17   //GPIO17      Pin11
#define PROT_INT_B1 13   //GPIO18 PWM1 Pin12
#define PROT_INT_B2 19   //GPIO17      Pin11


#endif // #define RASPI_ITR_H

extern void Raspi_PortSetup(void);
extern int setGPIOValue(int pin, int value);
extern int setPWMDutyCycle(int pwm, int dutyCycle);
