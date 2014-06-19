/**
 @file hl_pin_ll.cpp
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


#include "hlib.h"
namespace HLib_LL{
	
	
////////////////////////////////////////////
/**
 @brief Construction
 @para clk_periph_t Peripheral clock of the pin.
 @para port The port that the pin belongs to
 @para pin Index of the pin in the port
 @return None
 @attention All the parameter must be set correctly or un-predictable action can happen
*/
pin_ll_c::pin_ll_c(HLib::clk_periph_t clk, GPIO_TypeDef* port, uint8_t pin){
  this->clk   = clk;
  this->port  = port;
  this->pin   = pin;
} 


/**
 @brief Set operating mode of the pin
 @para mode Operating mode of the pin
 @para type Electronic type of the pin
 @retval HLib::INVALID One or some parameters are not valid
 @retval HLib::OK The functions is finished OK
*/
HLib::err_t pin_ll_c::SetMode(HLib::pin_mode_t mode, HLib::pin_type_t type){
  uint32_t configBits;
  uint32_t reg;

	CLK_Ctrl(clk, true);
	if (HLib::GPIO == mode){
		switch (type){
			case HLib::IN_FLOATING:    configBits = 0x04; break;
			case HLib::IN_PULL_UP:     configBits = 0x08; break;
			case HLib::IN_PULL_DOWN:   configBits = 0x08; break;
			case HLib::OUT_PUSH_PULL:  configBits = 0x03; break;
			case HLib::OUT_OPEN_DRAIN: configBits = 0x07; break;
			default: return HLib::INVALID;
		}
	}
	else if (HLib::PERIPHERAL ==mode){
		switch (type){
			case HLib::IN_ANALOG:
			case HLib::OUT_ANALOG:     configBits = 0x00; break;
			case HLib::IN_FLOATING:    configBits = 0x04; break;
			case HLib::IN_PULL_UP:     configBits = 0x08; break;
			case HLib::IN_PULL_DOWN:   configBits = 0x08; break;
			case HLib::OUT_PUSH_PULL:  configBits = 0x0B; break;
			case HLib::OUT_OPEN_DRAIN: configBits = 0x0F; break;
			default: return HLib::INVALID;
		}	
	}
	else{
		return HLib::INVALID;
	}
  /* update register */
  if (pin <8){
    configBits  =  (configBits << (pin*4));
    reg         =  port->CRL;
    reg         &= ~(((uint32_t) 0x0F) << (pin*4));
    reg         |= configBits;
    port->CRL   = reg;
  }
  else if (pin <16){
    configBits  =  (configBits << ((pin-8)*4));
    reg         =  port->CRH;
    reg         &= ~(((uint32_t) 0x0F) << ((pin-8)*4));
    reg         |= configBits;
    port->CRH   = reg;
  }
  else{
    return HLib::INVALID;
  }
  /* config pullup/pulldown resistor */
  if (HLib::IN_PULL_UP == type){
    port->BSRR = HL_BitMask(pin);
  }
  else if (HLib::IN_PULL_DOWN == type){
    port->BRR = HL_BitMask(pin);
  }
	return HLib::OK;
}


/**
 @brief Release the pin (set its mode to input floating)
 @return None
*/
void pin_ll_c::Release(){
  SetMode(HLib::GPIO, HLib::IN_FLOATING);
}



/**
 @brief Set output to 1
 @return None
*/
void pin_ll_c::OutOne(){
  port->BSRR = HL_BitMask(pin);
}



/**
 @brief Set output to 0
 @return None
*/
void pin_ll_c::OutZero(){
  port->BRR = HL_BitMask(pin);
}



/**
 @brief Set specified value for pin's output
 @para val Set value. TRUE: output will be set 1. FALSE: output will be set 0
 @return None
*/
void pin_ll_c::OutVal(bool val){
  if (val){
    OutOne();
  }
  else{
    OutZero();
  }
}



/**
 @brief Get input value of the pin
 @retval TRUE: the pin input is 1
 @retval FALSE: the pin input is 0
*/
bool pin_ll_c::GetInput(){
  return (bool) (port->IDR & HL_BitMask(pin));
}

} /* namespace HLib_LL */
