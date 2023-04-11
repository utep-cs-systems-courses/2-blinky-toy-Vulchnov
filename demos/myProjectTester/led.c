#include "led.h"
#include <msp430.h>


void led_init() 
{  
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;   
}

void redOn(){
  P1OUT |= LED_RED;
}

void redOff(){
  P1OUT &= ~LED_RED;
}

void greenOn()
{
  P1OUT |= LED_GREEN;
}
void greenOff()
{
  P1OUT &= ~LED_GREEN;
}
