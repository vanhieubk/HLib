/**
 * @file hl_leds_c.cpp
 * Providing single-color LEDs control utilities for MBoards
 *
 * @author  Bui Van Hieu <bvhieu@cse.hcmut.edu.vn>
 * @version 1.0
 * @date 04-09-2013
 *
 * @copyright
 * This project and all its relevant hardware designs, documents, source codes, compiled libraries
 * belong to <b> Smart Sensing and Intelligent Controlling Group (SSAIC Group)</b>. 
 * You have to comply with <b> Non-Commercial Share-Alike Creative Common License </b> 
 * in order to share (copy, distribute, transmit) or remix (modify, reproduce, adapt) these works.\n
 * SSAIC Group shall not be held liable for any direct, indirect or consequential damages 
 * with respect to any claims arising from the content of hardware, firmware and/or the use 
 * made by customers of the coding information contained herein in connection with their products.\n
 * You are prohibited from commercializing in any kind that using or basing on these works
 * without written permission from SSAIC Group. Please contact ssaic@googlegroups.com for commercializing
 * @attention
 * There should be only one instance of this class to avoid confliction. The instance
 * was initialized by HLib libraray. Thereforce, please do not create an instance of
 * this class.
 */

#include "hlib.h"

#ifdef PLATFORM_STM32F100_STARTER
  const port_pin_t ledsMap[NUM_OF_LEDS] = { {GPIOA, GPIO_Pin_11}, {GPIOA, GPIO_Pin_12} };
#elif defined (PLATFORM_MBOARD_ONE)
  const port_pin_t ledsMap[NUM_OF_LEDS] = { {GPIOC, GPIO_Pin_4 } };
#else
  #error "Unsupported platform"
#endif

/**
  * @brief Construction. Enable clock, set output mode for LEDs' pins
  * @return None
  */ 
leds_c::leds_c(void){
  uint8_t ledCount;
  GPIO_InitTypeDef  GPIO_InitStruct;

  for(ledCount=0; ledCount < NUM_OF_LEDS; ledCount++){
    #ifdef PLATFORM_STM32F100_STARTER
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
      GPIO_InitStruct.GPIO_Pin   = ledsMap[ledCount].pin;
      GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
      GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(ledsMap[ledCount].port, &GPIO_InitStruct);
      GPIO_SetBits(ledsMap[ledCount].port, ledsMap[ledCount].pin);
      ledsState[ledCount] = 1;
	#elif defined (PLATFORM_MBOARD_ONE)
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
      GPIO_InitStruct.GPIO_Pin   = ledsMap[ledCount].pin;
      GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
      GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(ledsMap[ledCount].port, &GPIO_InitStruct);
      GPIO_SetBits(ledsMap[ledCount].port, ledsMap[ledCount].pin);
      ledsState[ledCount] = 1;
    #else
      #error "Unsupported platform"
    #endif
  }
}



/**
  * @brief Set state of an LED
  * @param ledIndex Index or the LED
  * @param val TRUE turn on the LED, FALSE turn off the LED
  * @return None
  */
void leds_c::Set(uint8_t ledIndex, bool val){
  if (ledIndex < NUM_OF_LEDS){
    if (false == val){
      GPIO_ResetBits(ledsMap[ledIndex].port, ledsMap[ledIndex].pin);
      ledsState[ledIndex] = 0;
    }
    else{
      GPIO_SetBits(ledsMap[ledIndex].port, ledsMap[ledIndex].pin);
      ledsState[ledIndex] = 1;
    }
  }
}



/**
  * @brief Turn on an LED
  * @param ledIndex Index or the LED
  * @return None
  */
void leds_c::On(uint8_t ledIndex){
  if (ledIndex < NUM_OF_LEDS){
    GPIO_SetBits(ledsMap[ledIndex].port, ledsMap[ledIndex].pin);
    ledsState[ledIndex] = 1;
  }
}



/**
  * @brief Turn off an LED
  * @param ledIndex Index or the LED
  * @return None
  */
void leds_c::Off(uint8_t ledIndex){
  if (ledIndex < NUM_OF_LEDS){
    GPIO_ResetBits(ledsMap[ledIndex].port, ledsMap[ledIndex].pin);
    ledsState[ledIndex] = 0;
  }
}



/**
  * @brief Toggle state of an LED
  * @param ledIndex Index or the LED
  * @return None
  */
void leds_c::Toggle(uint8_t ledIndex){
  if (ledIndex < NUM_OF_LEDS){
    if (1 == ledsState[ledIndex]){
      GPIO_ResetBits(ledsMap[ledIndex].port, ledsMap[ledIndex].pin);
      ledsState[ledIndex] = 0;
    }
    else{
      GPIO_SetBits(ledsMap[ledIndex].port, ledsMap[ledIndex].pin);
      ledsState[ledIndex] = 1;
    }
  }
}
