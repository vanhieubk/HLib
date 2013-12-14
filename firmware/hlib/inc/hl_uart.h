/**
 @file hl_uart.h
 @brief Declaring serial communication methods
 
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

#ifndef __HL_UART_H
#define __HL_UART_H

/**
 @class uart_c
 @brief Providing controlling method for USART peripheral of STM32
 @attention
 - The USART1 is reserved for HLib as COM1. Please do not create an instance of this class with comPort=1
 - This library always enables receiving feature.
 - DMA transfer/receiver has not been supported\n.
 - Current version only supports polling receiving. Interrupt receiving will be implemented in next version
 - This library neither support 9-bit data word nor parity check. If you need this feature, please contact us.
*/
class uart_c {
private:
  uint8_t    uartNum;
  bool       uartStarted;
  USART_TypeDef *		UARTx;
public:   uart_c(uint8_t uartNum);
  err_t   Start(uint32_t baudRate, uint16_t stopBit);
  err_t   Start(uint32_t baudRate);
  err_t   Shutdown(void);
  err_t   Print(char outChar);
  err_t   Print(char* outStr);
  err_t   Print(uint32_t outNum, uint8_t radix);
  err_t   Print(uint32_t outNum);
  err_t   Print(int32_t outNum);
          
  err_t   Out(uint8_t outNum);
  err_t   Out(uint16_t outNum);
  err_t   Out(uint32_t outNum);
  err_t   Out(uint8_t outBuf[], uint32_t bufLen);

  uint8_t Get(void);
  bool    HasData(void);
};

#endif /*__HL_UART_H */
