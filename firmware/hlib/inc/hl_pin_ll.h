/**
 @file hl_pin_ll.h
 @brief Providing low-level I/O functions for a pin.

 @author  Bui Van Hieu <bvhieu@cse.hcmut.edu.vn>
 @version 1.0
 @date 5-12-2013

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

#ifndef __HL_PIN_LL
#define __HL_PIN_LL


///////////////////////////////////////////////////
namespace HLib_LL {

/**
 @class pin_ll_c
 @brief Low-level PINs class.
 @attention This class is used internal in HLib. Normal users shouldn't touch this
*/
class pin_ll_c {
private:
  HLib::clk_periph_t  clk;  /**< Clock source of GPIO */
  GPIO_TypeDef* port; /**< Port of a I/O pin */
  uint8_t       pin;  /**< Pin number of a I/O pin */
public:
  pin_ll_c(HLib::clk_periph_t clk, GPIO_TypeDef* port, uint8_t pin);  
  HLib::err_t SetMode(HLib::pin_mode_t mode, HLib::pin_type_t type);
  void Release();
  void OutOne();
  void OutZero();
  void OutVal(bool val);
  bool GetInput();
};

} /* namespace HLib__LL */

#endif /* __HL_PIN_LL */
