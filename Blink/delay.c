#include "delay.h"

void delay()
{
    int volatile counter = 0;
    while(counter < 1000000) //delay
        counter++;
}
