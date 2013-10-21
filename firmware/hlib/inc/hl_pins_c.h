/**
 @file hl_pins_c.h
 @brief Declaring general purpose I/O functions
 
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

#ifndef __HL_PINS_C_H
#define __HL_PINS_C_H

typedef enum{
  GPIO, 		  /**< Pin is connected with the general purpose input/output, used for getting 0/1 input or controlling 0/1 output */
  ADC1_CH_0, 	/**< Pin is connected with channel 0 of ADC0*/ 
  ADC1_CH_1, 	/**< Pin is connected with channel 1 of ADC0*/
  ADC1_CH_2, 	/**< Pin is connected with channel 2 of ADC0*/
  ADC1_CH_3, 	/**< Pin is connected with channel 3 of ADC0*/
  TIM2_CH_1, 	/**< Pin is connected with channel 1 of TIM2*/
  TIM2_CH_2, 	/**< Pin is connected with channel 2 of TIM2*/
  TIM2_CH_3, 	/**< Pin is connected with channel 3 of TIM2*/
  TIM2_CH_4, 	/**< Pin is connected with channel 4 of TIM2*/
  UART2_TXD, 	/**< Pin is connected with TxD of UART2*/
  UART2_RXD, 	/**< Pin is connected with RxD of UART2*/
  SPI1_NSS, 	/**< Pin is connected with NSS of SPI1*/
  SPI1_MISO, 	/**< Pin is connected with MISO of SPI1*/
  SPI1_MOSI, 	/**< Pin is connected with MOSI of SPI1*/
  SPI1_SCK, 	/**< Pin is connected with SCK of SPI1*/
  DAC1_OUT_1, /**< Pin is connected with channel 1 of DAC1*/
  DAC1_OUT_2, /**< Pin is connected with channel 2 of DAC1*/
  I2C1_SCL, 	/**< Pin is connected with SCL of I2C1*/
  I2C1_SDA 		/**< Pin is connected with SDA of I2C1*/
} pin_mode_t;

typedef enum {
  ANALOG_INPUT, 	  /**< An analog input, used for ADC mode */
  FLOATING_INPUT,   /**< An floating input */
  PULL_UP_INPUT, 		/**< An input with pull-up resistor */
  PULL_DOWN_INPUT,  /**< An input with pull-down resistor */
  ANALOG_OUTPUT,    /**< An analog output, used for DAC mode */
  PUSH_PULL_OUTPUT, /**< An push-pull output */
  OPEN_DRAIN_OUTPUT /**< An open drain output */
} pin_type_t;

class pins_c{
public: 
  pins_c(void);
  void  Release(uint8_t pinIndex);
  err_t SetMode(uint8_t pinIndex, pin_mode_t mode, pin_type_t type);
  void  SetOutVal(uint8_t pinIndex, bool val);
  void  SetOutOne(uint8_t pinIndex);
  void  SetOutZero(uint8_t pinIndex);
  bool  GetInput(uint8_t pinIndex);
};

#endif /* __HL_IO_C_H */
