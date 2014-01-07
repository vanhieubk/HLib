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
 
#ifndef __HL_SPI_BASE_H
#define __HL_SPI_BASE_H

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


class spi_base_c {
private:
  uint8_t    			spiNum;
  bool       			spiStarted;
  SPI_TypeDef *		SPIx;
public: 
	spi_base_c(uint8_t uartNum);

  err_t     Start(spi_prescaler_t prescaler, bool idleLevel, bool secondEdge, bool firstBitMSB, spi_direction_t direction, bool crcEnable, uint16_t crcPoly);
  err_t     Start(spi_prescaler_t prescaler, bool idleLevel, bool secondEdge);
  void      Shutdown();
  void      Send(uint8_t sendData);
  void      Send(uint8_t sendBuf[], uint16_t bufLen); 
	uint8_t   SendRecv(uint8_t sendData);
  void      SendRecv(uint8_t sendData, uint8_t *recvData);
  void      SendRecv(uint8_t sendBuf[], uint8_t recvBuf[], uint16_t bufLen); 
  uint16_t  GetCRCPoly();
  void      SendCRC();
  uint16_t  GetSendCRC();
  uint16_t  GetRecvCRC();
  void      ClearCRC();  
  bool      IsBusy();               
};

} /* namespace */
#endif /*__HL_SPI_BASE_H */