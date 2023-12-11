#ifndef RASPI_ITR_H
    #define RASPI_ITR_H

/* Port Setup */
#define PROT_INT_A1 23   //GPIO23      Pin12
#define PROT_INT_A2 24   //GPIO24      Pin11
#define PROT_INT_B1 20   //GPIO20      Pin12
#define PROT_INT_B2 21   //GPIO21      Pin11


#endif // #define RASPI_ITR_H

extern void Raspi_PortSetup(void);
extern int  Raspi_setGPIOValue(int pin, int value);
extern int  Raspi_setPWMDutyCycle(int pwm, int dutyCycle);
