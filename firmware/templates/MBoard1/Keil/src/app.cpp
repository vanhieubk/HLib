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
uint32_t   counter;

HLib::uart_c COM1;
void Setup(void){
	HLib::PIN_SetMode(15, HLib::ALT_FUNC, HLib::PUSH_PULL_OUTPUT);
	HLib::PIN_SetMode(16, HLib::ALT_FUNC, HLib::PULL_UP_INPUT);
	COM1.Start(1, 115200);
  COM1.Print("WELCOME TO HLib\n");
  counter = 0;
}

   
///////////////////////////////////////////////////////////////
void Loop(void){
	uint8_t recvData;
  if (COM1.HasData()){
		COM1.Get(&recvData);
		COM1.Out(recvData);
	}
  /* ADD CODE HERE TO IMPLEMENT YOUR INFINITIVE LOOP  */
}
