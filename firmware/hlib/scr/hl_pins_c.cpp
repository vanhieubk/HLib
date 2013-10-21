/**
 @file hl_pins_c.cpp
 @brief Providing general purpose I/O functions
 @attention 
 Current version does not support external trigger interrupt.\n
 The library does not support remap feature for the STM32F100 STARTER KIT.\n
 @author  Bui Van Hieu <bvhieu@cse.hcmut.edu.vn>
 @version 1.0
 @date 01-09-2013

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

///////////////////////////////////////////////////
#ifdef PLATFORM_STM32F100_STARTER
  #define IO_NUM_OF_PIN 14
  const port_pin_t pinMap[IO_NUM_OF_PIN] = 
    { {GPIOA, GPIO_Pin_0},  {GPIOA, GPIO_Pin_1},  {GPIOA, GPIO_Pin_2},  {GPIOA, GPIO_Pin_3},
      {GPIOA, GPIO_Pin_4},  {GPIOA, GPIO_Pin_5},  {GPIOA, GPIO_Pin_6},  {GPIOA, GPIO_Pin_7},
      {GPIOB, GPIO_Pin_6},  {GPIOB, GPIO_Pin_7},
      {GPIOB, GPIO_Pin_8},  {GPIOB, GPIO_Pin_9},  {GPIOB, GPIO_Pin_10}, {GPIOB, GPIO_Pin_11},
    };
#elif defined (PLATFORM_MBOARD_ONE)
  #define IO_NUM_OF_PIN 14
  const port_pin_t pinMap[IO_NUM_OF_PIN] = 
    { {GPIOA, GPIO_Pin_0},  {GPIOA, GPIO_Pin_1},  {GPIOA, GPIO_Pin_2},  {GPIOA, GPIO_Pin_3},
      {GPIOA, GPIO_Pin_4},  {GPIOA, GPIO_Pin_5},  {GPIOA, GPIO_Pin_6},  {GPIOA, GPIO_Pin_7},
      {GPIOB, GPIO_Pin_6},  {GPIOB, GPIO_Pin_7},
      {GPIOB, GPIO_Pin_8},  {GPIOB, GPIO_Pin_9},  {GPIOB, GPIO_Pin_10}, {GPIOB, GPIO_Pin_11},
    };
#else
  #error "Unsupported platform"
#endif

///////////////////////////////////////////////////


///////////////////////////////////////////////////
/**
 @brief Construction function. Enable GPIO clocks
 @return None
*/
pins_c::pins_c(){
  #ifdef PLATFORM_STM32F100_STARTER
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  #elif defined (PLATFORM_MBOARD_ONE)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  #else
    #error "Unsupported platform"
  #endif
}


/**
  @brief Release one pin to input floating state
  @param pinIndex Index of the pin
  @return None
*/
void pins_c::Release(uint8_t pinIndex){
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  #if defined(PLATFORM_STM32F100_STARTER) || defined(PLATFORM_MBOARD_ONE)
    GPIO_InitStruct.GPIO_Pin  = pinMap[pinIndex].pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(pinMap[pinIndex].port, &GPIO_InitStruct);
  #else
    #error "Unsupported platform"
  #endif
}



