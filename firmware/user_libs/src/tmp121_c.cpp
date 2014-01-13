/**
 @file tmp121_c.cpp
 @brief Implementing temperature sensor TMP121/TMP123 controlling methods 
 
 @author  
 @version 1.0
 @date 20-10-2013
 
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
#include "tmp121_c.h"

/**
 @brief Construction method. Store information of used SPI and Chip Select pin index 
 @param ctlSpi Pointer to a SPI instance
 @param csPinIndex Pin index of the chip select pin
 @return None
*/
tmp121_c::tmp121_c(HLib::spi_base_c* ctlSpi, uint8_t csPinIndex){
  this->ctlSpi = ctlSpi;
  this->csPinIndex = csPinIndex;
}


/**
 @brief Start SPI and set chip select to appropriate mode/value
 @return HL_OK or error code if the function is performed OK/FAIL
 @attention The function is performed FAIL iff input parameters of the construction function
 are set invalid with the platform
*/
HLib::err_t tmp121_c::Start(void){
  HLib::err_t retCode;

  //MODIFY CODE BELOW
  /*
  if (NULL == ctlSpi){
    return ...;
  }
  retCode = ctlSpi->Start(.......);
  if (retCode != HL_OK){
    return retCode;
  }
  retCode = PIN_SetMode(csPinIndex, ...);
  if (retCode != HL_OK){
    return retCode;
  }
  PIN_OutVal(csPinIndex, ...);
  */
   
  return retCode;
}



/**
 @brief Shutdown SPI and release chip select pin
 @return None
*/
void tmp121_c::Shutdown(void){
  ctlSpi->Shutdown();
  HLib::PIN_Release(csPinIndex);
}



/**
 @brief Read temperature from TMP101/103
 @return Temperature in 0.25 Celcius degree unit. 
 For example, if temperature is 30 degree, return value is 120
*/
int16_t tmp121_c::Read(void){
  uint16_t readVal;
  uint8_t  spiRecv;
  int16_t  readTmp;
  //MODIFY CODE BELOW
  /*
  PIN_OutVal(csPinIndex, ...);
  LoopDelay(0 or ...);
  ctlSpi->SendRecv(0x55, &spiRecv);
  readVal = (0/8 ???) << ((uint16_t) spiRecv);
  ctlSpi->SendRecv(0x55, &spiRecv);
  readVal |= (0/8 ???) << ((uint16_t) spiRecv);
  PIN_OutVal(csPinIndex, ...);
  readTmp = readVal +-* /...
  */
  return readTmp;
}



