/**
 @file hlib.cpp
 Implementing HLib initialize, looping framework
 *
 @author  Bui Van Hieu <bvhieu@cse.hcmut.edu.vn>
 @version 1.0
 @date 01-09-2013
 *
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
leds_c     LEDS;
pins_c     PINS; 
#ifdef PLATFORM_STM32F100_STARTER
  hd44780_c  LCD;
#endif


//  GLOBAL FUNCTIONS  ///////////
extern void Setup(void);
extern void Loop(void);


/////////////////////////////////
int main(void){
  /* Looping framework */
  HLib_Init();
  Setup();
  while (1){
    Loop();
  }
}


// HLib INITIALIZATION  ////////////////
/**
 @brief Initializing HLib's libraries.
 @param None
 @return None
*/  
void HLib_Init(void){
  COM1.Start(9600);
  COM1.Print("WELCOME TO HLib\n");
  #ifdef PLATFORM_STM32F100_STARTER
    LCD.Start();
	LCD.Print("WELCOME TO HLib");
  #endif
}
