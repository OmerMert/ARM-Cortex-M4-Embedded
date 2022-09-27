#include <stdint.h>
#include "tm4c123gh6pm.h"

void TIMER0A_Handler(void){
    GPIO_PORTF_DATA_R ^= (1<<2);    //Toggle Blue LED
    TIMER0_ICR_R |= (1<<0);         //Clear TIMER0_RIS_R

}

int main(void)
{
    /* Configuration for Blue LED on Port F */
    SYSCTL_RCGCGPIO_R |= (1<<5);
    GPIO_PORTF_AFSEL_R &= ~(1<<2);
    GPIO_PORTF_DIR_R |= (1<<2);
    GPIO_PORTF_DEN_R |= (1<<2);
    GPIO_PORTF_DATA_R |= (1<<2);

    /* Configuration for Periodic General-Purpose Timer 0A */
    SYSCTL_RCGCTIMER_R |= (1<<0);
    TIMER0_CTL_R &= ~(1<<0);        // Disable Timer
    TIMER0_CFG_R = 0x00000000;
    TIMER0_TAMR_R |= (0x2<<0);      // Set Periodic Timer Mode
    TIMER0_TAMR_R &= ~(1<<4);       // Set Count Down Mode
    TIMER0_TAILR_R = 0x00F42400;    // Set Start Value 16.000.000
    TIMER0_IMR_R |= (1<<0);         // Enable interrupt
    NVIC_EN0_R |= (1<<19);          // Configure NVIC for Timer 0A
    TIMER0_CTL_R |= (1<<0);         // Enable Timer

    while(1)
    {

    }


}
