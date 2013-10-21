/**
 @file hl_util.cpp
 Providing utilities to make program easier

 @author  Bui Van Hieu <bvhieu@cse.hcmut.edu.vn>
 @version 1.0
 @date 10-09-2013

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

//  Volatile variables  ////////////////////////
volatile  uint32_t loopDelayCounter;

///////////////////////////////////////////////
/**
 @brief Peforming delay by a finitive loop
 @param numLoop Delay time
 @return None
 @attention Real delay time depend on speed of used MCU.
*/
void HL_LoopDelay(uint32_t numLoop){
  for (loopDelayCounter=0; loopDelayCounter<numLoop; loopDelayCounter++){
    /* TRICK: use volatile loopDelayCounter to prevent Compiler Optimization */
  }
}


/**
 @brief Convert an unsigned interger to string 
 @param num Converted number
 @radix Only support 2, 8, 10, 16
 @outStr Converting result
 @return None
*/
void HL_NumToStr(uint32_t num, uint8_t radix, char outStr[]){
  uint32_t quotient, remainder;
  char     storageStr[33];
  int      count, index; //must int type, uint is incorrect

  remainder = num;
  count     = 0;
  do{
    quotient    = remainder % radix;
    remainder   = remainder / radix;
    if (quotient < 10){
      storageStr[count++]  = 0x30 | ((uint8_t) quotient);
    }
    else{
      storageStr[count++]  = (uint8_t) (quotient+55);
    }
  }while (remainder !=0);
  for(index=0; index<count; index++){
    outStr[index] = storageStr[count-index-1];
  }
  outStr[index] = '\0';
}
