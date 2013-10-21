/**
 * @file hl_spi_i2s_c.h
 * Declaring SPI/I2S communication methods 
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
 
#ifndef __HL_SPI_I2S_C_H
#define __HL_SPI_I2S_C_H

#include "stm32f10x_conf.h"

typedef enum{
  SPI_PRESCALER_256 = ((uint16_t)0x0038), 
  SPI_PRESCALER_128 = ((uint16_t)0x0030), 
  SPI_PRESCALER_64  = ((uint16_t)0x0028), 
  SPI_PRESCALER_32  = ((uint16_t)0x0020), 
  SPI_PRESCALER_16  = ((uint16_t)0x0018), 
  SPI_PRESCALER_8   = ((uint16_t)0x0010),   
  SPI_PRESCALER_4   = ((uint16_t)0x0008), 
  SPI_PRESCALER_2   = ((uint16_t)0x0000) 
} spi_prescaler_t;  
  
typedef enum{
  SPI_1LINES_RX      = ((uint16_t)0x8000), 
  SPI_1LINES_TX      = ((uint16_t)0xC000), 
  SPI_2LINES_RX_ONLY = ((uint16_t)0x0400), 
  SPI_2LINES_RX_TX   = ((uint16_t)0x0000)
} spi_direction_t; 


class spi_i2s_c {
private:
  uint8_t    spiNum;
  bool       spiStarted;
  SPI_TypeDef *		SPIx;
public: spi_i2s_c(uint8_t uartNum);
public:
  err_t     Start(spi_prescaler_t prescaler, bool idleLevel, bool secondEdge, bool firstBitMSB, spi_direction_t direction, bool crcEnable, uint16_t crcPoly);
  err_t     Start(spi_prescaler_t prescaler, bool idleLevel, bool secondEdge);
  void      Shutdown();
  void      Send(uint8_t sendData);
  void      Send(uint8_t sendBuf[], uint16_t bufLen); 
  void      SendRecv(uint8_t sendData, uint8_t *recvData);
  void      SendRecv(uint8_t sendBuf[], uint8_t recvBuf[], uint16_t bufLen); 
  uint16_t  GetCRCPoly();
  void      SendCRC();
  uint16_t  GetSendCRC();
  uint16_t  GetRecvCRC();
  void      ClearCRC();  
  bool      IsBusy();               
};

#endif /*__HL_SPI_I2S_C_H */
