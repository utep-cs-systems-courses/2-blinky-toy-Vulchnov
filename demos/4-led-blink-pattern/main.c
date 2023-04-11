//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);			/* CPU off, GIE on */
}

// global state vars that control blinking
int blinkLimitG = 5; // duty cycle = 1/blinkLimit
int blinkLimitR = 5;
int blinkCountG = 0;  // cycles 0...blinkLimit-1
int blinkCountR = 8;
int secondCount = 0; // state var representing repeating time 0…1s

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  // handle blinking 
  blinkCountG ++;
  blinkCountR ++;
  if (blinkCountG >= blinkLimitG) { // on for 1 interrupt period
    blinkCountG = 0;
    P1OUT |= LED_GREEN;
  } else		          // off for blinkLimit - 1 interrupt periods
    P1OUT &= ~LED_GREEN;
  if(blinkCountR >= blinkLimitR){
    blinkCountR = 0;
    P1OUT |=LED_RED;
  } else
    P1OUT &=~LED_RED;
  
  // measure a second
  secondCount ++;
  if (secondCount >= 250) {  // once each second
    secondCount = 0;
    blinkLimitR ++;
    if(blinkLimitR>=8){
      blinkLimitR=0;
    }
    blinkLimitG --;           // reduce duty cycle
    if (blinkLimitG <= 0)     // but don't let duty cycle go below 1/7.
      blinkLimitG = 8;
  }
} 

