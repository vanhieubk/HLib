/**
 * @file hlib.h
 * Wrapping of all the HLib firmware libraries and global variables/objects
 *
 * @author  Bui Van Hieu <bvhieu@cse.hcmut.edu.vn>
 * @version 1.0
 * @date 01-09-2013
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
 */
 
#ifndef __HLIB_H
#define __HLIB_H

#include "hl_conf.h"

#ifdef PLATFORM_STM32F100_STARTER
  ////  CONFIGURATION of STM32F100 STARTER KIT  ////
  #include "stm32f10x_conf.h"
  #include "hl_hd44780_c.h"
  extern hd44780_c  LCD;
#elif defined (PLATFORM_MBOARD_ONE)
  ////  CONFIGURATION of MBoard1 KIT  ////
  #include "stm32f10x_conf.h"
#else
  #error "You have selected unsupported platform"
#endif /* #ifdef PLATFORM_... */



////  INCLUDE HLib //////////////////
#include "hl_def.h"
#include "hl_util.h"
#include "hl_uart_c.h"
#include "hl_spi_i2s_c.h"
#include "hl_adc_c.h"
#include "hl_pins_c.h"
#include "hl_leds_c.h"


//  GLOBAL VARIABLES  ///////////////
extern volatile uint8_t optFreeVar; /* implement NOP instruction in C/C++ */


//  GLOBAL OBJECTS  ///////////////
extern uart_c     COM1;
extern leds_c     LEDS;
extern pins_c     PINS;
// HLIB FUNCTIONS  ///////////////
void HLib_Init();
#endif /* __HLIB_H */
