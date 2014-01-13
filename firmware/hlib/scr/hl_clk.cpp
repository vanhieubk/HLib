#include "hlib.h"

namespace HLib{
	
/***** private functions declaration ********/
void _CLK_APB2Ctrl(uint32_t RCC_APB2Periph, bool enable);
void _CLK_APB1Ctrl(uint32_t RCC_APB2Periph, bool enable);
void _CLK_AHBCtrl(uint32_t  RCC_AHBPeriph,  bool enable);
void _CLK_RTCCtrl(bool enable);

/***** private function implementation ********/
void _CLK_APB2Ctrl(uint32_t RCC_APB2Periph, bool enable){
  if (enable){
	  RCC->APB2ENR |= RCC_APB2Periph;
  }
	else{
		RCC->APB2ENR &= ~RCC_APB2Periph;
  }
}


void _CLK_APB1Ctrl(uint32_t RCC_APB1Periph, bool enable){
  if (enable){
	   RCC->APB1ENR |= RCC_APB1Periph;
  }
	else{
		 RCC->APB1ENR &= ~RCC_APB1Periph;
  }
}


void _CLK_AHBCtrl(uint32_t  RCC_AHBPeriph,  bool enable){
  if (enable){
	  RCC->AHBENR |= RCC_AHBPeriph;
  }
	else{
		RCC->AHBENR &= ~RCC_AHBPeriph;
  }
}


void _CLK_RTCCtrl(bool enable){
  if (enable){
    RCC->BDCR |= HL_BitMask(16);
  }
  else{
    RCC->BDCR &= ~HL_BitMask(16);
  }
 }


/****  Public Functions implementation *****/
err_t CLK_Ctrl(clk_periph_t peripheralClk, bool mode){
  switch(peripheralClk){
	  case CLK_TIM2:  	_CLK_APB1Ctrl(RCC_APB1Periph_TIM2,   mode); break;
	  case CLK_TIM3:  	_CLK_APB1Ctrl(RCC_APB1Periph_TIM3,   mode); break;
	  case CLK_TIM4:  	_CLK_APB1Ctrl(RCC_APB1Periph_TIM4,   mode); break;
	  case CLK_TIM5:  	_CLK_APB1Ctrl(RCC_APB1Periph_TIM5,   mode); break;
	  case CLK_TIM6:  	_CLK_APB1Ctrl(RCC_APB1Periph_TIM6,   mode); break;
	  case CLK_TIM7:  	_CLK_APB1Ctrl(RCC_APB1Periph_TIM7,   mode); break;
		case CLK_WWDG:  	_CLK_APB1Ctrl(RCC_APB1Periph_WWDG,   mode); break;
		case CLK_SPI2:  	_CLK_APB1Ctrl(RCC_APB1Periph_SPI2,   mode); break;
	  case CLK_SPI3:  	_CLK_APB1Ctrl(RCC_APB1Periph_SPI3,   mode); break;
	  case CLK_UART2:   _CLK_APB1Ctrl(RCC_APB1Periph_USART2, mode); break;
	  case CLK_UART3:   _CLK_APB1Ctrl(RCC_APB1Periph_USART3, mode); break;
		#ifdef STM32F103RCT6_MCU 
	  case CLK_UART4:   _CLK_APB1Ctrl(RCC_APB1Periph_USART4, mode); break;
	  case CLK_UART5:   _CLK_APB1Ctrl(RCC_APB1Periph_USART5, mode); break;
		#endif
	  case CLK_I2C1:  	_CLK_APB1Ctrl(RCC_APB1Periph_I2C1,   mode); break;
	  case CLK_I2C2:  	_CLK_APB1Ctrl(RCC_APB1Periph_I2C2,   mode); break;
	  case CLK_CAN1:   	_CLK_APB1Ctrl(RCC_APB1Periph_CAN1,   mode); break;
	  case CLK_BKP:    	_CLK_APB1Ctrl(RCC_APB1Periph_BKP,    mode); break;
	  case CLK_PWR:    	_CLK_APB1Ctrl(RCC_APB1Periph_PWR,    mode); break;
	  case CLK_DAC:    	_CLK_APB1Ctrl(RCC_APB1Periph_DAC,    mode); break;
	  case CLK_CEC:    	_CLK_APB1Ctrl(RCC_APB1Periph_CEC,    mode); break;
	  case CLK_TIM12:  	_CLK_APB1Ctrl(RCC_APB1Periph_TIM12,  mode); break;
	  case CLK_TIM13:  	_CLK_APB1Ctrl(RCC_APB1Periph_TIM13,  mode); break;
	  case CLK_TIM14:  	_CLK_APB1Ctrl(RCC_APB1Periph_TIM14 , mode); break;
	  case CLK_USB_DEV: _CLK_APB1Ctrl(RCC_APB1Periph_USB,    mode); break;
	
    case CLK_RTC:     _CLK_RTCCtrl(mode);
	
	  case CLK_AFIO:  	_CLK_APB2Ctrl(RCC_APB2Periph_AFIO,   mode); break;
	  case CLK_GPIOA:  	_CLK_APB2Ctrl(RCC_APB2Periph_GPIOA,  mode); break;
	  case CLK_GPIOB:  	_CLK_APB2Ctrl(RCC_APB2Periph_GPIOB,  mode); break;
	  case CLK_GPIOC:  	_CLK_APB2Ctrl(RCC_APB2Periph_GPIOC,  mode); break;
	  case CLK_GPIOD:  	_CLK_APB2Ctrl(RCC_APB2Periph_GPIOD,  mode); break;
	  case CLK_GPIOE:  	_CLK_APB2Ctrl(RCC_APB2Periph_GPIOE,  mode); break;
	  case CLK_GPIOF:  	_CLK_APB2Ctrl(RCC_APB2Periph_GPIOF,  mode); break;
	  case CLK_GPIOG:  	_CLK_APB2Ctrl(RCC_APB2Periph_GPIOG,  mode); break;
	  case CLK_ADC1:  	_CLK_APB2Ctrl(RCC_APB2Periph_ADC1,   mode); break;
	  case CLK_ADC2 :  	_CLK_APB2Ctrl(RCC_APB2Periph_ADC2,   mode); break;
	  case CLK_TIM1:  	_CLK_APB2Ctrl(RCC_APB2Periph_TIM1,   mode); break;
	  case CLK_SPI1:  	_CLK_APB2Ctrl(RCC_APB2Periph_SPI1,   mode); break;
	  case CLK_TIM8:  	_CLK_APB2Ctrl(RCC_APB2Periph_TIM8,   mode); break;
	  case CLK_UART1:  	_CLK_APB2Ctrl(RCC_APB2Periph_USART1, mode); break;
	  case CLK_ADC3:  	_CLK_APB2Ctrl(RCC_APB2Periph_ADC3,   mode); break;
	  case CLK_TIM15:  	_CLK_APB2Ctrl(RCC_APB2Periph_TIM15,  mode); break;
	  case CLK_TIM16:  	_CLK_APB2Ctrl(RCC_APB2Periph_TIM16,  mode); break;
	  case CLK_TIM17:  	_CLK_APB2Ctrl(RCC_APB2Periph_TIM17,  mode); break;
	  case CLK_TIM9:  	_CLK_APB2Ctrl(RCC_APB2Periph_TIM9,   mode); break;
	  case CLK_TIM10:  	_CLK_APB2Ctrl(RCC_APB2Periph_TIM10,  mode); break;
    case CLK_TIM11:  	_CLK_APB2Ctrl(RCC_APB2Periph_TIM11,  mode); break;


    case CLK_DMA1 :   _CLK_AHBCtrl(RCC_AHBPeriph_DMA1, 			mode); break;
    case CLK_DMA2 :   _CLK_AHBCtrl(RCC_AHBPeriph_DMA2, 			mode); break;
    case CLK_CRC :    _CLK_AHBCtrl(RCC_AHBPeriph_CRC, 				mode); break;
    #if 0
    case CLK_SRAM :   _CLK_AHBCtrl(RCC_AHBPeriph_SRAM, 			mode); break;
    case CLK_FLITF :  _CLK_AHBCtrl(RCC_AHBPeriph_FLITF, 			mode); break;
		case CLK_USB_OTG: _CLK_AHBCtrl(RCC_AHBPeriph_OTG_FS, 		mode); break;
    case CLK_ETH_MAC: _CLK_AHBCtrl(RCC_AHBPeriph_ETH_MAC, 		mode); break;
    case CLK_ETH_TX:  _CLK_AHBCtrl(RCC_AHBPeriph_ETH_MAC_Tx, mode); break;
    case CLK_ETH_RX:  _CLK_AHBCtrl(RCC_AHBPeriph_ETH_MAC_Rx, mode); break;
    case CLK_FSMC:    _CLK_AHBCtrl(RCC_AHBPeriph_FSMC, 			mode); break;
    #endif
		#ifdef STM32F103RCT6_MCU
		case CLK_SDIO:    _CLK_AHBCtrl(RCC_AHBPeriph_SDIO, 			mode); break;
		#endif
	  default: return INVALID;
  }
	return OK;
}



uint32_t  CLK_GetSysFreq(void){
  SystemCoreClockUpdate();
  return SystemCoreClock;
}


uint32_t  CLK_GetAHBFreq(void){
  return CLK_GetSysFreq() / ((uint32_t) CLK_GetAHBPrescalar());
}


uint32_t  CLK_GetAPB1Freq(void){
  return CLK_GetAHBFreq() / ((uint32_t) CLK_GetAPB1Prescalar());
}

uint32_t  CLK_GetAPB2Freq(void){
  return CLK_GetAHBFreq() / ((uint32_t) CLK_GetAPB2Prescalar());
}


err_t CLK_SetAHBPrescalar(uint16_t prescalar){
  uint32_t tmpReg;
 
  tmpReg =  RCC->CFGR;
  tmpReg &= ~((uint32_t) 0xF0);
  switch (prescalar){
    case 1:   tmpReg |= (((uint32_t) 0x00) << 4); break;
    case 2:   tmpReg |= (((uint32_t) 0x08) << 4); break;
    case 4:   tmpReg |= (((uint32_t) 0x09) << 4); break;
    case 8:   tmpReg |= (((uint32_t) 0x0A) << 4); break;
    case 16:  tmpReg |= (((uint32_t) 0x0B) << 4); break;
    case 64:  tmpReg |= (((uint32_t) 0x0C) << 4); break;
    case 128: tmpReg |= (((uint32_t) 0x0D) << 4); break;
    case 256: tmpReg |= (((uint32_t) 0x0E) << 4); break;
    case 512: tmpReg |= (((uint32_t) 0x0F) << 4); break;
    default: return INVALID;  
  }
  RCC->CFGR = tmpReg;
  return OK;
}



err_t     CLK_SetAPB1Prescalar(uint8_t prescalar){
  uint32_t tmpReg;
 
  tmpReg =  RCC->CFGR;
  tmpReg &= ~((uint32_t) 0x0700);
  switch (prescalar){
    case 1:  tmpReg |= (((uint32_t) 0x00) << 8); break;
    case 2:  tmpReg |= (((uint32_t) 0x04) << 8); break;
    case 4:  tmpReg |= (((uint32_t) 0x05) << 8); break;
    case 8:  tmpReg |= (((uint32_t) 0x06) << 8); break;
    case 16: tmpReg |= (((uint32_t) 0x07) << 8); break;
    default: return INVALID;
  } 
  RCC->CFGR = tmpReg;
  return OK;
}



err_t CLK_SetAPB2Prescalar(uint8_t prescalar){
  uint32_t tmpReg;
 
  tmpReg =  RCC->CFGR;
  tmpReg &= ~((uint32_t) 0x3800);
  switch (prescalar){
    case 1:  tmpReg |= (((uint32_t) 0x00) << 11); break;
    case 2:  tmpReg |= (((uint32_t) 0x04) << 11); break;
    case 4:  tmpReg |= (((uint32_t) 0x05) << 11); break;
    case 8:  tmpReg |= (((uint32_t) 0x06) << 11); break;
    case 16: tmpReg |= (((uint32_t) 0x07) << 11); break;
    default: return INVALID;
  } 
  RCC->CFGR = tmpReg;
  return OK;
}



uint16_t  CLK_GetAHBPrescalar(void){
  uint8_t   tmpVal;
  uint16_t  retPrescalar;

  tmpVal = (uint8_t) (((RCC->CFGR) >> 4) & (uint32_t) 0x0F);
  switch (tmpVal){ 
    case 0x08: retPrescalar = 2;   break;
    case 0x09: retPrescalar = 4;   break;
    case 0x0A: retPrescalar = 8;   break;
    case 0x0B: retPrescalar = 16;  break;
    case 0x0C: retPrescalar = 64;  break;
    case 0x0D: retPrescalar = 128; break;
    case 0x0E: retPrescalar = 256; break;
    case 0x0F: retPrescalar = 512; break;
    default: retPrescalar = 1;
  } 
  return retPrescalar;
}


uint8_t   CLK_GetAPB1Prescalar(void){
  uint8_t   tmpVal;
  uint8_t  retPrescalar;

  tmpVal = (uint8_t) (((RCC->CFGR) >> 8) & (uint32_t) 0x07);
  switch (tmpVal){ 
    case 0x04: retPrescalar = 2;   break;
    case 0x05: retPrescalar = 4;   break;
    case 0x06: retPrescalar = 8;   break;
    case 0x07: retPrescalar = 16;  break;
    default: retPrescalar = 1;
  } 
  return retPrescalar;
}



uint8_t CLK_GetAPB2Prescalar(void){
  uint8_t  tmpVal;
  uint8_t  retPrescalar;

  tmpVal = (uint8_t) (((RCC->CFGR) >> 11) & (uint32_t) 0x07);
  switch (tmpVal){ 
    case 0x04: retPrescalar = 2;   break;
    case 0x05: retPrescalar = 4;   break;
    case 0x06: retPrescalar = 8;   break;
    case 0x07: retPrescalar = 16;  break;
    default: retPrescalar = 1;
  } 
  return retPrescalar;
}



} /* namespace */
