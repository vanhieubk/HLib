#include "hlib.h"

HLib::uart_c COM1;
uint32_t counter;
void Setup(void){
  HLib::PIN_SetMode(15, HLib::PERIPHERAL, HLib::OUT_PUSH_PULL);
  HLib::PIN_SetMode(16, HLib::PERIPHERAL, HLib::IN_PULL_UP);
  COM1.Start(1, 115200);
  COM1.Print("*****************************\n");
  COM1.Print("** Welcome to HLib  **\n");
  COM1.Print("*****************************\n"); 
  COM1.Print("This program sends periodic messages to terminal\n");
  counter = 0;
}


void Loop(void){
  HLib::LED_Toggle(0);
  counter++;
  COM1.Print("\nMSG (");
  COM1.Print(counter);
  COM1.Print(")\n");
  HLib::LoopDelay(5000000);
}
