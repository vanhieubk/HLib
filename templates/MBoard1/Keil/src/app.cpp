/**
 * @file app.cpp
 * @Application wrapper
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

#include "hlib.h"
uint32_t counter;
//////////////////////////////////////////////
void Setup(void){
  counter = 0;
  /* ADD CODE HERE TO INITIALIZE YOUR PROGRAM */
}



///////////////////////////////////////////////////////////////
void Loop(void){
  uint8_t  getChar;
  if (COM1.HasData()){
    getChar = COM1.Get();
  }
  if (0 == (0x1FFFFF & counter++)){
    LEDS.Toggle(0);
    LEDS.Toggle(1);
    COM1.Print("Bui Van Hieu\n");
  }
  /* ADD CODE HERE TO IMPLEMENT YOUR INFINITIVE LOOP  */


}
