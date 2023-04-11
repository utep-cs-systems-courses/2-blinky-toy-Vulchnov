#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "led.h"
#include "stateMachine.h"

int count = 0;
double tempo = 60;
void __interrupt_vec(WDT_VECTOR) WDT(){
  if (count>=(250/(tempo/60))){
    advanceState();
    count = 0;
  }
  if (count==10){
    redOff();
    greenOff();
    buzzer_set_period(10);
  }
  count++;
}
void increaseTempo(){
  tempo+=5;
}
void decreaseTempo(){
  if (tempo>30){
    tempo-=5;
  }
}
