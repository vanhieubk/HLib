/**
@file hl_int_flash.h
@brief Declaring functions prototype to manipulate internal flash memory of STM32
@author Bui Van Hieu <bvhieu@cse.hcmut.edu.vn>
@version 1.0
@date 14/04/2014
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

/***********************************************************************/
#ifndef __HL_INT_FLASH_H
#define __HL_INT_FLASH_H

namespace HLib{

/**
@class int_flash_c
@brief Providing methods for accessing internal flash memory of STM32
*/
class int_flash_c{
private:
  bool   flashStarted;
public:
  void   Start();
  void   Shutdown();
  err_t  Erase(uint16_t blockPos, uint16_t blockSize);
  err_t  Write(uint32_t startAddr, uint8_t writeBuf[], uint32_t writeLen);
  err_t  Read(uint32_t startAddr, uint8_t readBuf[], uint32_t readLen);
}; /* end class */

} /* end namespace */

#endif /* __HL_CRC_H */

