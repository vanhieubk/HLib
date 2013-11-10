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
#include "tlc5971_c.h"

uint32_t counter;
spi_i2s_c spi1(1);
tlc5971_c TLC5971(&spi1);

void Setup(void){
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable SPI and GPIO clocks */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE);

/* Configure SPI pins: SCK, MISO and MOSI */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  counter = 0;
  /* ADD CODE HERE TO INITIALIZE YOUR PROGRAM */
  spi1.Start(SPI_PRESCALER_64, false, false);
  TLC5971.Send();
  HL_LoopDelay(1000000);
  TLC5971.Send();
  HL_LoopDelay(1000000);
}

   
///////////////////////////////////////////////////////////////
void Loop(void){
  uint8_t  getChar;
  uint8_t  fc;
  
  fc = TLC5971.CreateFc(true, false, false, true, false);
  TLC5971.SetFc(fc);
  TLC5971.Send();
  //HL_LoopDelay(1000000);
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
