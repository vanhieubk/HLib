#include "hlib.h"

HLib::uart_c com1;

void Setup(void){
  HLib::PIN_SetMode(TXD_PIN_INDEX, HLib::PERIPHERAL, HLib::OUT_PUSH_PULL);
  HLib::PIN_SetMode(RXD_PIN_INDEX, HLib::PERIPHERAL, HLib::IN_PULL_UP);
  com1.Start(1, 115200);
  com1.Print("*****************************\n");
  com1.Print("** Welcome to HLib  **\n");
  com1.Print("*****************************\n"); 
  com1.Print("This program sends received data back\n");
}


void Loop(void){
  uint8_t recvData;
  if (com1.HasData()){
    com1.Get(&recvData);
    com1.Out(recvData);
  }
}
