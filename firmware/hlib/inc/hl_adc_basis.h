/**
 @file hl_adc_basis.h
 @brief Declarating methods for ADCs 
 
 @author Bui Van Hieu 
 @version 1.0
 @date 16-1-2014
 
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

#ifndef __HL_ADC_BASIS_H
#define __HL_ADC_BASIS_H

namespace HLib{

/**
 @class adc_basis_c
 @brief Providing basis controlling methods for ADC peripheral of an STM32
 @attention This class only implement very basis functions of STM32's ADC.
	          All advanced functions are removed/hided to form an easy-to-use, easy-to-understand class
*/
class adc_basis_c{
private:
  bool         adcStarted;
  ADC_TypeDef* ADCx;
public:
  adc_basis_c();
  err_t     Start(uint8_t adcNum, bool rightAlign=true);
  err_t     Shutdown();
  
  err_t     Calib();
  err_t     SetChannel(uint8_t channel);
  err_t     Trigger();
  bool      IsBusy();
  uint16_t  GetAdc();
  err_t     Read(uint8_t channel, uint16_t* adcVal);
  err_t     Read(uint16_t* adcVal);
};

} /* namespace */

#endif /* __HL_ADC_BASIS_H */
