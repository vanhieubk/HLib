#include "hlib.h"

void Setup(void){
}


void Loop(void){
  HLib::LED_Toggle(0);
  HLib::LoopDelay(1000000);
}
