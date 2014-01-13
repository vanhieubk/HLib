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
  
	RCC_ADCCLKConfig(RCC_PCLK2_Div2);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	
	HLib::PIN_SetMode(0, HLib::PERIPHERAL, HLib::IN_ANALOG);
	HLib::PIN_SetMode(1, HLib::PERIPHERAL, HLib::IN_ANALOG);
	HLib::PIN_SetMode(2, HLib::PERIPHERAL, HLib::IN_ANALOG);
	HLib::PIN_SetMode(3, HLib::PERIPHERAL, HLib::IN_ANALOG);

	adc1.Start(1);
	adc1.Calib();

//	ADC_InitTypeDef  ADC_InitStructure;
//	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
//  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
//  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
//  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
//  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
//  ADC_InitStructure.ADC_NbrOfChannel = 1;
//  ADC_Init(ADC1, &ADC_InitStructure);
//	
//  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_13Cycles5);
	
}


void Loop(void){
  uint16_t adcResult;
	uint8_t i;
	
	
	for (i=0; i<4; i++){
	  adc1.Read(i, &adcResult);
	  com1.Print("ADC (");
		com1.Print(i);
		com1.Print(") value is: ");
    com1.Print(adcResult);
    com1.Print("\n");
    HLib::LoopDelay(0xFFFFF);
	}

}
