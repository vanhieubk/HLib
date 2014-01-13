#include "hlib.h"

HLib::uart_c COM1;

void Setup(void){
  HLib::PIN_SetMode(15, HLib::PERIPHERAL, HLib::OUT_PUSH_PULL);
  HLib::PIN_SetMode(16, HLib::PERIPHERAL, HLib::IN_PULL_UP);
  COM1.Start(1, 115200);
  COM1.Print("*****************************\n");
  COM1.Print("** Welcome to HLib  **\n");
  COM1.Print("*****************************\n"); 
  COM1.Print("This program sends received data back\n");
}


void Loop(void){
  uint8_t recvData;
  if (COM1.HasData()){
    COM1.Get(&recvData);
    COM1.Out(recvData);
  }
}
