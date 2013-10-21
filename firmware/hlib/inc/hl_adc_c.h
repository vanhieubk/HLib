//Not support dual/tripble mode
typedef void (*ISR_ADCCallback)(uint16_t); 
typedef enum {
  AlterTrig               = (uint32_t)0x00090000, 
  FastInterl              = (uint32_t)0x00070000,
  Independent             = (uint32_t)0x00000000,
  InjecSimult             = (uint32_t)0x00050000,
  InjecSimult_FastInterl  = (uint32_t)0x00030000,
  InjecSimult_SlowInterl  = (uint32_t)0x00040000,
  RegInjecSimult          = (uint32_t)0x00010000,
  RegSimult               = (uint32_t)0x00060000,
  RegSimult_AlterTrig     = (uint32_t)0x00020000,
  SlowInterl              = (uint32_t)0x00080000
  } adc_mode_t;	

typedef enum{
 #define  ADC_ExternalTrigConv_Ext_IT11_TIM8_TRGO   ((uint32_t)0x000C0000) 
#define  ADC_ExternalTrigConv_None   ((uint32_t)0x000E0000) 
#define  ADC_ExternalTrigConv_T1_CC1   ((uint32_t)0x00000000) 
#define  ADC_ExternalTrigConv_T1_CC2   ((uint32_t)0x00020000) 
#define  ADC_ExternalTrigConv_T1_CC3   ((uint32_t)0x00040000) 
#define  ADC_ExternalTrigConv_T2_CC2   ((uint32_t)0x00060000) 
#define  ADC_ExternalTrigConv_T2_CC3   ((uint32_t)0x00020000) 
#define  ADC_ExternalTrigConv_T3_CC1   ((uint32_t)0x00000000) 
#define  ADC_ExternalTrigConv_T3_TRGO   ((uint32_t)0x00080000) 
#define  ADC_ExternalTrigConv_T4_CC4   ((uint32_t)0x000A0000) 
#define  ADC_ExternalTrigConv_T5_CC1   ((uint32_t)0x000A0000) 
#define  ADC_ExternalTrigConv_T5_CC3   ((uint32_t)0x000C0000) 
#define  ADC_ExternalTrigConv_T8_CC1   ((uint32_t)0x00060000) 
#define  ADC_ExternalTrigConv_T8_TRGO   ((uint32_t)0x00080000) 


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

