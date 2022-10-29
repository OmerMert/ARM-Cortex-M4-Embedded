#include "TM4C123.h"                    // Device header

void LCD_init(void);
void LCD_Data(unsigned char data);
void LCD_Cmd(unsigned char command);
void delay_us(int n);
void delay_ms(int n);

int main(void)
{
    LCD_init();             // initialize LCD
    LCD_Cmd(0x01);          // clear display
    LCD_Cmd(0x80);			// first row
	delay_ms(500);
    LCD_Data('C');
    delay_us(500);

}

// Control pins connected to PA, data pins connected to PB
// RS -> PA5, RW -> PA6, E -> PA7
// D0,D1,...,D7 -> PB0, PB1,....,PB7
void LCD_init(void){
    SYSCTL->RCGCGPIO = 0x03;
    GPIOA->DIR |= 0xE0;     // PORTA control RS,E,RW
    GPIOA->DEN |= 0xE0;
    GPIOB->DIR |= 0xFF;
    GPIOB->DEN |= 0xFF;
    LCD_Cmd(0x20);          // 8-bits, 2 line display, 5x7 font
    LCD_Cmd(0x32); 
	LCD_Cmd(0x06);          // increment cursor automatically
    LCD_Cmd(0x01);          // clear display
	LCD_Cmd(0x0F);          // Turn on display
    
}

void LCD_Data(unsigned char data){
    GPIOA->DATA = 0x20;     // RS = 1, RW = 0, E = 0
    GPIOB->DATA = data;
    GPIOA->DATA |= 0x80;    // E = 1 to secure command
    delay_us(0);
    GPIOA->DATA = 0x00;     // RS = 0, RW = 0, E = 0
    delay_us(0);
}

void LCD_Cmd(unsigned char command){
    GPIOA->DATA = 0x00;     // RS = 0, RW = 0, E = 0
    GPIOB->DATA = command;
    GPIOA->DATA = 0x80;     // E = 1 send pulse to secure command
    delay_us(0);
    GPIOA->DATA = 0x00;
	delay_us(37);
}

// Microsecond delay
void delay_us(int n){
    int i,j;
    for(i = 0; i < n; i++)
        for(j = 0; j < 3;j++);
}

// Millisecond delay
void delay_ms(int n){
    int i,j;
    for(i = 0; i < n; i++)
        for(j = 0; j < 3180;j++);
}



