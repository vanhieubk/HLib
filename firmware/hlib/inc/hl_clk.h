#ifndef __HL_CLK_H
#define __HL_CLK_H

namespace HLib{

/*******************************************************/
typedef enum{
	CLK_GPIOA, 	CLK_GPIOB, 	CLK_GPIOC, 	CLK_GPIOD, 	CLK_GPIOE, 	CLK_GPIOF,
	CLK_GPIOG,  CLK_TIM1, 	CLK_TIM2, 	CLK_TIM3, 	CLK_TIM4, 	CLK_TIM5, 
	CLK_TIM6, 	CLK_TIM7, 	CLK_TIM8,		CLK_TIM9, 	CLK_TIM10, 	CLK_TIM11,
	CLK_TIM12, 	CLK_TIM13, 	CLK_TIM14,  CLK_TIM15,  CLK_TIM16,  CLK_TIM17, 
	CLK_UART1,  CLK_UART2,  CLK_UART3,  CLK_UART4,  CLK_UART5,  CLK_SPI1, 
	CLK_SPI2,   CLK_SPI3,   CLK_I2C1, 	CLK_I2C2,   CLK_ADC1,   CLK_ADC2,
	CLK_ADC3,   CLK_DAC,    CLK_CAN1,   CLK_WWDG, 	CLK_SDIO,		CLK_BKP,
	CLK_PWR, 		CLK_CEC,    CLK_CRC,    CLK_DMA1,   CLK_DMA2,   CLK_FLITF,
  CLK_SRAM,   CLK_FSMC,   CLK_AFIO,   CLK_RTC,
	CLK_USB_DEV, 
	CLK_USB_OTG, 
	CLK_ETH_MAC, 
	CLK_ETH_TX, 
	CLK_ETH_RX 
} clk_periph_t;
	

/********************************/
err_t     CLK_Ctrl(clk_periph_t peripheralClk, bool isEnable);
uint32_t  CLK_GetSysFreq(void);
uint32_t  CLK_GetAHBFreq(void);
uint32_t  CLK_GetAPB1Freq(void);
uint32_t  CLK_GetAPB2Freq(void);

uint16_t  CLK_GetAHBPrescalar(void);
err_t     CLK_SetAHBPrescalar(uint16_t prescalar);
uint8_t   CLK_GetAPB1Prescalar(void);
err_t     CLK_SetAPB1Prescalar(uint8_t prescalar);
uint8_t   CLK_GetAPB2Prescalar(void);
err_t     CLK_SetAPB2Prescalar(uint8_t prescalar);

} /* namespace */

#endif /* __HL_CLK_H */
