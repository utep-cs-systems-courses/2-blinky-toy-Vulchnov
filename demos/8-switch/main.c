#include <msp430.h>
#include "libTimer.h"

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)

#define SW1 BIT0                /* switch1 is p1.3 */
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1|SW2|SW3|SW4)		/* only 1 switch on this board */

void main(void) 
{  
  configureClocks();
  enableWDTInterrupts();

  P1DIR |= LEDS;
  P1OUT &= ~LEDS;		/* leds initially off */
  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */

  or_sr(0x18);  // CPU off, GIE on
}
char beatmax = 3;
char pushed = 0;
void
switch_interrupt_handler()
{
  char p1val = P2IN;		/* switch is in P1 */

/* update switch interrupt sense to detect changes from current buttons */
  P2IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */

/* up=red, down=green */
  if (p1val & SW1) {
    pushed=0;
  } else {
    if(pushed);
    else{
    beatmax++;
    pushed=1;
    }
  }
}

/* Switch on P1 (S2) */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}
char beat = 3;
int count = 0;
void
__interrupt_vec(WDT_VECTOR) WDT(){
  if(count>=250){
    if (beat==beatmax){
      P1OUT |= LED_RED;
      beat=0;
    }
    else{
      P1OUT |=LED_GREEN;
      beat++;
    }
    count=0;
  }
  if(count>50){
    P1OUT &= ~LED_RED;
    P1OUT &= ~LED_GREEN;
  }
  count++;
}
