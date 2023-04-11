#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

char toggle_red()		/* always toggle! */
{
  red_on ^= 1;
  return 1;			/* always changes an led */
}

char toggle_green()	/* only toggle green if red is on!  */
{
  green_on ^= 1;
  return 1;
}


void state_advance()		/* alternate between toggling red & green */
{
  char state = 0;

  switch(state){
  case 0:
    toggle_green();
    toggle_red();
    state = 1;
    break;
  case 1:
    toggle_green();
    state = 2;
    break;
  case 2:
    toggle_red();
    toggle_green();
    state = 3;
    break;
  case 3:
    toggle_green();
    state = 0;
    break;
  }
  led_changed = 1;
  led_update();
}



