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


namespace HLib{
//  GLOBAL VARIABLES  ///////////////
volatile uint8_t optFreeVar; 

// HLib INITIALIZATION  ////////////////
/**
 @brief Start HLib's libraries.
 @return None
*/  
void HLib_Start(void){
	PIN_Start();
	LED_Start();
	LED_OnAll();
}

} /* namespace */


/**
 @brief main function of the program. Implement Setup(), Loop() framework of the HLib library
 @return No meaning
*/
int main(void){
  /* Looping framework */
  HLib::HLib_Start();
  Setup();
  while (1){
    Loop();
  }
}


/** @} */
