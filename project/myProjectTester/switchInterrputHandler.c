#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "stateMachine.h"

#define SW1 BIT0                /* switch1 is p1.3 */
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1|SW2|SW3|SW4)		/* only 1 switch on this board */

void switch_init() 
{    
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  
}
char pushed = 0;
void
switch_interrupt_handler()
{
  char p2val = P2IN;		/* switch is in P1 */
  
/* update switch interrupt sense to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */

/* up=red, down=green */
  if (p2val & SW1) {
    pushed=0;
  } else {
    if(pushed);
    else{
      decreaseBeatMax();
      pushed = 1;
    }
  }
  if (p2val & SW2) {
    pushed = 0;
  } else {
    if(pushed);
    else{
      increaseBeatMax();
      pushed = 1;
    }
  }
  if (p2val & SW3) {
    pushed = 0;
  } else {
    if(pushed);
    else{
      decreaseTempo();
      pushed = 1;
    }
  }
  if (p2val & SW4) {
    pushed = 0;
  } else {
    if(pushed);
    else{ 
      increaseTempo();
      pushed = 1;
    }
  }
}

/* Switch on P1 (S2) */
void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}
