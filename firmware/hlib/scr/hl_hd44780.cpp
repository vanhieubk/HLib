/**
 * @file hl_hd44780.cpp
 * Providing functions controlling hd44780-based LCDs
 *
 * @author  Bui Van Hieu <bvhieu@cse.hcmut.edu.vn>
 * @version 1.0
 * @date 12-09-2013
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

/**
  * @brief Construction function. Do nothing
  * @return None
  */
hd44780_c::hd44780_c(void){
}


/** @brief Initialize all HD44780 control pins, set default mode, and return home
  * @retval None
  */
void hd44780_c::Start(void){
  GPIO_InitTypeDef GPIO_InitStructure;
  //init EN pin
	RCC_APB2PeriphClockCmd(HD44780_EN_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin   = HD44780_EN_PIN;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(HD44780_EN_PORT, &GPIO_InitStructure);
  GPIO_ResetBits(HD44780_EN_PORT, HD44780_EN_PIN);
  //init RS pin
  RCC_APB2PeriphClockCmd(HD44780_RS_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin   = HD44780_RS_PIN;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(HD44780_RS_PORT, &GPIO_InitStructure);
  //init RW pin
  RCC_APB2PeriphClockCmd(HD44780_RW_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin   = HD44780_RW_PIN;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(HD44780_RW_PORT, &GPIO_InitStructure);
  //init DATA pins
  RCC_APB2PeriphClockCmd(HD44780_DATA_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin   = HD44780_DATA_PIN_4| HD44780_DATA_PIN_5| HD44780_DATA_PIN_6| HD44780_DATA_PIN_7;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(HD44780_DATA_PORT, &GPIO_InitStructure);

  FunctionSet(false, false);
  FunctionSet(false, false);
  OnOff(true, true, true);
  EntryMode(false, true);
  Clear();
  Home();
  HL_LoopDelay(1000000);
  Print("Wellcome to HLib");
}



/**
  * @brief Write a data/command to LCD
  * @param data Written data
  * @param isCmd TRUE written is command, FALSE written is display data
  * @return none
  */
void hd44780_c::Write(uint8_t data, bool isCmd){
  if (isCmd){
    GPIO_ResetBits(HD44780_RS_PORT, HD44780_RS_PIN);
  }
  else{
    GPIO_SetBits(HD44780_RS_PORT, HD44780_RS_PIN);
  }
  GPIO_ResetBits(HD44780_RW_PORT, HD44780_RW_PIN);
  #ifdef PLATFORM_STM32F100_STARTER
    /* write higher nibble */
    GPIO_ResetBits(HD44780_DATA_PORT, HD44780_DATA_MASK);
    GPIO_SetBits( HD44780_DATA_PORT,  
                ((uint16_t) (data & 0xF0)) << (HD44780_DATA_POS-4) );
    optFreeVar++; /* NOP */
    GPIO_SetBits(HD44780_EN_PORT, HD44780_EN_PIN);
    optFreeVar++;
    GPIO_ResetBits(HD44780_EN_PORT, HD44780_EN_PIN);
    
    /* write lower nibble */ 
    GPIO_ResetBits(HD44780_DATA_PORT, HD44780_DATA_MASK);
    GPIO_SetBits(HD44780_DATA_PORT,  ((uint16_t) (data & 0x0F))  << HD44780_DATA_POS );
    optFreeVar++;
    GPIO_SetBits(HD44780_EN_PORT, HD44780_EN_PIN);
    optFreeVar++;
    GPIO_ResetBits(HD44780_EN_PORT, HD44780_EN_PIN);
  #else
    #error "Unsupported platform"
  #endif
}


/**
  * @brief Send FunctionSet command
  * @param eightBit TRUE 8-bit is selected, FALSE 4-bit is selected
  * @param font5x10 TRUE 5x10 font is selected, FALSE 5x7 font is selected
  * @return None
  */
void hd44780_c::FunctionSet(bool eightBit, bool font5x10){
  uint8_t writtenData = HD44780_FUNCTION_SET_CMD;
  if (eightBit){
    writtenData |= 0x10;
  }
  writtenData |= 0x08; /* two lines */
  if (font5x10){
    writtenData |= 0x04;
  }
  Write(writtenData, true);
  HL_LoopDelay(HD44780_FUNCTION_SET_DELAY);
}





/**
  * @brief Send Clear Display command
  * @return None
  */
void hd44780_c::Clear(void){
  Write(HD44780_CLEAR_DISPLAY_CMD, true);
  HL_LoopDelay(HD44780_CLEAR_DISPLAY_DELAY);  
}



/**
  * @brief Send Cursor Home command
  * @return None
  */
void hd44780_c::Home(void){
  Write(HD44780_CURSOR_HOME_CMD, true);
  HL_LoopDelay(HD44780_CURSOR_HOME_DELAY);  
}



/**
  * @brief Send Entry Mode command
  * @param shift TRUE the display will be shifted, FALSE the display will not be shifted
  * @param increase TRUE increase cursor position, FALSE decrease cursor position
  * @return None
  */
void hd44780_c::EntryMode(bool shift, bool increase){
  uint8_t writtenData = HD44780_ENTRY_MODE_CMD;
  if (shift){
    writtenData |= 0x01;
  }
  if (increase){
    writtenData |= 0x02;
  }
  Write(writtenData, true);
  HL_LoopDelay(HD44780_ENTRY_MODE_DELAY);
}



/**
  * @brief Send Display On Off command
  * @param displayOn TRUE set the display on, FALSE set the display off
  * @param cursorOn  TRUE set the cursor on, FALSE set the cursor off
  * @param cursorBlink TRUE the cursor is blinked, FALSE the cursor is not blinked
  * @return None
  */
void hd44780_c::OnOff(bool displayOn, bool cursorOn, bool cursorBlink){
  uint8_t writtenData = HD44780_DISPLAY_ON_OFF_CMD;
  if (displayOn){
    writtenData |= 0x04;
  }
  if (cursorOn){
    writtenData |= 0x02;
  }
  if (cursorBlink){
    writtenData |= 0x01;
  }
  Write(writtenData, true);
  HL_LoopDelay(HD44780_DISPLAY_ON_OFF_DELAY);
}



/**
  * @brief Set display cursor to a specified position
  * @param charLine LCD's line
  * @param charCol LCD's column
  * @return None
  */
void hd44780_c::Goto(uint8_t charLine, uint8_t charCol){
  uint8_t absAddr;
  absAddr = (charLine * 0x40) + charCol;
  Write((absAddr & 0xEF) | HD44780_SET_DDRAM_ADDRESS_CMD, true);
  HL_LoopDelay(HD44780_SET_DDRAM_ADDRESS_DELAY);
}
 



/**
  * @brief Print one character to the LCD
  * @param printChar Character to print
  * @return None
  */
void hd44780_c::Print(char printChar){
  Write(printChar, false);   
  HL_LoopDelay(200);
}



/**
  * @brief Print one string to the LCD
  * @param printString String to print
  * @return None
  */
void hd44780_c::Print(char* printString){
  while(*printString != '\0'){
    Print(*printString);
    printString++;
  }
}

    
/**
  * @brief Print one unsigned number to the LCD
  * @param printNum Unsigned number to print
  * @param radix Valid values are 2, 8, 10, 16
  * @return None
  */
void hd44780_c::Print(uint32_t printNum, uint8_t radix){
  char outStr[33];
  HL_NumToStr(printNum, radix, outStr);
  Print((char*) outStr);
}


/**
  * @overload
  * @brief Print one unsigned number to the LCD in decimal
  * @param printNum Unsigned number to print
  * @return None
  */
void hd44780_c::Print(uint32_t printNum){
  Print(printNum, 10);
}



/**
  * @brief Print one signed number to the LCD in decimal
  * @param printNum Unsigned number to print
  * @return None
  */
void hd44780_c::Print(int32_t printNum){
  if (printNum<0){
    Print('-');
    Print((uint32_t) -printNum, 10);
  }
  else{
    Print((uint32_t) printNum, 10);
  }
}
