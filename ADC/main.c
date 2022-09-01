#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "tm4c123gh6pm.h"

void DelayMs(int counter);

int main(void)
{
    unsigned int adc_data = 0;      //variable that contains adc value

    /* Enable Clock to ADC0 and GPIO pins */
    SYSCTL_RCGCGPIO_R |= (1<<4);    // Enable clock for PE
    DelayMs(10);
    SYSCTL_RCGCADC_R |= (1<<0);     // ADC0 clock enable

    /* initialize PE3 for AN0 input */
    GPIO_PORTE_AFSEL_R |= (1<<3);   //enable alternate function
    GPIO_PORTE_DEN_R &= ~(1<<3);    //disable digital function
    GPIO_PORTE_AMSEL_R |= (1<<3);   //enable analog function

    /* initialize sample sequencer3 */
    ADC0_ACTSS_R &= ~(1<<3);        // disable SS3 during configuration
    ADC0_EMUX_R  &= ~0xF000;        // software trigger conversion
    ADC0_SSMUX3_R = 0;              // get input from channel 0
    ADC0_SSCTL3_R |= (1<<1)|(1<<2); // take one sample at a time, set flag at 1st sample
    ADC0_ACTSS_R = (1<<3);          // enable ADC0 sequencer 3

    /*Iniitialize PF3 as a digital output pin */
    SYSCTL_RCGCGPIO_R |= 0x20;      // turn on bus clock for GPIOF
    DelayMs(20);
    GPIO_PORTF_DIR_R |= 0x08;       // set GREEN pin as a digital output pin
    GPIO_PORTF_DEN_R |= 0x08;       // Enable PF3 pin as a digital pin

    while(1)
    {
        ADC0_PSSI_R = (1<<3);
        while((ADC0_RIS_R & 8) == 0) ;
        adc_data = ADC0_SSFIFO3_R;
        ADC0_ISC_R = 8;
        if(adc_data >= 1024)
            GPIO_PORTF_DATA_R = 0x00;
        else
            GPIO_PORTF_DATA_R = 0x08;


    }
    //return 0;
}

void DelayMs(int counter)
{
    volatile int i,j;             //volatile is important for variables incremented in code
        for(i=0;i<counter;i++)
            for(j=0;j<3180;j++)         //delay for 1 msec
            {}
}

