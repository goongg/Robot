#include <stdio.h>
#include <string.h> 
#include <fcntl.h>
#include <stdlib.h> /* atoi() */
#include <unistd.h> /* close() */
#include <errno.h>

#include "Raspi_Itr.h"
#include "error.h"
#include "../GlobalFeature.h"

/* Local Macro */
#if BUILD_OPT == BUILD_OPT_PI
	#define SYSFS_GPIO_DIR "/sys/class/gpio"
	#define SYSFS_PWM_DIR "/sys/class/pwm"
#elif BUILD_OPT == BUILD_OPT_WINDOW
	#define SYSFS_GPIO_DIR "../"
	#define SYSFS_PWM_DIR "../"
#endif

#define MAX_BUF 64
#define GPIO_HIGH  1
#define GPIO_LOW  0
#define E_OK 0
#define PWM_CHENNEL_0 0
#define PWM_CHENNEL_1 1

/* Local Function */
static int exportGPIO(int pin);
static int setGPIODirection(int pin, const char *direction);

static int setPWMPeriod(int pwm, int period);
static int exportPWM(int pwm);
static int enablePWM(int pwm);

/* Global Function */
void Raspi_PortSetup(void)
{	
	(void)exportGPIO(PROT_INT_A1);
	(void)setGPIODirection(PROT_INT_A1, "out");
	(void)exportGPIO(PROT_INT_A2);
	(void)setGPIODirection(PROT_INT_A2, "out");
	(void)exportGPIO(PROT_INT_B1);
	(void)setGPIODirection(PROT_INT_B1, "out");
	(void)exportGPIO(PROT_INT_B2);
	(void)setGPIODirection(PROT_INT_B2, "out");

/*
	(void)exportPWM(PWM_CHENNEL_0);
	(void)enablePWM(PWM_CHENNEL_0);

	(void)exportPWM(PWM_CHENNEL_1);
	(void)enablePWM(PWM_CHENNEL_1);
*/
}

int Raspi_setGPIOValue(int pin, int value) {
    int fd, len;
    char buf[MAX_BUF];

    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", pin);
    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "Can't open GPIO %d value file: %s\n", pin, strerror(errno));
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%d", value);
    write(fd, buf, len);

    close(fd);

    return 0;
}

int Raspi_setPWMDutyCycle(int pwm, int dutyCycle) {
    int fd, len;
    char buf[MAX_BUF];

    snprintf(buf, sizeof(buf), SYSFS_PWM_DIR "/pwmchip0/pwm%d/duty_cycle", pwm);
    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "Can't open PWM %d duty cycle file: %s\n", pwm, strerror(errno));
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%d", dutyCycle);
    write(fd, buf, len);

    close(fd);

    return 0;
}


/* Local Function */
static int exportGPIO(int pin) {
    int fd, len;
    char buf[MAX_BUF];

    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d", pin);
    if (access(buf, F_OK) != -1) {
        fprintf(stderr, "GPIO %d is already exported\n", pin);
        return 0;
    }

    fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "Can't export GPIO %d pin: %s\n", pin, strerror(errno));
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%d", pin);
    write(fd, buf, len);

    close(fd);

    return 0;
}

static int setGPIODirection(int pin, const char *direction) {
    int fd, len;
    char buf[MAX_BUF];

    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/direction", pin);
    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "Can't open GPIO %d direction file: %s\n", pin, strerror(errno));
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%s", direction);
    write(fd, buf, len);

    close(fd);

    return 0;
}


static int exportPWM(int pwm) 
{
    int fd, len;
    char buf[MAX_BUF];

    snprintf(buf, sizeof(buf), SYSFS_PWM_DIR "/pwmchip0/pwm%d", pwm);
    if (access(buf, F_OK) != -1) {
        fprintf(stderr, "PWM %d is already exported\n", pwm);
        return 0;  // 이미 export 되어있으면 그냥 리턴
    }

    fd = open(SYSFS_PWM_DIR "/pwmchip0/export", O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "Can't export PWM %d pin: %s\n", pwm, strerror(errno));
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%d", pwm);
    write(fd, buf, len);

    close(fd);

    return 0;
}

static int setPWMPeriod(int pwm, int period) 
{
    int fd, len;
    char buf[MAX_BUF];

    snprintf(buf, sizeof(buf), SYSFS_PWM_DIR "/pwmchip0/pwm%d/period", pwm);
    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "Can't open PWM %d period file: %s\n", pwm, strerror(errno));
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%d", period);
    write(fd, buf, len);

    close(fd);

    return 0;
}

// PWM 활성화 함수
static int enablePWM(int pwm) 
{
    int fd, len;
    char buf[MAX_BUF];

    // enable 파일 열기
    snprintf(buf, sizeof(buf), SYSFS_PWM_DIR "/pwmchip0/pwm%d/enable", pwm);
    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "Can't open PWM %d enable file: %s\n", pwm, strerror(errno));
        return fd;
    }

    // enable 쓰기
    len = snprintf(buf, sizeof(buf), "1");
    write(fd, buf, len);

    // 파일 닫기
    close(fd);

    return 0;
}

int main()
{
	Raspi_PortSetup();
    while(1)
    {
        char c = getchar();
        switch(c)
        {
            case 'W': 
                Raspi_setGPIOValue(PROT_INT_A1, 1);
                Raspi_setGPIOValue(PROT_INT_A2, 0);

                Raspi_setGPIOValue(PROT_INT_B1, 1);
                Raspi_setGPIOValue(PROT_INT_B2, 0);            
            break;
            case 'A':
                Raspi_setGPIOValue(PROT_INT_A1, 0);
                Raspi_setGPIOValue(PROT_INT_A2, 0);

                Raspi_setGPIOValue(PROT_INT_B1, 1);
                Raspi_setGPIOValue(PROT_INT_B2, 0);            
            break;
            case 'D':
                Raspi_setGPIOValue(PROT_INT_A1, 1);
                Raspi_setGPIOValue(PROT_INT_A2, 0);

                Raspi_setGPIOValue(PROT_INT_B1, 0);
                Raspi_setGPIOValue(PROT_INT_B2, 0);            
            break;
            case 'S':
                Raspi_setGPIOValue(PROT_INT_A1, 0);
                Raspi_setGPIOValue(PROT_INT_A2, 1);

                Raspi_setGPIOValue(PROT_INT_B1, 0);
                Raspi_setGPIOValue(PROT_INT_B2, 1);            
            break;
            case 'X':
                Raspi_setGPIOValue(PROT_INT_A1, 0);
                Raspi_setGPIOValue(PROT_INT_A2, 0);

                Raspi_setGPIOValue(PROT_INT_B1, 0);
                Raspi_setGPIOValue(PROT_INT_B2, 0);            
            break;            
        }
    }

}