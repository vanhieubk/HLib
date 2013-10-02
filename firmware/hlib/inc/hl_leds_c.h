/**
 * @file hl_leds_c.h
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
 */

#ifndef __HL_LEDS_C_H
#define __HL_LEDS_C_H

#ifdef PLATFORM_STM32F100_STARTER
  #define NUM_OF_LEDS 2
#elif defined (PLATFORM_MBOARD_ONE)
  #define NUM_OF_LEDS 1  
#else
  #error "Unsupported platform"
#endif

class leds_c{
private:
  uint8_t ledsState[NUM_OF_LEDS];
public: 
  leds_c(void);
  void  Set(uint8_t ledIndex, bool val);

  void  On(uint8_t ledIndex);
  void  Off(uint8_t ledIndex);
  void  Toggle(uint8_t ledIndex);
};

#endif /* __HL_LEDS_C_H */
