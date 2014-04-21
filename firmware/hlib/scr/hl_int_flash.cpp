/**
@file hl_int_flash.cpp
@brief Implementing methods for accessing internal flash memory of STM32 in <b> HLib's MBoards </b>

@author 
@version 1.1
@date 

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

namespace HLib{
////////////////////////////////////////////////////////////
/**
@brief 
@return None
*/
void   int_flash_c::Start(){
  //enable clock
  //config bits
  flashStarted = true;
}


void   int_flash_c::Shutdown(){
  //config bits
  //disable clock
  flashStarted = false;
}

  
err_t  int_flash_c::Erase(uint16_t blockPos, uint16_t blockSize){
  if (!flashStarted) { return NOT_START;}
    /* add your code here */
}



err_t  int_flash_c::Write(uint32_t startAddr, uint8_t writeBuf[], uint32_t writeLen){
  if (!flashStarted) { return NOT_START;}
  /* add your code here */
}



err_t  int_flash_c::Read(uint32_t startAddr, uint8_t readBuf[], uint32_t readLen){
  if (!flashStarted) { return NOT_START;}
    /* add your code here */
}
  
} /* end namespace */

