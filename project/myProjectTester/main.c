#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "stateMachine.h"
#include "led.h"

void main(void) 
{  
  configureClocks();
  enableWDTInterrupts();
  buzzer_init();
  led_init();
  switch_init();

  or_sr(0x18);  // CPU off, GIE on
}
