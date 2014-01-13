/**
 @file hl_adc_basis.cpp
 @brief Implementing methods for ADCs in <b> HLib's MBoards </b>
 
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

/**
 @class adc_basis_c
 @brief Providing basis controlling methods for ADC peripheral of an STM32
 @attention This class only implement very basis functions of STM32's ADC.
	          All advanced functions are removed/hided to form an easy-to-use, easy-to-understand class
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
 @brief Turning on an ADC, configuring its operating
 @para adcNum Number of the ADC used
 @para rightAlign Data alignment of conversion result. TRUE: data is right aligned. FALSE: data is left aligned.
 @retval INVALID adcNum parameter is out of range 
 @retval OK the function if finished successfully
*/
err_t adc_basis_c::Start(uint8_t adcNum, bool rightAlign){
  ADC_InitTypeDef  ADC_InitStruct;
	
	#if defined(STM32F100C8_MCU)
    switch (adcNum){
      case 1:  ADCx = ADC1; CLK_Ctrl(CLK_ADC1, true); break;
      default: ADCx = NULL; adcStarted = false; return INVALID;  
    }
  #elif defined(STM32F103RCT6_MCU)
    switch (adcNum){
      case 1:  ADCx = ADC1; CLK_Ctrl(CLK_ADC1, true); break;
      case 2:  ADCx = ADC2; CLK_Ctrl(CLK_ADC2, true); break;
      case 3:  ADCx = ADC3; CLK_Ctrl(CLK_ADC3, true); break;
      default: ADCx = NULL; adcStarted = false; return INVALID;  
    }
  #else
    #error "Unsupported MCU"
  #endif
		
	ADC_Cmd(ADCx, DISABLE);	
		
	ADC_InitStruct.ADC_Mode         = ADC_Mode_Independent;
  ADC_InitStruct.ADC_ScanConvMode = DISABLE;
  ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	if (rightAlign){
		ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
  }
	else{
		ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Left;
	}
	ADC_InitStruct.ADC_NbrOfChannel = 1;
  ADC_Init(ADCx, &ADC_InitStruct);	
	ADC_RegularChannelConfig(ADCx, ADC_Channel_0, 1, ADC_SampleTime_28Cycles5);
	ADC_Cmd(ADCx, ENABLE);
	
	adcStarted = true;
	return OK;
}



/**
 @brief Stop ADC clock
 @retval NOT_START the ADC has not been started before  
 @retval OK the function if finished successfully
*/
err_t adc_basis_c::Shutdown(){
  if (!adcStarted) {return NOT_START;}
	
	ADC_Cmd(ADCx, DISABLE);
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
    return INVALID;
  }
  ADCx = NULL;
  adcStarted = false;
  return OK;
}



/**
 @brief Recalibrating ADC
 @retval NOT_START the ADC has not been started before  
 @retval OK the function if finished successfully
*/
err_t adc_basis_c::Calib(){
	if (!adcStarted) {return NOT_START;}
	/* Enable ADC1 reset calibration register */   
  ADC_ResetCalibration(ADCx);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADCx)){
	}
  /* Start ADC1 calibration */
  ADC_StartCalibration(ADCx);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADCx)){
	}
	return OK;
}



