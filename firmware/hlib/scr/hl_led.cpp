/**
 @file hl_led.cpp
 @brief Providing single-color LEDs control utilities
 
 @author  Bui Van Hieu <bvhieu@cse.hcmut.edu.vn>
 @version 2.0
 @date 10-12-2013
 
 @copyright
 This project and all its relevant hardware designs, documents, source codes, compiled libraries
 belong to <b> Smart Sensing and Intelligent Controlling Group (SSAIC Group)</b>. 
 You have to comply with <b> Non-Commercial Share-Alike Creative Common License </b> 
 in order to share (copy, distribute, transmit) or remix (modify, reproduce, adapt) these works.\n
 SSAIC Group shall not be held liable for any direct, indirect or consequential damages 
 with respect to any claims arising from the content of hardware, firmware and/or the use 
 made by customers of the coding information contained herein in connection with their products.\n
 You are prohibited from commercializing in any kind that using or basing on these works
 without written permission from SSAIC Group. Please contact ssaic@googlegroups.com for commercializing
 
 @brief Providing controlling function for LEDs of a platform
*/

#include "hlib.h"
namespace HLib{


//////////////////////////////////////////////////
#ifdef PLATFORM_STM32F100_STARTER
  #define NUM_OF_LEDS 2
  const HLib_LL::pin_ll_c  ledsMapTbl[NUM_OF_LEDS] = 
    { HLib_LL::pin_ll_c(CLK_GPIOA, GPIOA, 11), 
      HLib_LL::pin_ll_c(CLK_GPIOA, GPIOA, 12) };               
#elif defined (PLATFORM_MBOARD_ONE)
  #define NUM_OF_LEDS 4  
  const HLib_LL::pin_ll_c ledsMapTbl[NUM_OF_LEDS] = 
    { HLib_LL::pin_ll_c(CLK_GPIOC, GPIOC, 4 ),  HLib_LL::pin_ll_c(CLK_GPIOC, GPIOC, 5 ),
		  HLib_LL::pin_ll_c(CLK_GPIOC, GPIOC, 7 ),  HLib_LL::pin_ll_c(CLK_GPIOC, GPIOC, 9 )
		};
#else
  #error "Unsupported platform"
#endif


/////////////////////////////////////////////////
 
static  HLib_LL::pin_ll_c* ledsMap = (HLib_LL::pin_ll_c*) ledsMapTbl;
static  uint8_t ledsState[NUM_OF_LEDS];

/////////////////////////////////////////////////
/**
 @brief  Start LEDs, turn on all LEDs
 @return None
*/ 
void LED_Start(void){
  uint8_t ledCount;

  for(ledCount=0; ledCount < NUM_OF_LEDS; ledCount++){
    ledsMap[ledCount].SetMode(GPIO, OUT_PUSH_PULL);
    ledsMap[ledCount].OutOne();
		ledsState[ledCount] = 1;
  }
}



/**
 @brief Set state of an LED
 @param ledIndex Index or the LED
 @param val TRUE turn on the LED, FALSE turn off the LED
 @retval INVALID the ledIndex parameter is out of range
 @retval OK function is finished correctly
*/
err_t LED_Set(uint8_t ledIndex, bool val){
  if (ledIndex < NUM_OF_LEDS){
    if (false == val){
      ledsMap[ledIndex].OutOne();
      ledsState[ledIndex] = 0;
    }
    else{
      ledsMap[ledIndex].OutZero();
      ledsState[ledIndex] = 1;
    }
		return OK;
  }
	else{
		return INVALID;
	}
}



/**
 @brief Turn on an LED
 @param ledIndex Index or the LED
 @retval INVALID the ledIndex parameter is out of range
 @retval OK function is finished correctly
*/
err_t LED_On(uint8_t ledIndex){
  if (ledIndex < NUM_OF_LEDS){
    ledsMap[ledIndex].OutOne();
    ledsState[ledIndex] = 1;
		return OK;
  }
	else{
		return INVALID;
	}
}



/**
 @brief Turn on all LEDs
 @retval OK function is finished correctly
*/
err_t LED_OnAll(){
  for (uint8_t ledIndex=0; ledIndex < NUM_OF_LEDS; ledIndex++){
    ledsMap[ledIndex].OutOne();
    ledsState[ledIndex] = 1;
  }
	return OK;
}



/**
 @brief Turn off an LED
 @param ledIndex Index or the LED
 @retval INVALID the ledIndex parameter is out of range
 @retval OK function is finished correctly
*/
err_t LED_Off(uint8_t ledIndex){
  if (ledIndex < NUM_OF_LEDS){
    ledsMap[ledIndex].OutZero();
    ledsState[ledIndex] = 0;
		return OK;
  }
	else{
		return INVALID;
	}
}



/**
 @brief Turn off all LEDs
 @retval OK function is finished correctly
*/
err_t LED_OffAll(){
  for (uint8_t ledIndex=0; ledIndex < NUM_OF_LEDS; ledIndex++){
    ledsMap[ledIndex].OutZero();
    ledsState[ledIndex] = 1;
  }
	return OK;
}



/**
 @brief Toggle state of an LED
 @param ledIndex Index or the LED
 @retval INVALID the ledIndex parameter is out of range
 @retval OK function is finished correctly
*/
err_t LED_Toggle(uint8_t ledIndex){
  if (ledIndex < NUM_OF_LEDS){
    if (1 == ledsState[ledIndex]){
      ledsMap[ledIndex].OutZero();
      ledsState[ledIndex] = 0;
    }
    else{
      ledsMap[ledIndex].OutOne();
      ledsState[ledIndex] = 1;
    }
		return OK;
  }
	else{
		return INVALID;
	}
}



/**
 @brief Toggle all LEDs
 @retval OK function is finished correctly
*/
err_t LED_ToggleAll(){
  for (uint8_t ledIndex=0; ledIndex < NUM_OF_LEDS; ledIndex++){
		if (1 == ledsState[ledIndex]){
      ledsMap[ledIndex].OutZero();
			ledsState[ledIndex] = 0;
		}
		else{
			ledsMap[ledIndex].OutOne();
			ledsState[ledIndex] = 1;
		}
  }
  return OK;
}


} /* namespace */

