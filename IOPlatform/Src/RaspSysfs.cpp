#include "RaspSysfs.h"

#include <stdio.h>
#include <string.h> 
#include <fcntl.h>
#include <stdlib.h> /* atoi() */
#include <unistd.h> /* close() */
#include <errno.h>
#include <error.h>

/* Local Macro */
#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define SYSFS_PWM_DIR "/sys/class/pwm"

#define MAX_BUF 64
#define GPIO_HIGH  1
#define GPIO_LOW  0
#define E_OK 0
#define PWM_CHENNEL_0 0
#define PWM_CHENNEL_1 1

RaspSysfs::RaspSysfs()
{
	initPort();
}


RaspSysfs::~RaspSysfs()
{
    
}

void RaspSysfs::setGPIOValue(int pin, int value) 
{
    int fd, len;
    char buf[MAX_BUF];

    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", pin);
    fd = open(buf, O_WRONLY);
    if (fd < 0){
        fprintf(stderr, "Can't open GPIO %d value file: %s\n", pin, strerror(errno));    
    return;
    }

    len = snprintf(buf, sizeof(buf), "%d", value);
    write(fd, buf, len);

    close(fd);
    return;
}

void RaspSysfs::setPwmDutyCycle(int pwm, int dutyCycle) 
{
    int fd, len;
    char buf[MAX_BUF];

    snprintf(buf, sizeof(buf), SYSFS_PWM_DIR "/pwmchip0/pwm%d/duty_cycle", pwm);
    fd = open(buf, O_WRONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Can't open PWM %d duty cycle file: %s\n", pwm, strerror(errno));    
        return;
    }

    len = snprintf(buf, sizeof(buf), "%d", dutyCycle);
    write(fd, buf, len);
    close(fd);
    return;

}

void RaspSysfs::initPort(void)
{	
	(void)exportGPIO(PROT_GPI0_IN_23);
	(void)setGPIODirection(PROT_GPI0_IN_23, "out");
	(void)exportGPIO(PROT_GPI0_IN_24);
	(void)setGPIODirection(PROT_GPI0_IN_24, "out");
	(void)exportGPIO(PROT_GPI0_IN_20);
	(void)setGPIODirection(PROT_GPI0_IN_20, "out");
	(void)exportGPIO(PROT_GPI0_IN_21);
	(void)setGPIODirection(PROT_GPI0_IN_21, "out");

	(void)exportPWM(PWM_CHENNEL_0);
	(void)enablePWM(PWM_CHENNEL_0);

	(void)exportPWM(PWM_CHENNEL_1);
	(void)enablePWM(PWM_CHENNEL_1);

    return;
}


void RaspSysfs::exportGPIO(int pin) 
{
    int fd, len;
    char buf[MAX_BUF];

    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d", pin);
    if (access(buf, F_OK) != -1) {
        fprintf(stderr, "GPIO %d is already exported\n", pin);
        return;
    }

    fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "Can't export GPIO %d pin: %s\n", pin, strerror(errno));
        return;
    }

    len = snprintf(buf, sizeof(buf), "%d", pin);
    write(fd, buf, len);
    close(fd);

    return;
}

void RaspSysfs::setGPIODirection(int pin, const char *direction) 
{
    int fd, len;
    char buf[MAX_BUF];

    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/direction", pin);
    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "Can't open GPIO %d direction file: %s\n", pin, strerror(errno));
        return;
    }

    len = snprintf(buf, sizeof(buf), "%s", direction);
    write(fd, buf, len);
    close(fd);

    return;
}


void RaspSysfs::exportPWM(int pwm) 
{
    int fd, len;
    char buf[MAX_BUF];

    snprintf(buf, sizeof(buf), SYSFS_PWM_DIR "/pwmchip0/pwm%d", pwm);
    if (access(buf, F_OK) != -1) {
        fprintf(stderr, "PWM %d is already exported\n", pwm);
        return ;
    }

    fd = open(SYSFS_PWM_DIR "/pwmchip0/export", O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "Can't export PWM %d pin: %s\n", pwm, strerror(errno));
        return;
    }

    len = snprintf(buf, sizeof(buf), "%d", pwm);
    write(fd, buf, len);
    close(fd);

    return;
}

void RaspSysfs::setPWMPeriod(int pwm, int period) 
{
    int fd, len;
    char buf[MAX_BUF];

    snprintf(buf, sizeof(buf), SYSFS_PWM_DIR "/pwmchip0/pwm%d/period", pwm);
    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "Can't open PWM %d period file: %s\n", pwm, strerror(errno));
        return;
    }

    len = snprintf(buf, sizeof(buf), "%d", period);
    write(fd, buf, len);
    close(fd);

    return ;
}

void RaspSysfs::enablePWM(int pwm) 
{
    int fd, len;
    char buf[MAX_BUF];

    snprintf(buf, sizeof(buf), SYSFS_PWM_DIR "/pwmchip0/pwm%d/enable", pwm);
    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "Can't open PWM %d enable file: %s\n", pwm, strerror(errno));
        return;
    }

    len = snprintf(buf, sizeof(buf), "1");
    write(fd, buf, len);
    close(fd);

    return;
}


