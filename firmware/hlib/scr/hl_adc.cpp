/**
 @file hl_adc.cpp
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
 
 @class adc_c
 @brief Providing controlling method for ADC peripheral of a STM32
 @attention
*/

#ifdef INITIAL_CHECK 
  #define _ADC_CONSTRUCT_CHECK() if (adcNum == NULL) {return HL_INVALID;} 
  #define _ADC_STARTED_CHECK()   if (adcStarted == false) {return HL_NOT_START;} 
#else
  #define _ADC_CONSTRUCT_CHECK()
  #define _ADC_STARTED_CHECK()
#endif

#include "hlib.h"

///////////////////////////////////////////////////////
/** 
 @brief Construction method
 @return None
*/
adc_c::adc_c(uint8_t adcNum){
  #if defined(STM32F100C8_MCU)
    switch (adcNum){
      case 1:  this->adcNum = adcNum; ADCx = ADC1; break;
      default: this->adcNum = 0; ADCx = NULL;  
    }
  #elif defined(STM32F103RCT6_MCU)
    switch (adcNum){
      case 1:  this->adcNum = adcNum; ADCx = ADC1; break;
      case 2:  this->adcNum = adcNum; ADCx = ADC2; break;
      case 3:  this->adcNum = adcNum; ADCx = ADC3; break;
      default: this->adcNum = 0; ADCx = NULL;  
    }
  #else
    #error "Unsupported MCU"
  #endif
  adcStarted    = false;
}

/**
 @brief Turning on an ADC, configuring its operating, and calibrating 
 @param adcMode Inter-operation of ADCs. The revision 1.0 library ignores this parameter and it is set as Independent 
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
err_t adc_c::Start(adc_mode_t adcMode, uint8_t triggerSource, bool singleConv, bool rightAlign, bool scanMode, uint8_t numOfScan){
  return HL_OK;
}
//err_t adc_c::Start(uint8_t triggerSource, bool singleConv, bool rightAlign, bool scanMode, uint8_t numOfScan);
//err_t adc_c::Start(bool singleConv, bool rightAlign, bool scanMode, uint8_t numOfScan);



/**
 @overload
 @brief Turning on an ADC, configuring default mode, and then calibrating.\n
  *Default configuration is: independent mode, software trigger source, single conversion, right alignment, one channel
 @retval HL_INVALID some parameters' values are invalid 
 @retval HL_UNSUPPORT some parameters' values are not supported in selected platform
 @retval HL_UNKNOW function reaches some unknown errors 
 @retval HL_OK function is performed OK
*/
err_t adc_c::Start(){ /*adcMode = independent, triggerSource = software, singleConv = true, rightAlign = true, scanMode=false*/
  
  return HL_OK;
}



/**
 @brief Stop ADC clock
 @return HL_OK, HL_INVALID
*/
err_t adc_c::Shutdown(){
  _ADC_CONSTRUCT_CHECK();
  /*ADD CODE HERE */  
  return HL_OK;
}



/**
 @brief Recalibrating ADC
 @return NONE
*/
void adc_c::Calib(){
  _ADC_CONSTRUCT_CHECK();
}



/**
 @brief Set ADC input channel
 @param channel 
 @param
 @return
*/
err_t adc_c::SetChannel(uint8_t channel){
  return HL_OK;
}



/**
 @brief
 @param
 @param
 @return
*/
err_t adc_c::SetChannel(uint8_t channel, uint8_t convOrder){
  return HL_OK;
}



/**
 @brief
 @param
 @param
 @return
*/
void adc_c::SetConvMode(bool singleConversion){

}







/**
 @brief
 @param
 @param
 @return
*/
uint16_t adc_c::Get(){
  return HL_OK;
}



/**
 @brief
 @param
 @param
 @return
*/
void adc_c::SetWatchdog(uint16_t highThreshold, uint16_t lowThreshold){

}



/**
 @brief
 @param
 @param
 @return
*/
void adc_c::SetISR(ISR_ADCCallback cbFunction){

}



/**
 @brief
 @param
 @param
 @return
*/
err_t adc_c::AllowInterrupt(){
  return HL_OK;
}



/**
 @brief
 @param
 @param
 @return
*/
err_t adc_c::DisableInterrupt(){
  return HL_OK;
}



/**
 @brief
 @param
 @param
 @return
*/
void adc_c::ClearFlag(uint16_t flag){

}



/**
 @brief
 @param
 @param
 @return
*/


