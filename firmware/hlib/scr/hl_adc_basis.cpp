/**
 @file hl_adc_basis.cpp
 @brief Implementing methods for ADCs in <b> HLib's MBoards </b>
 
 @author Bui Van Hieu 
 @version 1.0
 @date 16-09-2013
 
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
namespace HLib{


///////////////////////////////////////////////////////
/** 
 @brief Construction method
 @return None
*/
adc_basis_c::adc_basis_c(){
  ADCx 				= NULL;
  adcStarted  = false;
}


/**
 @brief Turning on an ADC, configuring its operating, and calibrating 
 @param adcMode Inter-operation of ADCs. 
 The version 1.0 library ignores this parameter and it is set as Independent 
 @param triggerSource The source that trigger conversion
 @param singleConv <b>TRUE</b> stop after finish one conversion./n<b>FALSE</b> start new conversion after finish.
 @param rightAlign <b>TRUE</b> conversing data is aligned right/n<b>FALSE</b>conversing data is aligned left
 @param scanMode <b>TRUE</b>each conversion scan on multi-channels/n<b>FALSE</b> each conversion measures only one channel
 @param numOfScan number of channels are scanned each conversion. This parameter is ignored if scanMode = FALSE
 @retval HL_INVALID some parameters' values are invalid 
 @retval HL_UNSUPPORT some parameters' values are not supported in selected platform
 @retval HL_UNKNOW function reaches some unknown errors 
 @retval HL_OK function is performed OK
*/
err_t adc_basis_c::Start(uint8_t adcNum, bool rightAlign){
    #if defined(STM32F100C8_MCU)
    switch (adcNum){
      case 1:  ADCx = ADC1; break;
      default: ADCx = NULL; adcStarted = false; return HL_INVALID;  
    }
  #elif defined(STM32F103RCT6_MCU)
    switch (adcNum){
      case 1:  ADCx = ADC1; break;
      case 2:  ADCx = ADC2; break;
      case 3:  ADCx = ADC3; break;
      default: ADCx = NULL; adcStarted = false; return HL_INVALID;  
    }
  #else
    #error "Unsupported MCU"
  #endif
	return HL_OK;
}



/**
 @brief Stop ADC clock
 @return HL_OK, HL_INVALID
*/
err_t adc_basis_c::Shutdown(){
  /*ADD CODE HERE */
  if (!adcStarted) {return HL_NOT_START;}
  if (ADC1 == ADCx){
    CLK_Ctrl(CLK_ADC1, false);
  }
  else if (ADC2 == ADCx){
    CLK_Ctrl(CLK_ADC2, false);
  }
  else if (ADC3 == ADCx){
    CLK_Ctrl(CLK_ADC3, false);
  }  
  else{
    return HL_INVALID;
  }
  ADCx = NULL;
  adcStarted = false;
  return HL_OK;
}



/**
 @brief Recalibrating ADC
 @return NONE
*/
err_t adc_basis_c::Calib(){
	return HL_OK;
}


/**
 @brief Set ADC input channel
 @param channel 
 @param
 @return
*/
err_t adc_basis_c::SetChannel(uint8_t channel){
  return HL_OK;
}

} /* namespace */




