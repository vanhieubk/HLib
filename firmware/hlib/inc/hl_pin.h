/**
 @file hl_pin.h
 @brief Declaring general purpose I/O functions
 
 @author  Bui Van Hieu <bvhieu@cse.hcmut.edu.vn>
 @version 2.0
 @date 10-12-2013
 
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

#ifndef __HL_PIN_H
#define __HL_PIN_H

namespace HLib{                
/////////////////////////////////////
void  		PIN_Start(void);
void  		PIN_Start(uint8_t numPin, HLib_LL::pin_ll_c pinMap[]);
void  		PIN_Release(uint8_t pinIndex);
err_t 		PIN_SetMode(uint8_t pinIndex, pin_mode_t mode, pin_type_t type);
void  		PIN_OutVal(uint8_t pinIndex, bool val);
void  		PIN_OutOne(uint8_t pinIndex);
void  		PIN_OutZero(uint8_t pinIndex);
bool  		PIN_GetInput(uint8_t pinIndex);
uint8_t   PIN_GetNumPin(void);
HLib_LL::pin_ll_c*    PIN_GetPinMap(void);

} /* namespace */
#endif /* __HL_PIN_H */
