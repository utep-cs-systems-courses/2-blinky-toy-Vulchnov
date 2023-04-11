#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "led.h"

char beatmax = 3;
char beat = 3;
void advanceState(){
  if (beat>=beatmax){ 
    redOn();
    buzzer_set_period(1000);
    beat=0;
  }
  else{
    greenOn();
    buzzer_set_period(2000);
    beat++;
  }
}
void increaseBeatMax(){
  if(beatmax<6){
    beatmax++;
  }
}
void decreaseBeatMax(){
  if(beatmax>3){
    beatmax--;
  }
}
