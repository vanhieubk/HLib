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
/** \addtogroup HLibGlobalDef HLib's global data structure
 @{
*/

//  TYPEDEF  //////////////////////////
/**
 @brief Return value of an HLib's function
*/
typedef enum {
  HL_OK = 0,        /**< Function works well */
  HL_NOT_START = 1, /**< Peripherals have not been started before the function is called */
  HL_INVALID = 2,   /**< One or some function's parameters is not valid */
  HL_UNSUPPORT = 3, /**< Function is call with unsupported parameter */
  HL_UNKNOW = 4     /**< Function enters some errors with unknow reasons */
} err_t;

/**
 @brief Data structure represent port and pin of a STM32 physical pin
*/
typedef struct {
  GPIO_TypeDef* port; /**< Port of a I/O pin */
  uint16_t pin;       /**< Pin number of a I/O pin */
} port_pin_t;

/** @} */
#endif /* __HL_DEF_H */
