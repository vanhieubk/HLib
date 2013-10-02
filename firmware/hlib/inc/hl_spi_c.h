/**
 * @file hl_spi_c.h
 * Declaring serial communication methods 
 *
 * @author  Bui Van Hieu <bvhieu@cse.hcmut.edu.vn>
 * @version 1.0
 * @date 01-09-2013
 *
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
 
#ifndef __SPI_C_H
#define __SPI_C_H

#include "stm32f10x_conf.h"

class spi_c {
private:
         uint8_t    spiNum;
         bool       spiStarted;
         uint16_t   dummyWord;
         uint8_t    spiDataSize;
         SPI_TypeDef *		SPIx;
public: spi_c(uint8_t uartNum);
public:
  err_t  Start(uint16_t prescaler, uint16_t cpha, uint16_t cpol, uint16_t dataSize,  uint16_t direction, uint16_t mode, uint16_t firstBit, uint16_t crcPoly);
  err_t  Start(uint32_t baudRate);
  err_t  Shutdown();
  err_t  Send(uint8_t  outWord, uint8_t* recvWord);
  err_t  Send(uint16_t outWord, uint16_t recvWord);
  err_t  Send(uint8_t  outWord);
  err_t  Send(uint16_t outWord);
  err_t  Send(uint8_t outStr[], uint8_t recvStr[]);
  err_t  Recv(uint8_t                   


  err_t  Out(uint8_t outNum);
  err_t  Out(uint16_t outNum);
  err_t  Out(uint32_t outNum);
  err_t  Out(uint8_t outBuf[], uint32_t bufLen);

  void  ClearRBuf(void);
  bool   IsRBufEmpty(void);
  uint32_t RBufLen(void);
  err_t  Get(uint8_t* recvByte);
  err_t  Get(uint8_t outBuf[], uint32_t getLen);
};

#endif /*__UART_C_H */
