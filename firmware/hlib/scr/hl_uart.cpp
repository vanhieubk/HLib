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

/**
 @class uart_c
 @brief Providing controlling method for USART peripheral of STM32
 @attention
 - This library always enables receiving feature.
 - This library always uses 1-stop-bit mode
 - DMA transfer/receiver has not been supported\n.
 - Current version only supports polling receiving. Interrupt receiving will be implemented in next version
 - This library neither support 9-bit data word nor parity check. If you need this feature, please contact us.
*/

#include "hlib.h"

namespace HLib{
////////////////////////////////////////////////////////////
/**
 @brief Construction function
 @return None
*/
uart_c::uart_c(){
  UARTx     	= NULL;
	uartStarted = false;
}



/**
 @brief Start serial communicating
 @param uartNum Number of the UART used
 @param baudRate UART's baud rate
 @retval INVALID the uartNum parameter is out of range
 @retval OK the function if finished successfully
 @attention the baudRate parameter is not checked. Use a valid value with your platform.
*/
err_t  uart_c::Start(uint8_t uartNum, uint32_t baudRate){
  USART_InitTypeDef USART_InitStruct;

  switch (uartNum){
    #if defined(STM32F100C8_MCU)
      case 1:  UARTx = USART1; CLK_Ctrl(CLK_UART1, true); break;
      case 2:  UARTx = USART2; CLK_Ctrl(CLK_UART2, true);break;
    #elif defined(STM32F103RCT6_MCU)
      case 1:  UARTx = USART1; CLK_Ctrl(CLK_UART1, true);break;
      case 2:  UARTx = USART2; CLK_Ctrl(CLK_UART2, true);break;
      case 3:  UARTx = USART3; CLK_Ctrl(CLK_UART2, true);break;
      case 4:  UARTx = UART4;  CLK_Ctrl(CLK_UART3, true);break;
      case 5:  UARTx = UART5;  CLK_Ctrl(CLK_UART4, true);break;
	  #else
      #error "Unsupported platform"
    #endif
   	  default: uartStarted = false; UARTx = NULL; return INVALID;  
  } /* end switch */
    
	USART_InitStruct.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity     = USART_Parity_No;
	USART_InitStruct.USART_BaudRate   = baudRate;
	USART_InitStruct.USART_StopBits   = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Cmd(UARTx, DISABLE);
	USART_Init(UARTx, &USART_InitStruct);
	
	/*enable USART*/
	USART_Cmd(UARTx, ENABLE);
	uartStarted = true;
  return OK;
}



/**
 @brief Stop UART and disable its clock
 @retval NOT_START the UART has not been started before
 @retval OK the function is finished successfully
*/
err_t  uart_c::Shutdown(){
  if (!uartStarted) { return NOT_START;}
 
  USART_Cmd(UARTx, DISABLE);
	if (USART1 == UARTx){
		CLK_Ctrl(CLK_UART1, DISABLE);
  }
	else if (USART2 == UARTx){
		CLK_Ctrl(CLK_UART2, DISABLE);
  }
	#ifdef STM32F103RCT6_MCU
	else if (USART3 == UARTx){
		CLK_Ctrl(CLK_UART3, DISABLE);
  }
	
	else if (UART4 == UARTx){
		CLK_Ctrl(CLK_UART4, DISABLE);
  }
	else if (UART5 == UARTx){
		CLK_Ctrl(CLK_UART5, DISABLE);
  }
	#endif
  UARTx 			= NULL;
	uartStarted = false;
  return OK;
}



/**
 @brief Send one character
 @param outChar Character to send
 @retval NOT_START the UART has not been started before
 @retval OK the function is finished successfully
*/
err_t  uart_c::Print(char outChar){
  if (!uartStarted) { return NOT_START;}
  /* Wait until output buffer is empty */ 
  while (!(UARTx->SR & USART_FLAG_TXE)) {  }; /* wait */ 
  UARTx->DR = (uint16_t)  outChar;
  return OK;
}



/**
 @overload
 @brief Send one string
 @param outStr String to send
 @retval NOT_START the UART has not been started before
 @retval OK the function is finished successfully
*/
err_t  uart_c::Print(char* outStr){
  if (!uartStarted) { return NOT_START;}
  while (*outStr != '\0'){
    while (!(UARTx->SR & USART_FLAG_TXE)) {  }; /* wait */  
    UARTx->DR = (uint16_t) (*outStr);
    outStr++;
  } 
  return OK;
}



/**
 @overload
 @brief Convert one unsigned interger into string and then send it 
 @param outNum Unsigned interger number to send
 @param radix Radix of the conversion. Valid values are 2, 8, 10, 16
 @retval NOT_START the UART has not been started before
 @retval INVALID the radix parameter is out of range
 @retval OK the function is finished successfully
*/
err_t  uart_c::Print(uint32_t outNum, uint8_t radix){
  char  outStr[33];

  if (!uartStarted) { return NOT_START;}
  if ((radix != 2) && (radix != 8) && (radix != 10) && (radix != 16)) { return INVALID; }

  NumToStr(outNum, radix, outStr);
  return Print((char*) outStr);
}




/**
 @brief Convert one signed interger into decimal string and then send it
 @param outNum Signed interger to send
 @retval NOT_START the UART has not been started before
 @retval OK the function is finished successfully
*/
err_t  uart_c::Print(int32_t outNum){
  if (!uartStarted) { return NOT_START;}
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
 @retval NOT_START the UART has not been started before
 @retval OK the function is finished successfully
*/
err_t  uart_c::Out(uint8_t outNum){
  if (!uartStarted) { return NOT_START;}
  while (!(UARTx->SR & USART_FLAG_TXE)) {  }; /* wait */ 
  UARTx->DR = (uint16_t)  outNum;
  return OK;
}



/**
 @overload
 @brief Send one raw 16-bit number. The low-order part is sent first.
 @param outNum 16-bit number to send. 
 @retval NOT_START the UART has not been started before
 @retval OK the function is finished successfully
*/
err_t  uart_c::Out(uint16_t outNum){
  if (!uartStarted) { return NOT_START;}
  while (!(UARTx->SR & USART_FLAG_TXE)) {  }; /* wait */ 
  UARTx->DR = (uint16_t)  (outNum);
  while (!(UARTx->SR & USART_FLAG_TXE)) {  }; /* wait */ 
  UARTx->DR = (uint16_t)  (outNum >> 8);
  return OK;
}



/**
 @overload
 @brief Send one raw 32-bit number. The low-order part is sent first.
 @param outNum 32-bit number to send. 
 @retval NOT_START the UART has not been started before
 @retval OK the function is finished successfully
*/
err_t  uart_c::Out(uint32_t outNum){
  if (!uartStarted) { return NOT_START;}
  while (!(UARTx->SR & USART_FLAG_TXE)) {  }; /* wait */ 
  UARTx->DR = (uint16_t) ((outNum ) & 0xFF);
  while (!(UARTx->SR & USART_FLAG_TXE)) {  }; /* wait */ 
  UARTx->DR = (uint16_t) ((outNum >> 8) & 0xFF);
  while (!(UARTx->SR & USART_FLAG_TXE)) {  }; /* wait */ 
  UARTx->DR = (uint16_t) ((outNum >> 16) & 0xFF);
  while (!(UARTx->SR & USART_FLAG_TXE)) {  }; /* wait */ 
  UARTx->DR = (uint16_t) ((outNum >> 24) & 0xFF);
  return OK;
}


 
/**
 @brief Send one buffer
 @param outBuf Buffer to send
 @param bufLen Length in byte of the buffer
 @retval NOT_START the UART has not been started before
 @retval OK the function is finished successfully
*/
err_t  uart_c::Out(uint8_t outBuf[], uint32_t bufLen){
  uint32_t count = 0;

  if (!uartStarted) { return NOT_START;}
  while (count < bufLen){
    while (!(UARTx->SR & USART_FLAG_TXE)) {  } /* wait */
    UARTx->DR = (uint16_t) outBuf[count];
    count++;
  } 
  return OK;   
}


/**
 @brief Get one received byte in receiving buffer
 @para recvData pointer to memory stored receiving data
 @retval NOT_START the UART has not been started before, recvData is not modified
 @retval OK the function is finished successfully
*/
err_t uart_c::Get(uint8_t* recvData){
  if (!uartStarted) { return NOT_START;}
	*recvData = (uint8_t) (UARTx->DR & (uint16_t) 0x00FF);
	return OK;
}


/**
 @brief Check whether there is a new received byte in receiving buffer
 @retval TRUE has new data
 @retval FALSE no new data
*/
bool uart_c::HasData(void){
  if (!uartStarted) { 
		return false;
  }
  else {
    return ( (UARTx->SR & USART_FLAG_RXNE) != 0 );
	}
}
/////////////////////////////////////////////////
extern "C" {
void USART1_IRQHandler(void){
  //use callback to implement interrupt handle
}
  
} /* end extern "C" */


} /* namespace */

