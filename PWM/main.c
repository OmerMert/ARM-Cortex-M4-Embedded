#include <stdint.h>
#include "tm4c123gh6pm.h"

void delay(long time)
{
    while(time--);
}

int main(void)
{
    /* Clock setting for PWM and GPIO PORTF */
    SYSCTL_RCGCPWM_R |= (1<<1);         // Enable clock to PWM1 module
    SYSCTL_RCGCGPIO_R |= (1<<5);        // Enable system clock to PORTF
    SYSCTL_RCC_R &= ~(1<<20);           // Directly feed clock to PWM1 module without pre-divider

    /* Setting of PF2 pin for M1PWM6 channel output pin */
    GPIO_PORTF_AFSEL_R |= (1<<2);       // PF2 sets a alternate function
    GPIO_PORTF_PCTL_R = 0x00000500;     // Make PF2 PWM output pin
    GPIO_PORTF_DEN_R |= (1<<2);         // set PF2 as a digital pin

    /* PWM1 channel 6 setting */
    PWM1_3_CTL_R &= ~(1<<0);            // Disable Generator 3 counter
    PWM1_3_CTL_R &= ~(1<<1);            // Select down count mode of counter 3
    PWM1_3_LOAD_R = 16000;              // set load value for 1kHz (16MHz/16000)
    PWM1_3_CMPA_R = 8000;               // set duty cycle to 50% by loading of 16000 to PWM1CMPA
    PWM1_3_GENA_R = 0x0000008C;         // Set PWM output when counter reloaded and clear when matches PWMCMPA
    PWM1_3_CTL_R = 1;                   // Enable Generator 3 counter
    PWM1_ENABLE_R |= (1<<6);             // Enable PWM1 channel 6 output

    uint16_t i;
    while(1)
    {
        for(i = 0; i < 16000; i++)
        {
            PWM1_3_CMPA_R = i;
            delay(1000);
        }
        delay(10000);
        for(i = 16000; i > 0; i--)
        {
            PWM1_3_CMPA_R = i;
            delay(1000);
        }
        delay(10000);


    }

}


