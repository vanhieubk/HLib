/**
 @file hl_util.h
 @brief Declaring utilities 
 
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
#ifndef __HL_UTIL_H
#define __HL_UTIL_H

/** \addtogroup HLibGlobalMac HLib's global macros
 @{
*/

//  DEFINE  ///////////////////////////
#define HL_BitMask(pos) 				(1 <<(pos)) /**< Generate one-bit mask */
#define HL_BitSet(var, pos) 		((var) |= BIT_Mask(pos)) /**< Set one bit at specified position*/
#define HL_BitClear(var, pos) 	((var) &= ~BIT_Mask(pos)) /**< Clear one bit a specified position */

/** @} */

void HL_LoopDelay(uint32_t numLoop);
void HL_NumToStr(uint32_t num, uint8_t radix, char outStr[]);


#endif
