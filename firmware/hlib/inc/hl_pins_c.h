/**
 * @file hl_pins_c.h
 * Declaring general purpose I/O functions
 *
 * @author  Bui Van Hieu <bvhieu@cse.hcmut.edu.vn>
 * @version 1.0
 * @date 01-09-2013
 *
 * @copyright
 * @copyright
 * This project and all its relevant hardware designs, documents, source codes, compiled libraries
 * belong to <b> Smart Sensing and Intelligent Controlling Group (SSAIC Group)</b>. 
 * You have to comply with <b> Non-Commercial Share-Alike Creative Common License </b> 
 * in order to share (copy, distribute, transmit) or remix (modify, reproduce, adapt) these works.\n
 * SSAIC Group shall not be held liable for any direct, indirect or consequential damages 
 * with respect to any claims arising from the content of hardware, firmware and/or the use 
 * made by customers of the coding information contained herein in connection with their products.\n
 * You are prohibited from commercializing in any kind that using or basing on these works
 * without written permission from SSAIC Group. Please contact ssaic@googlegroups.com for commercializing
 */

#ifndef __HL_PINS_C_H
#define __HL_PINS_C_H

typedef enum{
  GPIO, 
  ADC1_CH_0, ADC1_CH_1, ADC1_CH_2, ADC1_CH_3,
  TIM2_CH_1, TIM2_CH_2, TIM2_CH_3, TIM2_CH_4,
  UART2_TXD, UART2_RXD,
  SPI1_NSS, SPI1_MISO, SPI1_MOSI, SPI1_SCK,
  DAC_OUT_1, DAC_OUT_2,
  I2C1_SCL, I2C1_SDA
} pin_mode_t;

typedef enum {
  ANALOG_INPUT, FLOATING_INPUT, PULL_UP_INPUT, PULL_DOWN_INPUT,
  ANALOG_OUTPUT, PUSH_PULL_OUTPUT, OPEN_DRAIN_OUTPUT 
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
