/**
 * @file hl_def.h
 * Defining common data of HLib firmware 
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

#ifndef __HL_DEF_H
#define __HL_DEF_H

#include <stddef.h>

//  DEFINE  ///////////////////////////
#define BIT_Mask(pos) (1 <<(pos))
#define BIT_Set(var, pos) (var) |= BIT_Mask(pos)
#define BIT_Clear(var, pos) (var) &= ~BIT_Mask(pos)

//  TYPEDEF  //////////////////////////
typedef enum {
  HL_OK = 0,
  HL_NOT_START = 1,
  HL_INVALID = 2,
  HL_UNSUPPORT = 3,
  HL_UNKNOW = 4
} err_t;

typedef struct {
  GPIO_TypeDef* port;
  uint16_t pin;
} port_pin_t;

#endif /* __HL_DEF_H */
