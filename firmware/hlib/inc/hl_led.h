/**
 @file hl_led.h
 @brief Providing single-color LEDs control utilities
 
 @author  Bui Van Hieu <bvhieu@cse.hcmut.edu.vn>
 @version 1.0
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

#ifndef __HL_LED_H
#define __HL_LED_H

namespace HLib{

/********************************************************/
void   LED_Start(void);
err_t  LED_Set(uint8_t ledIndex, bool val);

err_t  LED_On(uint8_t ledIndex);
err_t  LED_OnAll();
err_t  LED_Off(uint8_t ledIndex);
err_t  LED_OffAll();
err_t  LED_Toggle(uint8_t ledIndex);
err_t  LED_ToggleAll();

} /* namespace */
#endif /* __HL_LED_H */
