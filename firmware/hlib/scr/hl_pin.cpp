/**
 @file hl_pin.cpp
 @brief Providing I/O functions for all the PINs in a platform

 @author  Bui Van Hieu <bvhieu@cse.hcmut.edu.vn>
 @version 2.0
 @date 10-12-2013

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

 @attention 
 - Current version does not support external trigger interrupt.
 - The library does not support remap feature for the STM32F100 STARTER KIT.
*/
#include "hlib.h"


namespace HLib{


////   STATIC VARIABLEs   ///////////////////////////////////////////////
#ifdef PLATFORM_STM32F100_STARTER
  #define NUM_OF_PIN 23
   const HLib_LL::pin_ll_c  dfl_pinMap[NUM_OF_PIN]= 
    { HLib_LL::pin_ll_c(CLK_GPIOA, GPIOA, 0),   HLib_LL::pin_ll_c(CLK_GPIOA, GPIOA, 1),  /* ADC0 - ADC1 */ 
		  HLib_LL::pin_ll_c(CLK_GPIOA, GPIOA, 2),   HLib_LL::pin_ll_c(CLK_GPIOA, GPIOA, 3),  /* ADC2 - ADC3 */
      HLib_LL::pin_ll_c(CLK_GPIOA, GPIOA, 4),   HLib_LL::pin_ll_c(CLK_GPIOA, GPIOA, 5),  /* NSS  - SCK */
  		HLib_LL::pin_ll_c(CLK_GPIOA, GPIOA, 6),   HLib_LL::pin_ll_c(CLK_GPIOA, GPIOA, 7),  /* MISO - MOSI */
		  HLib_LL::pin_ll_c(CLK_GPIOA, GPIOA, 8),   HLib_LL::pin_ll_c(CLK_GPIOB, GPIOB, 0),  /* RS   - RW  */
  	  HLib_LL::pin_ll_c(CLK_GPIOB, GPIOB, 1),   HLib_LL::pin_ll_c(CLK_GPIOB, GPIOB, 12), /* EN   - D4 */
  	  HLib_LL::pin_ll_c(CLK_GPIOB, GPIOB, 13),  HLib_LL::pin_ll_c(CLK_GPIOB, GPIOB, 14), /* D5   - D6 */
	    HLib_LL::pin_ll_c(CLK_GPIOB, GPIOB, 15),  HLib_LL::pin_ll_c(CLK_GPIOA, GPIOA, 9),  /* D7   - TXD */
  	  HLib_LL::pin_ll_c(CLK_GPIOA, GPIOA, 10),  HLib_LL::pin_ll_c(CLK_GPIOB, GPIOB, 6),  /* RXD  - SCL*/
   		HLib_LL::pin_ll_c(CLK_GPIOB, GPIOB, 7),   HLib_LL::pin_ll_c(CLK_GPIOB, GPIOB, 8),  /* SDA  - PB8*/
  		HLib_LL::pin_ll_c(CLK_GPIOB, GPIOB, 9),	  HLib_LL::pin_ll_c(CLK_GPIOB, GPIOB, 10), /* PB9  - PB10 */
      HLib_LL::pin_ll_c(CLK_GPIOB, GPIOB, 11)										                         /* PB11 */	
    };
		
#elif defined (PLATFORM_MBOARD_ONE)
  #error "Not defined PIN yet"
#else
  #error "Unsupported platform"
#endif

static uint8_t              _numPin = NUM_OF_PIN;
static HLib_LL::pin_ll_c*   _pinMap = (HLib_LL::pin_ll_c *) dfl_pinMap;
///////////////////////////////////////////////////
/** \addtogroup  PIN_Group Setting and controlling PINs 
 @{
*/


/**
 @brief  Start default platform PIN
 @return None
*/
void PIN_Start(void){
  _numPin = NUM_OF_PIN;
  _pinMap = (HLib_LL::pin_ll_c *) dfl_pinMap;
}


/**
 @brief Remap pin map for a customized platform
 @para numPin Number of pins
 @para pinMap Array of pin_t corresponding with the customized platform
 @return None
 @attention pinMap have to be available for later referencing
*/
void  PIN_Start(uint8_t numPin, HLib_LL::pin_ll_c pinMap[]){
	_numPin = numPin;
	_pinMap = pinMap;
}



/**
  @brief Release one pin to input floating state
  @param pinIndex Index of the pin
  @return None
*/
void PIN_Release(uint8_t pinIndex){
  _pinMap[pinIndex].Release();
}



/**
 @brief Set operation mode for one pin\n
 @details The pins in *STM32F100 STARTER KIT* are mapped as below\n
 PIN INDEX | BOARD SIGNAL | 5V TOLERANCE | SUPPORTED MODEs
 :-------: | :----------- | ------------ | :-----------------
 0         | ADC0         |              | ADC1_CH_0/ TIM2_CH_1                
 1         | ADC1         |              | ADC1_CH_1/ TIM2_CH_2                         
 2         | ADC2         |              | ADC1_CH_2/ TIM2_CH_3/ UART2_TXD     
 3         | ADC3         |              | ADC1_CH_3/ TIM2_CH_4/ UART2_RXD     
 4         | NSS/DAC1     |              | DAC1_OUT_1                  
 5         | SCK          |              | SPI1_SCK/ DAC1_OUT_2                  
 6         | MISO         |              | SPI1_MISO                            
 7         | MOSI         |              | SPI1_MOSI    
 8         | RS    				|              | TIM1_CH_1
 9         | RW    				|              | TIM3_CH_3
 10        | EN    				|              | TIM3_CH_4
 11        | D4    				|              | TIM1_BKIN
 12        | D5    				|              | TIM1_CH_1_N
 13        | D6    				|              | TIM1_CH_2_N/ TIM15_CH_1
 14        | D7    				|              | TIM1_CH_3_N/ TIM15_CH_1_N
 15        | TxD    			|              | UART1_TXD/ TIM1_CH_2
 16        | RxD    			|              | UART1_RXD/ TIM1_CH_3
 17        | SCL          |              | I2C1_SCL/ TIM4_CHA_1/ TIM16_                          
 18        | SDA          |              | I2C1_SDA                             
 19        | PB8          |              | (TIM16_CH1)                          
 20        | PB9          |              | (TIM17_CH1)                          
 21        | PB10         |              | (TIM2_CH3)                          
 22        | PB11         |              | (TIM2_CH4)                          
 @param pinIndex Index of the pin
 @param mode Operation mode. Please refer the table pin map for valid configuration
 @param type Type of pin
 @return HL_OK, HL_INVALID
 @attention NEED redefine alternate peripheral functions. Please select type corresponding with selected mode. If you make a wrong
 pin configuration, your system may behave in unpredictable manner. Thereforce, we
 strongly recommend that you check return value of the function and make sure it is HL_OK
 @warning Due to limitation of STM32F1xx families, pin's mode may be overrided if multi-peripherals
 which use same pin are enabled. This library cannot handle these situations. You have to
 ensure that no pin are used by different peripheral at the same time 
*/
err_t PIN_SetMode(uint8_t pinIndex, pin_mode_t mode, pin_type_t type){
	return _pinMap[pinIndex].SetMode(mode, type);
}



/**
  @brief Set output register to a specified value
  @param pinIndex Index of the pin
  @param val TRUE set one, FALSE set zero
  @return None
  @attention The actual value on the pin is also depend on pinMode, pull-up/pull-down resistor.
  Please ensure the pin is set as Output mode and pull-up/pull-down resistor is configured appropriately
*/
void PIN_OutVal(uint8_t pinIndex, bool val){
	_pinMap[pinIndex].OutVal(val);
}



/**
  @brief Set output register to one
  @param pinIndex Index of the pin
  @return None
  @attention The actual value on the pin is also depend on pinMode, pull-up/pull-down resistor.
  Please ensure the pin is set as Output mode and pull-up/pull-down resistor is configured appropriately
*/
void PIN_OutOne(uint8_t pinIndex){
	_pinMap[pinIndex].OutOne();
}


/**
  @brief Set output register to zero
  @param pinIndex Index of the pin
  @return None
  @attention The actual value on the pin is also depend on pinMode, pull-up/pull-down resistor.
  Please ensure the pin is set as Output mode and pull-up/pull-down resistor is configured appropriately
*/
void PIN_OutZero(uint8_t pinIndex){
  _pinMap[pinIndex].OutZero();
}



/**
  @brief Get digital electronic value at one pin
  @param pinIndex Index of the pin
  @retval true pin is 1
  @retval false pin is 0
*/
bool PIN_GetInput(uint8_t pinIndex){
  return _pinMap[pinIndex].GetInput();
}


/**
 @brief Get number of pins in the platform
 @return Number of pins
*/
uint8_t PIN_NumPin(void){
	return _numPin;
}



/**
 @brief Get address of table which map pinIndex to real pin
 @return Pointer to the current used pinMap
*/
HLib_LL::pin_ll_c*    PIN_GetPinMap(void){
  return &(_pinMap[0]);
}

} /* namespace */

/** @}*/
