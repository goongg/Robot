#include <stdio.h>
#include <string.h> 
#include <fcntl.h>
#include <stdlib.h> /* atoi() */
#include <unistd.h> /* close() */

#define BUILD_OPT_PI 0
#define BUILD_OPT_PC 1
#define BUILD_OPT BUILD_OPT_PC

/* Port Setup */
#define PROT_INT_A1 18   //GPIO18 PWM0 Pin12
#define PROT_INT_A2 17   //GPIO17      Pin11
#define PROT_INT_B1 13   //GPIO18 PWM1 Pin12
#define PROT_INT_B2 19   //GPIO17      Pin11


#if BUILD_OPT == BUILD_OPT_PI
    #define SYSFS_GPIO_EXPERT_DIR       "/sys/class/gpio/expert"
    #define SYSFS_GPIO_DIRECTION_DIR    "/sys/class/gpio/direction"
    #define SYSFS_GPIO_VALUE_DIR        "/sys/class/gpio/value"
#elif BUILD_OPT == BUILD_OPT_PC
    #define SYSFS_GPIO_EXPERT_DIR       "../"
    #define SYSFS_GPIO_DIRECTION_DIR    "../"
    #define SYSFS_GPIO_VALUE_DIR        "../"
#endif

#define GPIO_HIGH  1
#define GPIO_LOW  0

#define MAX_BUF 64

#if 0
void Raspi_PortSetup(void)
{
    int fd, len;
    char buf[MAX_BUF];

    /*Set PROT_INT_A1 as GPIO Out*/
    fd = open(SYSFS_GPIO_EXPERT_DIR, O_WRONLY);
	if (fd < 0) {
		fprintf(stderr, "Can't export GPIO %d pin: %s\n", PROT_INT_A1, strerror(errno));
    return;
    }
	len = snprintf(buf, sizeof(buf), "%d", PROT_INT_A1);
    close(fd);    

    fd = open(SYSFS_GPIO_EXPERT_DIR, O_WRONLY);
	if (fd < 0) {
		fprintf(stderr, "Can't export GPIO %d pin: %s\n", PROT_INT_A1, strerror(errno));
    return;
    }
	len = snprintf(buf, sizeof(buf), "%d", PROT_INT_A1);

}
#endif

int Raspi_Set_Gpioval(int GpioPort, int val)
{
    int fd, len;
	char buf[MAX_BUF];
	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_VALUE_DIR, GpioPort);

	fd = open(buf, O_WRONLY);

	if (fd < 0) {
		fprintf(stderr, "Can't set GPIO %d pin value: %s\n", GpioPort, strerror(errno));
		return fd;
	}

	if (val == GPIO_HIGH)
		write(fd, "1", 2);
	else
		write(fd, "0", 2);

	close(fd);

	return 0;
}

int Raspi_Set_PwmPeriod(int Period)
{

}
