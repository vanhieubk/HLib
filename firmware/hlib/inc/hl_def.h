/**
 @file hl_def.h
 @brief Defining common data of HLib firmware 
 
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

#ifndef __HL_DEF_H
#define __HL_DEF_H

#include <stddef.h>
namespace HLib{

/** \addtogroup HLibGlobalDef HLib's global data structure
 @{
*/

//  TYPEDEF  //////////////////////////
/**
 @brief Return value of an HLib's function
*/
typedef enum {
  OK 				  = 0,  /**< Function works well */
  NOT_START 	= 1,  /**< Peripherals have not been started before the function is called */
  INVALID 		= 2,  /**< One or some function's parameters is not valid */
  UNSUPPORT 	= 3,  /**< Function is call with unsupported parameter */
  UNKNOW 		  = 4   /**< Function enters some errors with unknow reasons */
} err_t;


/**
 @brief Available mode of PINs in an MBoard
 @attention Platforms which use STM32F10x MCU such as STM32F100_STARTER, MBoard1
 are only support GPIO and PERIPHERAL modes. The others are reserved for the future
*/
typedef enum{
  GPIO, 		  /**< Pin is connected with the general purpose input/output, used for getting 0/1 input or controlling 0/1 output */
	PERIPHERAL, /**< Pin is connected with a peripheral*/
} pin_mode_t;


/**
 @brief Electrical type of PINs
*/
typedef enum {
  IN_ANALOG, 	   /**< An analog input, used for ADC PERIPHERAL only */
  IN_FLOATING,   /**< A floating input */
  IN_PULL_UP, 	 /**< An input with pull-up resistor */
  IN_PULL_DOWN,  /**< An input with pull-down resistor */
  OUT_ANALOG,    /**< An analog output, used for DAC PERIPHERAL only */
  OUT_PUSH_PULL, /**< A push-pull output */
  OUT_OPEN_DRAIN /**< An open drain output */
} pin_type_t;

} /* namespace */
/** @} */
#endif /* __HL_DEF_H */
