/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.h 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_IT_H
#define __STM32F10x_IT_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

void WWDG_IRQHandler(void); 				// Window Watchdog
void PVD_IRQHandler(void); 					// PVD through EXTI Line detect
void TAMPER_IRQHandler(void); 				// Tamper
void RTC_IRQHandler(void); 					// RTC
void FLASH_IRQHandler(void); 				// Flash
void RCC_IRQHandler(void); 					// RCC
void EXTI0_IRQHandler(void); 				// EXTI Line 0
void EXTI1_IRQHandler(void); 				// EXTI Line 1
void EXTI2_IRQHandler(void); 				// EXTI Line 2
void EXTI3_IRQHandler(void); 				// EXTI Line 3
void EXTI4_IRQHandler(void); 				// EXTI Line 4
void DMA1_Channel1_IRQHandler(void); 		// DMA1 Channel 1
void DMA1_Channel2_IRQHandler(void); 		// DMA1 Channel 2
void DMA1_Channel3_IRQHandler(void); 		// DMA1 Channel 3
void DMA1_Channel4_IRQHandler(void); 		// DMA1 Channel 4
void DMA1_Channel5_IRQHandler(void); 		// DMA1 Channel 5
void DMA1_Channel6_IRQHandler(void); 		// DMA1 Channel 6
void DMA1_Channel7_IRQHandler(void); 		// DMA1 Channel 7
void ADC1_IRQHandler(void); 				// ADC1
void EXTI9_5_IRQHandler(void); 				// EXTI Line 9..5
void TIM1_BRK_TIM15_IRQHandler(void); 		// TIM1 Break and TIM15
void TIM1_UP_TIM16_IRQHandler(void); 		// TIM1 Update and TIM16
void TIM1_TRG_COM_TIM17_IRQHandler(void); 	// TIM1 Trigger and Commutation and TIM17
void TIM1_CC_IRQHandler(void); 				// TIM1 Capture Compare
void TIM2_IRQHandler(void); 				// TIM2
void TIM3_IRQHandler(void); 				// TIM3
void I2C1_EV_IRQHandler(void); 				// I2C1 Event
void I2C1_ER_IRQHandler(void); 				// I2C1 Error
void SPI1_IRQHandler(void); 				// SPI1
void USART1_IRQHandler(void); 				// USART1
void USART2_IRQHandler(void); 				// USART2
void EXTI15_10_IRQHandler(void); 			// EXTI Line 15..10
void RTCAlarm_IRQHandler(void); 			// RTC Alarm through EXTI Line
void CEC_IRQHandler(void); 					// HDMI-CEC
void TIM6_DAC_IRQHandler(void); 			// TIM6 and DAC underrun
void TIM7_IRQHandler(void); 				// TIM7
				

#endif /* __STM32F10x_IT_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
