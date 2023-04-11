#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

char beat = 3;
int count = 0;
void
__interrupt_vec(WDT_VECTOR) WDT(){
  if(count>=(250/(tempo/60))){
    if (beat>=beatmax){
      P1OUT |= LED_RED;
      buzzer_set_period(1000);
      beat=0;
    }
    else{
      P1OUT |=LED_GREEN;
      buzzer_set_period(2000);
      beat++;
    }
    count=0;
  }
  if(count>10){
    P1OUT &= ~LED_RED;
    P1OUT &= ~LED_GREEN;
    buzzer_set_period(10);
  }
  count++;
}
