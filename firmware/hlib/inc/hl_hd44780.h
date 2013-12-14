/**
 * @file hl_hd44780.h
 * functions controlling hd44780-based LCD
 *
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
#ifndef __HL_HD44780_H
#define __HL_HD44780_H

///////////////////////////////////////
#define HD44780_CLEAR_DISPLAY_CMD           0x01 /**< Clear display command*/
#define HD44780_CURSOR_HOME_CMD             0x02 /**< Set cursor to home command*/
#define HD44780_ENTRY_MODE_CMD              0x04 /**< Set entry mode command*/
#define HD44780_DISPLAY_ON_OFF_CMD          0x08 /**< Set display ON/OFF command*/
#define HD44780_CURSOR_DISPLAY_SHIFT_CMD    0x10 /**< Set cursor shift command*/
#define HD44780_FUNCTION_SET_CMD            0x20 /**< Set function mode command*/
#define HD44780_SET_CGRAM_ADDRESS_CMD       0x40 /**< Set CGRAM addresss command*/
#define HD44780_SET_DDRAM_ADDRESS_CMD       0x80 /**< Set DDRAM address command*/

#define HD44780_CLEAR_DISPLAY_DELAY         24000 	/**< Delay time after clear display command*/ 
#define HD44780_CURSOR_HOME_DELAY           24000 	/**< Delay time after set cursor to home command*/ 
#define HD44780_ENTRY_MODE_DELAY            24000 	/**< Delay time after set entry mode command*/ 
#define HD44780_DISPLAY_ON_OFF_DELAY        24000 	/**< Delay time after set display ON/OFF command*/ 
#define HD44780_CURSOR_DISPLAY_SHIFT_DELAY  24000 	/**< Delay time after set cursor shift command*/ 
#define HD44780_FUNCTION_SET_DELAY          400000 	/**< Delay time after set function mode command*/ 
#define HD44780_SET_CGRAM_ADDRESS_DELAY     200 		/**< Delay time after set CGRAM address command*/ 
#define HD44780_SET_DDRAM_ADDRESS_DELAY     200 		/**< Delay time after set DDRAM address command*/ 

#ifdef PLATFORM_STM32F100_STARTER
	#define HD44780_RS_PORT     GPIOA
	#define HD44780_RS_CLK      RCC_APB2Periph_GPIOA
	#define HD44780_RS_PIN      GPIO_Pin_8

	#define HD44780_RW_PORT     GPIOB
	#define HD44780_RW_CLK      RCC_APB2Periph_GPIOB
	#define HD44780_RW_PIN      GPIO_Pin_0

	#define HD44780_EN_PORT     GPIOB
	#define HD44780_EN_CLK      RCC_APB2Periph_GPIOB
	#define HD44780_EN_PIN      GPIO_Pin_1

	#define HD44780_DATA_PORT   GPIOB
	#define HD44780_DATA_CLK    RCC_APB2Periph_GPIOB
	#define HD44780_DATA_PIN_4  GPIO_Pin_12
	#define HD44780_DATA_PIN_5  GPIO_Pin_13
	#define HD44780_DATA_PIN_6  GPIO_Pin_14
	#define HD44780_DATA_PIN_7  GPIO_Pin_15
	#define HD44780_DATA_POS    12
  #define HD44780_DATA_MASK   0xF000              
#else
  #error "Unsupported platform"
#endif


/**
 @class hd44780_c
 @brief Providing all methods to control HD44780 LCD for STM32 STARTER KIT
*/
class hd44780_c {
private:
  void Write(uint8_t data, bool isCmd);
  void FunctionSet(bool eightBit, bool font5x10);
public:
  hd44780_c();
  void Start(void);
  void Clear(void);
  void Home(void);
  void EntryMode(bool shift, bool increase);
  void OnOff(bool displayOn, bool cursorOn, bool cursorBlink);

  //character functions
  void Goto(uint8_t charLine, uint8_t charCol);
  void Print(char printChar);
  void Print(char* printStr);
  void Print(uint32_t printNum, uint8_t radix);
  void Print(uint32_t printNum);
  void Print(int32_t printNum);
};

#endif /*__HL_HD44780_H  */
