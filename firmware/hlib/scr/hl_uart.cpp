/**
 @file hl_uart.cpp
 @brief Implementing serial communication methods for USARTs in <b> HLib's MBoards  </b>

 @author  Bui Van Hieu <bvhieu@cse.hcmut.edu.vn>
 @version 1.1
 @date 10-12-2013

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

////////////////////////////////////////////////////////////
#ifdef INITIAL_CHECK 
  #define _UART_CONSTRUCT_CHECK() if (uartNum == NULL) {return HL_INVALID;} 
  #define _UART_STARTED_CHECK()   if (uartStarted == false) {return HL_NOT_START;} 
#else
  #define _UART_CONSTRUCT_CHECK()
  #define _UART_STARTED_CHECK()
#endif

////////////////////////////////////////////////////////////
/**
 @brief Construction function
 @param uartNum UART will be used.   
 @return None
*/
uart_c::uart_c(uint8_t uartNum){
  switch (uartNum){
    #if defined(STM32F100C8_MCU)
      case 1:  this->uartNum = uartNum; UARTx = USART1; break;
      case 2:  this->uartNum = uartNum; UARTx = USART2; break;
    #elif defined(STM32F103RCT6_MCU)
      case 1:  this->uartNum = uartNum; UARTx = USART1; break;
      case 2:  this->uartNum = uartNum; UARTx = USART2; break;
      case 3:  this->uartNum = uartNum; UARTx = USART3; break;
      case 4:  this->uartNum = uartNum; UARTx = UART4; break;
      case 5:  this->uartNum = uartNum; UARTx = UART5; break;
	#else
      #error "Unsupported platform"
    #endif
   	  default: this->uartNum = 0; UARTx = NULL;  
  } /* end switch */
  uartStarted    = false;
}



/**
 @brief Start serial communicating
 @param baudRate UART's baud rate
 @param stopBit UART's stopBit
 @return HL_OK , HL_INVALID
*/
err_t  uart_c::Start(uint32_t baudRate, uint16_t stopBit){
  USART_InitTypeDef USART_InitStruct;
  
  _UART_CONSTRUCT_CHECK();

  /* enable UART clock */
  switch (uartNum){
    case 1: RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); break;
  	case 2: RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); break;
	  case 3: RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); break;
	  case 4: RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,  ENABLE); break;
	  case 5: RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,  ENABLE); break;
  }
  
  /*config USART */
  if (0 != uartNum){  
    USART_InitStruct.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct.USART_Parity     = USART_Parity_No;
    USART_InitStruct.USART_BaudRate   = baudRate;
    USART_InitStruct.USART_StopBits   = stopBit;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(UARTx, &USART_InitStruct);
    
    /*enable USART*/
    USART_Cmd(UARTx, ENABLE);
    uartStarted = true;
  }
  return HL_OK;
}



/**
 @overload
 @brief Start serial communicating in default mode with 8 data-bit, 1 stop-bit, no-parity
 @param baudRate UART's baud rate
 @return HL_OK, HL_INVALID
*/
err_t  uart_c::Start(uint32_t baudRate){
  return Start(baudRate, USART_StopBits_1);
}



/**
 @brief Stop UART clock
 @return HL_OK, HL_INVALID
*/
err_t  uart_c::Shutdown(){
  
  _UART_CONSTRUCT_CHECK();
  
  USART_Cmd(UARTx, DISABLE);
  switch (uartNum){
    case 1:	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, DISABLE); break;
	  case 2:	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, DISABLE);	break;
	  case 3:	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, DISABLE);	break;
	  case 4:	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,  DISABLE);	break;
	  case 5:	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,  DISABLE);	break;
  }
  return HL_OK;
}



/**
 @brief Send one character
 @param outChar Character to send
 @return HL_OK, HL_NOT_STARTED, HL_INVALID
*/
err_t  uart_c::Print(char outChar){
  _UART_STARTED_CHECK();
  /* Wait until output buffer is empty */ 
  while (!(UARTx->SR & USART_FLAG_TXE)) {  }; /* wait */ 
  UARTx->DR = (uint16_t)  outChar;
  return HL_OK;
}



/**
 @overload
 @brief Send one string
 @param outStr String to send
 @return HL_OK, HL_NOT_STARTED, HL_INVALID
*/
err_t  uart_c::Print(char* outStr){
  _UART_STARTED_CHECK();
  while (*outStr != '\0'){
    while (!(UARTx->SR & USART_FLAG_TXE)) {  }; /* wait */  
    UARTx->DR = (uint16_t) (*outStr);
    outStr++;
  } 
  return HL_OK;
}



