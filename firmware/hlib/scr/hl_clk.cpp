#include "hlib.h"

namespace HLib{
	
/***** private functions declaration ********/
void _CLK_APB2Ctrl(uint32_t RCC_APB2Periph, bool enable);
void _CLK_APB1Ctrl(uint32_t RCC_APB2Periph, bool enable);
void _CLK_AHBCtrl(uint32_t  RCC_AHBPeriph,  bool enable);

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
    case CLK_SRAM :   _CLK_AHBCtrl(RCC_AHBPeriph_SRAM, 			mode); break;
    case CLK_FLITF :  _CLK_AHBCtrl(RCC_AHBPeriph_FLITF, 			mode); break;
    case CLK_CRC :    _CLK_AHBCtrl(RCC_AHBPeriph_CRC, 				mode); break;
    #if 0
		case CLK_USB_OTG: _CLK_AHBCtrl(RCC_AHBPeriph_OTG_FS, 		mode); break;
    case CLK_ETH_MAC: _CLK_AHBCtrl(RCC_AHBPeriph_ETH_MAC, 		mode); break;
    case CLK_ETH_TX:  _CLK_AHBCtrl(RCC_AHBPeriph_ETH_MAC_Tx, mode); break;
    case CLK_ETH_RX:  _CLK_AHBCtrl(RCC_AHBPeriph_ETH_MAC_Rx, mode); break;
    case CLK_FSMC:    _CLK_AHBCtrl(RCC_AHBPeriph_FSMC, 			mode); break;
    #endif
		#ifdef STM32F103RCT6_MCU
		case CLK_SDIO:    _CLK_AHBCtrl(RCC_AHBPeriph_SDIO, 			mode); break;
		#endif
	  default: return HL_INVALID;
  }
	return HL_OK;
}

} /* namespace */
