//Not support dual/tripble mode
typedef void (*ISR_ADCCallback)(uint16_t); 
typedef enum {
  ADC_ALTER_TRIG               = (uint32_t)0x00090000, 
  ADC_FAST_INTER1              = (uint32_t)0x00070000,
  ADC_INDEPENDENT             = (uint32_t)0x00000000,
  ADC_INJECT_SIMULT             = (uint32_t)0x00050000,
  ADC_INJECT_SIMULT_FASTINTER1  = (uint32_t)0x00030000,
  ADC_INJEC_SIMULT_SLOWINTER1  = (uint32_t)0x00040000,
  ADC_REG_INJECT_SIMULT         = (uint32_t)0x00010000,
  ADC_REG_SIMULT               = (uint32_t)0x00060000,
  ADC_REG_SIMULT_ALTER_TRIG    = (uint32_t)0x00020000,
  ADC_SLOW_INTER1              = (uint32_t)0x00080000
  } adc_mode_t;	

typedef enum{
   ADC_TRIG_SOURCE_Ext_IT11_TIM8_TRGO =  ((uint32_t)0x000C0000), 
ADC_TRIG_SOURCE_None  = ((uint32_t)0x000E0000) ,
ADC_TRIG_SOURCE_T1_CC1 =  ((uint32_t)0x00000000), 
ADC_TRIG_SOURCE_T1_CC2 =  ((uint32_t)0x00020000) ,
ADC_TRIG_SOURCE_T1_CC3 =  ((uint32_t)0x00040000) ,
ADC_TRIG_SOURCE_T2_CC2 =  ((uint32_t)0x00060000) ,
ADC_TRIG_SOURCE_T2_CC3 =  ((uint32_t)0x00020000) ,
ADC_TRIG_SOURCE_T3_CC1 =  ((uint32_t)0x00000000) ,
ADC_TRIG_SOURCE_T3_TRGO =  ((uint32_t)0x00080000) ,
ADC_TRIG_SOURCE_T4_CC4  = ((uint32_t)0x000A0000) ,
ADC_TRIG_SOURCE_T5_CC1  = ((uint32_t)0x000A0000) ,
ADC_TRIG_SOURCE_T5_CC3  = ((uint32_t)0x000C0000) ,
ADC_TRIG_SOURCE_T8_CC1  = ((uint32_t)0x00060000) ,
ADC_TRIG_SOURCE_T8_TRGO  = ((uint32_t)0x00080000) 
} adc_trig_source_t;

class adc_c{
private:
  uint8_t      adcNum;
  bool         adcStarted;
  ADC_TypeDef* ADCx;
public:
  adc_c     (uint8_t adcNum);
  err_t     Start(adc_mode_t adcMode, uint8_t triggerSource, bool singleConv, bool rightAlign, bool scanMode, uint8_t numOfScan);
  //err_t     Start(uint8_t triggerSource, bool singleConv, bool rightAlign, bool scanMode, uint8_t numOfScan);
  //err_t     Start(bool singleConv, bool rightAlign, bool scanMode, uint8_t numOfScan);
  err_t     Start(); /*adcMode = independence, triggerSource = software, singleConv = true, rightAlign = true, scanMode=false*/
  err_t     Shutdown();
  void      Calib();
  err_t     SetChannel(uint8_t channel);
  err_t     SetChannel(uint8_t channel, uint8_t convOrder);

  void      SetConvMode(bool singleConversion);
  void      TriggerConv();
  bool      ConvComplete();
  uint16_t  Get();
  void      SetWatchdog(uint16_t highThreshold, uint16_t lowThreshold);
  void      SetISR(ISR_ADCCallback cbFunction);
  err_t     AllowInterrupt();
  err_t     DisableInterrupt();
  void      ClearFlag(uint16_t flag);
};

