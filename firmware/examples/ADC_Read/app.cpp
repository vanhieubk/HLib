#include "hlib.h"

HLib::adc_basis_c adc1;
HLib::uart_c com1;

void Setup(void){
  HLib::PIN_SetMode(15, HLib::PERIPHERAL, HLib::OUT_PUSH_PULL);
  HLib::PIN_SetMode(16, HLib::PERIPHERAL, HLib::IN_PULL_UP);
  com1.Start(1, 115200);
  com1.Print("*****************************\n");
  com1.Print("** Welcome to HLib  **\n");
  com1.Print("*****************************\n"); 
  com1.Print("This program periodic measure ADC on pin 0 and send result to terminal\n");
  
	HLib::PIN_SetMode(0, HLib::PERIPHERAL, HLib::IN_ANALOG);
	adc1.Start(1);
	adc1.Calib();
	adc1.SetChannel(0);
}


void Loop(void){
  uint16_t adcResult;
	
	adc1.Read(&adcResult);
	
	com1.Print("ADC value is: ");
  com1.Print(adcResult);
  com1.Print("\n");
  HLib::LoopDelay(0xFFFFFF);
}
