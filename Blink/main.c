#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "delay.h"

#define LED_RED   (0x1U << 1)
#define LED_BLUE  (0x1U << 2)
#define LED_GREEN (0x1U << 3)


int main(void)
{
    SYSCTL_RCGCGPIO_R |= 0x20U; // Enable clock for GPIOF
    GPIO_PORTF_DIR_R |= 0x0EU; //set pins 1,2, and 3 as output
    GPIO_PORTF_DEN_R |= 0x0EU;

    GPIO_PORTF_DATA_R |= LED_BLUE;
    while(1){
        GPIO_PORTF_DATA_R |= LED_RED;

        delay();

        GPIO_PORTF_DATA_R &= ~LED_RED;

        delay();

    }
	//return 0;
}