#include "hlib.h"

HLib::uart_c com1;
uint32_t counter;

void Setup(void){
  HLib::PIN_SetMode(TXD_PIN_INDEX, HLib::PERIPHERAL, HLib::OUT_PUSH_PULL);
  HLib::PIN_SetMode(RXD_PIN_INDEX, HLib::PERIPHERAL, HLib::IN_PULL_UP);
  com1.Start(1, 115200);
  com1.Print("*****************************\n");
  com1.Print("** Welcome to HLib  **\n");
  com1.Print("*****************************\n"); 
  com1.Print("This program sends periodic messages\n");
  counter = 0;
}


void Loop(void){
  com1.Print("Message (");
  com1.Print(counter);
  com1.Print(")\n");
  counter ++;
  HLib::LoopDelay(0xFFFFFF);
}
