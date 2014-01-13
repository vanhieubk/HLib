/**
 @file hl_spi_base.h
 @brief Declaring SPI/I2S communication methods 
 
 @author  Bui Van Hieu <bvhieu@cse.hcmut.edu.vn>
 @version 1.1
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
*/
 
#ifndef __HL_SPI_BASIS_H
#define __HL_SPI_BASIS_H

#include "stm32f10x_conf.h"
namespace HLib{

typedef enum{
  SPI_PRESCALER_256 = ((uint16_t)0x0038), /**< SPI clock is PCLK divided by 256 */
  SPI_PRESCALER_128 = ((uint16_t)0x0030), /**< SPI clock is PCLK divided by 128 */
  SPI_PRESCALER_64  = ((uint16_t)0x0028), /**< SPI clock is PCLK divided by 64 */
  SPI_PRESCALER_32  = ((uint16_t)0x0020), /**< SPI clock is PCLK divided by 32 */
  SPI_PRESCALER_16  = ((uint16_t)0x0018), /**< SPI clock is PCLK divided by 16 */
  SPI_PRESCALER_8   = ((uint16_t)0x0010), /**< SPI clock is PCLK divided by 8 */  
  SPI_PRESCALER_4   = ((uint16_t)0x0008), /**< SPI clock is PCLK divided by 4 */
  SPI_PRESCALER_2   = ((uint16_t)0x0000)  /**< SPI clock is PCLK divided by 2 */
} spi_prescaler_t;  
  
typedef enum{
  SPI_1LINES_RX      = ((uint16_t)0x8000), /**< SPI works in half-duplex mode as a receiver */
  SPI_1LINES_TX      = ((uint16_t)0xC000), /**< SPI works in half-duplex mode as a transmitter */
  SPI_2LINES_RX_ONLY = ((uint16_t)0x0400), /**< SPI works in full-duplex mode with only receiving is enabled */
  SPI_2LINES_RX_TX   = ((uint16_t)0x0000)  /**< SPI works in full-duplex mode with both receiving and transmitting are enabled */
} spi_direction_t; 

/**
 @class spi_basis_c
 @brief Providing controlling method for SPI peripheral of a STM32
 @attention
 - Only master SPI mode is supported. No slave mode.
 - Only 8-bit data frame mode is supported. No 16-bit data frame mode.
 - DMA has not supported yet
 - Interrupt has not supported yet
*/
class spi_basis_c {
private:
  bool       			spiStarted;
  SPI_TypeDef *		SPIx;
public: 
	spi_basis_c();

  err_t     Start(spi_direction_t direction, uint8_t spiNum = 1, uint16_t prescaler = 32, bool idleHigh = true,
                  bool secondEdge = true, bool firstMSB = true, 
                  bool crcEnable = false, uint16_t crcPoly = 0x1021);
  err_t     Shutdown();
  err_t     Send(uint8_t sendData);
  err_t     Send(uint8_t sendData, uint8_t *recvData);
  err_t     Send(uint8_t sendBuf[], uint16_t bufLen);
  err_t     Send(uint8_t sendBuf[], uint16_t bufLen, uint8_t recvBuf[]); 
  err_t     RecvSafe(uint8_t sendBuf[], uint16_t bufLen, uint8_t recvBuf[]);
  uint16_t  GetCRCPoly();
  err_t     SendCRC();
  uint16_t  GetSendCRC();
  uint16_t  GetRecvCRC();
  err_t     ClearCRC();  
  bool      IsBusy();               
};

} /* namespace */
#endif /*__HL_SPI_BASIS_H */
