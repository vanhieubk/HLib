/**
 @file hl_conf.h
 @brief Configuring used hardware and firmware features 
 
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

#ifndef __HL_CONF_H
#define __HL_CONF_H

/** \addtogroup HLibGlobalMac HLib's global macros 
 @{
*/


/** SELECT YOUR PLATFORM BY UNCOMMENTING. 
HLib supports STM32F100_STARTER and MBoard1 currently */
//#define PLATFORM_STM32F100_STARTER
#define PLATFORM_MBOARD_ONE


/** SELECET YOUR COMPILER BY UNCOMMENTING*/
//#define GNU_COMPILER
#define KEIL_COMPILER
//#define IAR_COMPILER 


#ifdef PLATFORM_STM32F100_STARTER
  #define F100_MCU_LINE
  #define STM32F100C8_MCU /**< Used MCU is STM32F100C8 */
	#if !defined(STM32F10X_LD_VL)
	  #define  STM32F10X_LD_VL
	#endif 
  #define TXD_PIN_INDEX  15
  #define RXD_PIN_INDEX  16

#elif defined(PLATFORM_MBOARD_ONE)
  #define F103_MCU_LINE
	#if !defined(STM32F10X_HD)
	  #define  STM32F10X_HD
	#endif
  #define STM32F103RCT6_MCU /**< Used MCU is STM32F103RCT6 */
  #define TXD_PIN_INDEX  32
  #define RXD_PIN_INDEX  33
#endif

/** @} */
#endif /* __HL_CONF_H */
