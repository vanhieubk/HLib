namespace HLib{

typedef enum{
  ADC_TRIG_SOURCE_Ext_IT11_TIM8_TRGO =  ((uint32_t)0x000C0000), 
  ADC_TRIG_SOURCE_NONE    = ((uint32_t)0x000E0000) ,
  ADC_TRIG_SOURCE_T1_CC1  = ((uint32_t)0x00000000), 
  ADC_TRIG_SOURCE_T1_CC2  = ((uint32_t)0x00020000) ,
  ADC_TRIG_SOURCE_T1_CC3  = ((uint32_t)0x00040000) ,
  ADC_TRIG_SOURCE_T2_CC2  = ((uint32_t)0x00060000) ,
  ADC_TRIG_SOURCE_T2_CC3  = ((uint32_t)0x00020000) ,
  ADC_TRIG_SOURCE_T3_CC1  = ((uint32_t)0x00000000) ,
  ADC_TRIG_SOURCE_T3_TRGO = ((uint32_t)0x00080000) ,
  ADC_TRIG_SOURCE_T4_CC4  = ((uint32_t)0x000A0000) ,
  ADC_TRIG_SOURCE_T5_CC1  = ((uint32_t)0x000A0000) ,
  ADC_TRIG_SOURCE_T5_CC3  = ((uint32_t)0x000C0000) ,
  ADC_TRIG_SOURCE_T8_CC1  = ((uint32_t)0x00060000) ,
  ADC_TRIG_SOURCE_T8_TRGO = ((uint32_t)0x00080000) 
} adc_trig_source_t;

/**
 @class adc_c
 @brief Providing controlling method for ADC peripheral of a STM32
 @attention
*/

class adc_c{
private:
  bool         adcStarted;
  ADC_TypeDef* ADCx;
public:
  adc_c     ();
  err_t     Start(uint8_t adcNum = 1, bool rightAlign=true);
  err_t     Shutdown();
  
  err_t     Calib();
  err_t     Trigger();
  err_t     Read(uint8_t channel, uint16_t* adcVal);
  err_t     Read(uint16_t* adcVal);
  err_t     SetChannel(uint8_t channel);
  uint16_t  GetAdc();
  bool      IsBusy();
};

} /* namespace */