/**
 @overload
 @brief Convert one unsigned interger into string and then send it 
 @param outNum Unsigned interger number to send
 @param radix Valid values are 2, 8, 10, 16
 @return HL_OK, HL_NOT_STARTED, HL_INVALID
*/
err_t  uart_c::Print(uint32_t outNum, uint8_t radix){
  char  outStr[33];

  _UART_STARTED_CHECK();
  #ifdef PARAM_CHECK_FULL
    if ((radix != 2) && (radix != 8) && (radix != 10) && (radix != 16)) { return HL_INVALID; }
  #endif 
  HL_NumToStr(outNum, radix, outStr);
  return Print((char*) outStr);
}



/**
 @overload
 @brief Convert one unsigned interger into string and then send it with default radix (decimal)
 @param outNum Unsigned interger number to send
 @return HL_OK, HL_NOT_STARTED, HL_INVALID
*/
err_t  uart_c::Print(uint32_t outNum){
  return Print(outNum, 10);
}



/**
 @brief Convert one signed interger into decimal string and then send it
 @param outNum Signed interger number to send
 @return HL_OK, HL_NOT_STARTED, HL_INVALID
*/
err_t  uart_c::Print(int32_t outNum){
  _UART_STARTED_CHECK();
  if (outNum<0){
    Print('-');
    return Print((uint32_t) (-outNum), 10);
  }
  else{
    return Print((uint32_t) outNum, 10);
  }
}



/**
 @brief Send one raw 8-bit number 
 @param outNum 8-bit number to send
 @return HL_OK, HL_NOT_STARTED, HL_INVALID
*/
err_t  uart_c::Out(uint8_t outNum){
  _UART_STARTED_CHECK();
  while (!(UARTx->SR & USART_FLAG_TXE)) {  }; /* wait */ 
  UARTx->DR = (uint16_t)  outNum;
  return HL_OK;
}



/**
 @overload
 @brief Send one raw 16-bit number. The low-order part is sent first.
 @param outNum 16-bit number to send. 
 @return HL_OK, HL_NOT_STARTED, HL_INVALID
*/
err_t  uart_c::Out(uint16_t outNum){
  _UART_STARTED_CHECK();
  while (!(UARTx->SR & USART_FLAG_TXE)) {  }; /* wait */ 
  UARTx->DR = (uint16_t)  (outNum);
  while (!(UARTx->SR & USART_FLAG_TXE)) {  }; /* wait */ 
  UARTx->DR = (uint16_t)  (outNum >> 8);
  return HL_OK;
}



/**
 @overload
 @brief Send one raw 32-bit number. The low-order part is sent first.
 @param outNum 32-bit number to send. 
 @return HL_OK, HL_NOT_STARTED, HL_INVALID
*/
err_t  uart_c::Out(uint32_t outNum){
  _UART_STARTED_CHECK();
  while (!(UARTx->SR & USART_FLAG_TXE)) {  }; /* wait */ 
  UARTx->DR = (uint16_t) (outNum);
  while (!(UARTx->SR & USART_FLAG_TXE)) {  }; /* wait */ 
  UARTx->DR = (uint16_t) (outNum >> 8);
  while (!(UARTx->SR & USART_FLAG_TXE)) {  }; /* wait */ 
  UARTx->DR = (uint16_t) (outNum >> 16);
  while (!(UARTx->SR & USART_FLAG_TXE)) {  }; /* wait */ 
  UARTx->DR = (uint16_t) (outNum >> 24);
  return HL_OK;
}


 
/**
 @brief Send one buffer
 @param outBuf Buffer to send
 @param bufLen Length in byte of the buffer
 @return HL_OK, HL_NOT_STARTED, HL_INVALID
*/
err_t  uart_c::Out(uint8_t outBuf[], uint32_t bufLen){
  uint32_t count = 0;

  _UART_STARTED_CHECK();
  while (count < bufLen){
    while (!(UARTx->SR & USART_FLAG_TXE)) {  } /* wait */
    UARTx->DR = (uint16_t) outBuf[count];
    count++;
  } 
  return HL_OK;   
}


/**
 @brief Get one received byte in receiving buffer
 @return Received data 
*/
uint8_t uart_c::Get(void){
  return (uint8_t)(UARTx->DR & (uint16_t)0x00FF);
}


/**
 @brief Check whether there is a new received byte in receiving buffer
 @retval TRUE has new data
 @retval FALSE no new data
*/
bool uart_c::HasData(void){
  return ( (UARTx->SR & USART_FLAG_RXNE) != 0 );
}
/////////////////////////////////////////////////
extern "C" {
void USART1_IRQHandler(void){
  //use callback to implement interrupt handle
}
  
} /* end extern "C" */
