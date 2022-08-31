#include <stdio.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"

#define LED_RED   (0x01 << 1)
#define LED_BLUE  (0x01 << 2)
#define LED_GREEN (0x01 << 3)

unsigned int state;

int main(void)
{
    SYSCTL_RCGCGPIO_R |= 0x20; // Enable clock for GPIOF

    GPIO_PORTF_DIR_R |= 0x02; //set pins PF4 as input and 1,2, and 3 as output
    GPIO_PORTF_PUR_R |= 0x10; // Enable Pull Up resistor PF4
    GPIO_PORTF_DEN_R |= 0x12;

    GPIO_PORTF_DATA_R = 0x00;

    while(1){
        state = GPIO_PORTF_DATA_R & 0x10;
        GPIO_PORTF_DATA_R = (~state>>3);    /* put it on red LED */



    }
    //return 0;
}
