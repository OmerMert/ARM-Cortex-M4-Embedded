#include <stdio.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"

void UART0_init(void);
void UART0_Transmitter(unsigned char data);
char UART0_Receiver(void);
void TransmitString(char *string);
void DelayMs(int counter);

/* UART Communication through Putty */

int main(void)
{

    UART0_init();
    char *string = "Hello World";
    TransmitString(string);

    return 0;
}

void UART0_init(void)
{
    /* UART0 initialization */
    SYSCTL_RCGCUART_R |= 0x01;           /* Enable the UART module using the RCGCUART register */
    SYSCTL_RCGCGPIO_R |= 0x01;           /* Enable the clock to the appropriate GPIO module via the RCGCGPIO register */

    GPIO_PORTA_AFSEL_R = 0x03;           /* Set the GPIO AFSEL bits for the appropriate pins */
    GPIO_PORTA_PCTL_R = (1<<0)|(1<<4);   /* Configure the PMCn fields in the GPIOPCTL register to assign the UART signals to the appropriate pins*/
    GPIO_PORTA_DEN_R = 0x03;             /* set PA0 and PA1 as digital */
    UART0_CTL_R &= ~0x01;                /* disable UART0 module */
    UART0_IBRD_R = 104;                  /* for 9600 baud rate, integer = 104 (BRD = 16,000,000 / (16 * 9600) = 104.1666) */
    UART0_FBRD_R = 11;                   /* for 9600 baud rate, fractional = 11 (integer(104.1667 * 64 + 0.5) = 1)*/
    UART0_LCRH_R = (0x03<<5);            /* data lenght 8-bit, not parity bit, 1-stop bit */
    UART0_CC_R = 0;                      /* select system clock for UART clock source */
    UART0_CTL_R = (1<<0)|(1<<8)|(1<<9);  /* Enable the UART, Tx and Rx */

}

void UART0_Transmitter(unsigned char data)
{
    while((UART0_FR_R & 0x20) != 0);      /* wait until Tx buffer not full */
    UART0_DR_R = data;
}

char UART0_Receiver(void)
{
    char data;
    while((UART0_FR_R & 0x10) != 0);      /* wait until Tx buffer not full */
    data = UART0_DR_R;                    /* before giving it another byte */
    return data;
}

void TransmitString(char *string)
{
    while(*string)
        UART0_Transmitter(*(string++));

}


void DelayMs(int counter)
{
    volatile int i,j;
        for(i=0;i<counter;i++)
            for(j=0;j<3180;j++)         //delay for 1 msec
            {}
}