/**
 @brief Set ADC input channel
 @param channel The channel will be used for ADC conversion
 @retval NOT_START the ADC has not been started before  
 @retval OK the function if finished successfully
*/
err_t adc_basis_c::SetChannel(uint8_t channel){
  if (!adcStarted) {return NOT_START;}
	switch (channel){
		case 0: 	ADC_RegularChannelConfig(ADCx, ADC_Channel_0,  1, ADC_SampleTime_28Cycles5); break;
    case 1: 	ADC_RegularChannelConfig(ADCx, ADC_Channel_1,  1, ADC_SampleTime_28Cycles5); break;
		case 2: 	ADC_RegularChannelConfig(ADCx, ADC_Channel_2,  1, ADC_SampleTime_28Cycles5); break;
		case 3: 	ADC_RegularChannelConfig(ADCx, ADC_Channel_3,  1, ADC_SampleTime_28Cycles5); break;
		case 4: 	ADC_RegularChannelConfig(ADCx, ADC_Channel_4,  1, ADC_SampleTime_28Cycles5); break;
		case 5: 	ADC_RegularChannelConfig(ADCx, ADC_Channel_5,  1, ADC_SampleTime_28Cycles5); break;
		case 6: 	ADC_RegularChannelConfig(ADCx, ADC_Channel_6,  1, ADC_SampleTime_28Cycles5); break;
		case 7: 	ADC_RegularChannelConfig(ADCx, ADC_Channel_7,  1, ADC_SampleTime_28Cycles5); break;
		case 8: 	ADC_RegularChannelConfig(ADCx, ADC_Channel_8,  1, ADC_SampleTime_28Cycles5); break;
		case 9: 	ADC_RegularChannelConfig(ADCx, ADC_Channel_9,  1, ADC_SampleTime_28Cycles5); break;
		case 10: 	ADC_RegularChannelConfig(ADCx, ADC_Channel_10, 1, ADC_SampleTime_28Cycles5); break;
		case 11: 	ADC_RegularChannelConfig(ADCx, ADC_Channel_11, 1, ADC_SampleTime_28Cycles5); break;
		case 12: 	ADC_RegularChannelConfig(ADCx, ADC_Channel_12, 1, ADC_SampleTime_28Cycles5); break;
		case 13: 	ADC_RegularChannelConfig(ADCx, ADC_Channel_13, 1, ADC_SampleTime_28Cycles5); break;
		case 14: 	ADC_RegularChannelConfig(ADCx, ADC_Channel_14, 1, ADC_SampleTime_28Cycles5); break;
		case 15: 	ADC_RegularChannelConfig(ADCx, ADC_Channel_15, 1, ADC_SampleTime_28Cycles5); break;
		case 16: 	ADC_RegularChannelConfig(ADCx, ADC_Channel_16, 1, ADC_SampleTime_28Cycles5); break;
		case 17: 	ADC_RegularChannelConfig(ADCx, ADC_Channel_17, 1, ADC_SampleTime_28Cycles5); break;
    default: return INVALID;
	}
  return OK;
}



/**
 @brief Start ADC conversion
 @retval NOT_START the ADC has not been started before  
 @retval OK the function if finished successfully
*/
err_t adc_basis_c::Trigger(){
	if (!adcStarted) {return NOT_START;}
	ADC_SoftwareStartConvCmd(ADCx, ENABLE);
	return OK;
}


/**
 @brief Checking weather the ADC is busy
 @retval TRUE the ADC is busy
 @retval FALSE the ADC is not busy
*/
bool adc_basis_c::IsBusy(){
	if (!adcStarted) {return false;}
	return !((bool) ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC));
}



/**
 @brief Return the conversion result
 @retval Conversion result
 @attention If the ADC has not been started, the return value is always 0
*/
uint16_t adc_basis_c::GetAdc(){
	if (!adcStarted) {return 0;}
	return ADC_GetConversionValue(ADCx);
}



/**
 @brief Perform ADC converting and get result on a specified channel
 @para channel The channel will be used for ADC conversion
 @para adcVal Address of the memory that will store conversion result
 @retval NOT_START the ADC has not been started before 
 @retval OK the function if finished successfully
*/
err_t adc_basis_c::Read(uint8_t channel, uint16_t* adcVal){
  if (!adcStarted) {return NOT_START;}
	SetChannel(channel);
	return Read(adcVal);
}



/**
 @brief Perform ADC converting and get result on the selected channel
 @para adcVal Address of the memory that will store conversion result
 @retval NOT_START the ADC has not been started before 
 @retval OK the function if finished successfully
*/
err_t adc_basis_c::Read(uint16_t* adcVal){
  if (!adcStarted) {return NOT_START;}
	ADC_ClearFlag(ADCx, ADC_FLAG_EOC); /* redundant, protect itself */
	Trigger();
	while (IsBusy()){
	}
	*adcVal = GetAdc();
	ADC_ClearFlag(ADCx, ADC_FLAG_EOC);
	return OK;
}

} /* namespace */
