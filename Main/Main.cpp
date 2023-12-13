#include <Controller.h>
#include <Motor.h>
#include <RaspSysfs.h>
#include <iostream>

int main()
{
    /*For Raspberrypi 4B PinOut Setup*/
    RaspSysfs _RaspiSysfs;
    Motor _Motor(_RaspiSysfs.setGPIOValue, _RaspiSysfs.exportGPIO);
    
    Controller _8bitdo;

    while(1);
    return;
}