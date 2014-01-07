/**
 @file tmp121_c.h
 @brief Declaring temperature sensor TMP121/123 controlling methods 
 
 @author  Bui Van Hieu <bvhieu@cse.hcmut.edu.vn>
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

#ifndef __TMP121_C_H
#define __TMP121_C_H

class tmp121_c{
  HLib::spi_base_c*  ctlSpi;
  uint8_t     csPinIndex;
public:
								tmp121_c(HLib::spi_base_c* ctlSpi, uint8_t csPinIndex);
  HLib::err_t   Start(void);
  void     			Shutdown(void);
  int16_t  			Read(void);
};

#endif /* __TMP121_C_H */