/**
 @brief Set operation mode for one pin\n
 @details The pins in *STM32F100 STARTER KIT* are mapped as below\n
 PIN NUMBER | BOARD SIGNAL | 5V TOLERANCE | SUPPORTED MODEs
 :--------: | :----------- | ------------ | :-----------------
 0          | ADC0         |              | ADC1_CH_0/ TIM2_CH_1/ GPIO                
 1          | ADC1         |              | ADC1_CH_1/ TIM2_CH_2/ GPIO                         
 2          | ADC2         |              | ADC1_CH_2/ TIM2_CH_3/ UART2_TXD/ GPIO     
 3          | ADC3         |              | ADC1_CH_3/ TIM2_CH_4/ UART2_RXD/ GPIO     
 4          | NSS/DAC1     |              | DAC1_OUT_1/ GPIO                  
 5          | SCK          |              | SPI1_SCK/ DAC1_OUT_2/ GPIO                  
 6          | MISO         |              | SPI1_MISO/ GPIO                            
 7          | MOSI         |              | SPI1_MOSI/ GPIO                            
 8          | SCL          |              | I2C1_SCL/ GPIO                             
 9          | SDA          |              | I2C1_SDA/ GPIO                             
 10         | PB8          |              | (TIM16_CH1)/ GPIO                          
 11         | PB9          |              | (TIM17_CH1)/ GPIO                          
 12         | PB10         |              | (TIM2_CH3)/ GPIO                          
 13         | PB11         |              | (TIM2_CH4)/ GPIO                          
 @param pinIndex Index of the pin
 @param mode Operation mode. Please refer the table pin map for valid configuration
 @param type Type of pin
 @return HL_OK, HL_INVALID
 @attention Please select type corresponding with selected mode. If you make a wrong
 pin configuration, your system may behave in unpredictable manner. Thereforce, we
 strongly recommend that you check return value of the function and make sure it is HL_OK
 @warning Due to limitation of STM32F1xx families, pin's mode may be overrided if multi-peripherals
 which use same pin are enabled. This library cannot handle these situations. You have to
 ensure that no pin are used by different peripheral at the same time 
*/
err_t pins_c::SetMode(uint8_t pinIndex, pin_mode_t mode, pin_type_t type){
  GPIO_InitTypeDef  GPIO_InitStruct;
  bool combineOk = true;
  bool assignOk = false;
  
  #ifdef PLATFORM_STM32F100_STARTER
    /* check valid mode assignment */
    if (GPIO == mode){
      assignOk = true;
    }
    else{
      switch (pinIndex){ 
        case 0: if ((ADC1_CH_0 == mode) || (TIM2_CH_1 == mode)) {assignOk = true;} break;
        case 1: if ((ADC1_CH_1 == mode) || (TIM2_CH_2 == mode)) {assignOk = true;} break;
        case 2: if ((ADC1_CH_2 == mode) || (TIM2_CH_3 == mode) || (UART2_TXD == mode)) {assignOk = true;} break;
        case 3: if ((ADC1_CH_3 == mode) || (TIM2_CH_4 == mode) || (UART2_RXD == mode)) {assignOk = true;} break;
        case 4: if ( DAC_OUT_1 == mode) {assignOk = true;} break;
        case 5: if ((SPI1_SCK  == mode) || (DAC_OUT_2 == mode)) {assignOk = true;} break;
        case 6: if ( SPI1_MISO == mode) {assignOk = true;}  break;
        case 7: if ( SPI1_MOSI == mode) {assignOk = true;}  break;
        case 8: if ( I2C1_SCL  == mode) {assignOk = true;}  break;
        case 9: if ( I2C1_SDA  == mode) {assignOk = true;}  break;
      }
    }

    /* detect invalid combination */
    if (GPIO == mode){
      if ((ANALOG_INPUT == type) || (ANALOG_OUTPUT == type)){
        combineOk = false;;
      }
    }
    else if ((ADC1_CH_0 == mode) || (ADC1_CH_1 == mode) ||(ADC1_CH_2 == mode) ||(ADC1_CH_3 == mode)){
      if (ANALOG_INPUT != type){
        combineOk = false;;
      }
    }
    else if ((DAC_OUT_1 == mode) ||(DAC_OUT_2 == mode)){
      if (ANALOG_OUTPUT != type){
        combineOk = false;;
      }
    }
    else if ((UART2_RXD == mode) || (SPI1_MISO == mode)){
      if ((FLOATING_INPUT != type) && (PULL_UP_INPUT != type) && (PULL_DOWN_INPUT != type)){
        combineOk = false;;
      }
    }
    else if (  (TIM2_CH_1 == mode) || (TIM2_CH_2 == mode) 
             ||(TIM2_CH_3 == mode) || (TIM2_CH_4 == mode) 
             ||(UART2_TXD == mode) || (SPI1_SCK  == mode) || (SPI1_MOSI == mode)){
      if ((PUSH_PULL_OUTPUT != type) && (OPEN_DRAIN_OUTPUT != type)){
        combineOk = false;;
      }
    }
    else if ((I2C1_SCL == mode) ||(I2C1_SDA == mode)){
      if (OPEN_DRAIN_OUTPUT != type){
        combineOk = false;;
      }
    }
    else{
      combineOk = false;; /* invalid mode */
    }

    /* set pin mode if inputs are valid */
    if ((assignOk == true) && (combineOk == true)){
      GPIO_InitStruct.GPIO_Pin   = pinMap[pinIndex].pin;
      GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
      switch (type){
        case ANALOG_INPUT:
        case ANALOG_OUTPUT:     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN; break;
        case FLOATING_INPUT:    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; break;
        case PULL_UP_INPUT:     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; break;
        case PULL_DOWN_INPUT:   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; break;
        case PUSH_PULL_OUTPUT:  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; break;
        case OPEN_DRAIN_OUTPUT: GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
      }
      GPIO_Init(pinMap[pinIndex].port, &GPIO_InitStruct);
      return HL_OK;
    }
    else{
      return HL_INVALID;
    }
  #elif defined(PLATFORM_MBOARD_ONE)
    #warning "Add code processig MBoard1 pin init"
	return HL_OK;
  #else
    #error "Unsupported platform"
  #endif
}



/**
  @brief Set output register to a specified value
  @param pinIndex Index of the pin
  @param val TRUE set one, FALSE set zero
  @return None
  @attention The actual value on the pin is also depend on pinMode, pull-up/pull-down resistor.
  Please ensure the pin is set as Output mode and pull-up/pull-down resistor is configured appropriately
*/
void pins_c::SetOutVal(uint8_t pinIndex, bool val){
  if (0 == val){
    GPIO_ResetBits(pinMap[pinIndex].port, pinMap[pinIndex].pin);
  }
  else{
    GPIO_SetBits(pinMap[pinIndex].port, pinMap[pinIndex].pin);
  }
}



/**
  @brief Set output register to one
  @param pinIndex Index of the pin
  @return None
  @attention The actual value on the pin is also depend on pinMode, pull-up/pull-down resistor.
  Please ensure the pin is set as Output mode and pull-up/pull-down resistor is configured appropriately
*/
void pins_c::SetOutOne(uint8_t pinIndex){
  GPIO_SetBits(pinMap[pinIndex].port, pinMap[pinIndex].pin);
}


/**
  @brief Set output register to zero
  @param pinIndex Index of the pin
  @return None
  @attention The actual value on the pin is also depend on pinMode, pull-up/pull-down resistor.
  Please ensure the pin is set as Output mode and pull-up/pull-down resistor is configured appropriately
*/
void pins_c::SetOutZero(uint8_t pinIndex){
  GPIO_ResetBits(pinMap[pinIndex].port, pinMap[pinIndex].pin);
}



/**
  @brief Get digital electronic value at one pin
  @param pinIndex Index of the pin
  @retval true pin is 1
  @retval false pin is 0
*/
bool pins_c::GetInput(uint8_t pinIndex){
  return GPIO_ReadInputDataBit(pinMap[pinIndex].port, pinMap[pinIndex].pin);
}
