/**
 @file hlib.cpp
 @brief Implementing HLib initialize, looping framework
 
 @author  Bui Van Hieu <bvhieu@cse.hcmut.edu.vn>
 @version 1.0
 @date 01-09-2013
 
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
*/

#include "hlib.h"

//  GLOBAL VARIABLES  ///////////////
volatile uint8_t optFreeVar; 

//  GLOBAL OBJECTs  //////////////
uart_c     COM1(1); 
#ifdef PLATFORM_STM32F100_STARTER
  hd44780_c  LCD;
#endif


/** \addtogroup HLibGlobalFunc HLib's global functions
 @{
*/

//  GLOBAL FUNCTIONS  ///////////
/**
 @brief User's Setup function initializing program
*/
extern void Setup(void);

/**
 @brief User's Loop function implementing one loop cylcle
*/
extern void Loop(void);


/////////////////////////////////
/**
 @brief main function of the program. Implement Setup(), Loop() framework of the HLib library
 @return No meaning
*/
int main(void){
  /* Looping framework */
  HLib_Start();
  Setup();
  while (1){
    Loop();
  }
}


// HLib INITIALIZATION  ////////////////
/**
 @brief Start HLib's libraries.
 @return None
*/  
void HLib_Start(void){
	GPIO_InitTypeDef  GPIO_InitStruct;
	PIN_Start();
	LED_Start();
	
	/* enable IO of USART1 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	 
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

  COM1.Start(115200);
  COM1.Print("WELCOME TO HLib\n");
  #ifdef PLATFORM_STM32F100_STARTER
    LED_On(0);
    LED_On(1);
    LCD.Start();
  	LCD.Print("WELCOME TO HLib");
  #endif
}

/** @} */
