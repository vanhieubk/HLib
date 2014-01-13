/**
 @file hl_spi_basis.cpp
 @brief Implementing basis communication methods for SPI in <b> HLib's MBoards  </b>
 
 @author  Bui Van Hieu <bvhieu@cse.hcmut.edu.vn>
 @version 1.2
 @date 11-1-2014
 
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
 
 @class spi_basis_c
 @brief Providing controlling method for SPI peripheral of a STM32
 @attention
 - Only master SPI mode is supported. No slave mode.
 - Only 8-bit data frame mode is supported. No 16-bit data frame mode.
 - DMA has not supported yet
 - Interrupt has not supported yet
*/



#include "hlib.h"
namespace HLib{



#define CR1_CRCNext_Set      ((uint16_t)0x1000)
#define CR1_SPE_Set          ((uint16_t)0x0040)
#define CR1_SPE_Reset        ((uint16_t)0xFFBF)
#define CR1_CRCEN_Set        ((uint16_t)0x2000)
#define CR1_CRCEN_Reset      ((uint16_t)0xDFFF)



////////////////////////////////////////////////////////////
#ifdef INITIAL_CHECK 
  #define _SPI_CONSTRUCT_CHECK() if (spiNum == NULL) {return HL_INVALID;} 
  #define _SPI_STARTED_CHECK()   if (spiStarted == false) {return HL_NOT_START;} 
#else
  #define _SPI_CONSTRUCT_CHECK()
  #define _SPI_STARTED_CHECK()
#endif

////////////////////////////////////////////////////////////
/**
 @brief Construction function  
 @return None
*/
spi_basis_c::spi_basis_c(){
  SPIx       = NULL;
  spiStarted = false;
}



 /**
 @brief Start SPI peripheral.
 @brief spiNum Number of the SPI used
 @param prescaler Baudrate prescaler of SPI. Valid values are ....
 @param idleHigh TRUE : data line is kept at high level in idle state.\n FALSE : data line is kept at low level in idle state.
 @param secondEdge TRUE: data is latched at the second edge.\n FALSE: data is latched at the first edge
 @param firstMSB TRUE: first bit is the MSB.\n FALSE: first bit is the LSB
 @param direction Communication direction of the SPI
 @param crcEnable TRUE: hardware CRC calculator is used.\n FALSE: hardware CRC calculator is not used
 @param crcPoly: CRC polynomial 
 @retval HL_INVALID one or some parameters is invalid. The method is cancel
 @retval HL_OK The used SPI is started OK
*/
err_t spi_basis_c::Start(spi_direction_t direction, uint8_t spiNum,  uint16_t prescaler, bool idleLevel, bool secondEdge, 
bool firstMSB,  bool crcEnable, uint16_t crcPoly){
  SPI_InitTypeDef   SPI_InitStruct;
  spi_prescaler_t   setPrescaler;
  
  switch (spiNum){
    #if defined(STM32F100C8_MCU)
      case 1:  SPIx = SPI1; CLK_Ctrl(CLK_SPI1, ENABLE);break;
    #elif defined(STM32F103RCT6_MCU)
      case 1:  SPIx = SPI1; CLK_Ctrl(CLK_SPI1, ENABLE);break;
      case 2:  SPIx = SPI2; CLK_Ctrl(CLK_SPI2, ENABLE);break;
      case 3:  SPIx = SPI3; CLK_Ctrl(CLK_SPI3, ENABLE);break;
	  #else
      #error "Unsupported MCU"
    #endif
   	  default: SPIx = NULL; spiStarted = false; return HL_INVALID; 
  } /* end switch */
  
  switch (prescaler){
    case 2:   setPrescaler = SPI_PRESCALER_2;   break;
    case 4:   setPrescaler = SPI_PRESCALER_4;   break;
    case 8:   setPrescaler = SPI_PRESCALER_8;   break;
    case 16:  setPrescaler = SPI_PRESCALER_16;  break;
    case 32:  setPrescaler = SPI_PRESCALER_32;  break;
    case 64:  setPrescaler = SPI_PRESCALER_64;  break;
    case 128: setPrescaler = SPI_PRESCALER_128; break;
    case 256: setPrescaler = SPI_PRESCALER_256; break;
    default : SPIx = NULL; return HL_INVALID;
  }
  /*config SPI/I2S */
  SPI_InitStruct.SPI_CPOL              = idleLevel  ? SPI_CPOL_High    : SPI_CPOL_Low;
  SPI_InitStruct.SPI_CPHA              = secondEdge ? SPI_CPHA_2Edge   : SPI_CPHA_1Edge;
  SPI_InitStruct.SPI_FirstBit          = firstMSB   ? SPI_FirstBit_MSB : SPI_FirstBit_LSB; 
  SPI_InitStruct.SPI_CPHA              = SPI_CPHA_2Edge;
  SPI_InitStruct.SPI_NSS               = SPI_NSS_Soft;
  SPI_InitStruct.SPI_Mode              = SPI_Mode_Master;
  SPI_InitStruct.SPI_DataSize          = SPI_DataSize_8b;
  SPI_InitStruct.SPI_Direction         = direction;
  SPI_InitStruct.SPI_CRCPolynomial     = crcPoly;  
  SPI_InitStruct.SPI_BaudRatePrescaler = setPrescaler; 
 
  SPIx->CR1 &= CR1_SPE_Reset; /* stop/disable */  
  SPI_Init(SPIx, &SPI_InitStruct);
  if (crcEnable){
    SPIx->CR1 |= CR1_CRCEN_Set;
  }
  else{
    SPIx->CR1 &= CR1_CRCEN_Reset;
  }
  /*enable SPI*/
  SPIx->CR1 |= CR1_SPE_Set;     
  
  spiStarted = true;
  return HL_OK;
}


/**
 @brief Stop SPI/I2S and then disable its clock
 @retval HL_NOT_START SPI is not started before calling this function
 @retval HL_OK The function is finished successfully
*/
err_t spi_basis_c::Shutdown(){
  if (!spiStarted){return HL_NOT_START;}

  SPIx->CR1 &= CR1_SPE_Reset;
  if (SPI1 == SPIx){
    CLK_Ctrl(CLK_SPI1, DISABLE);
  }
  else if (SPI2 == SPIx){
    CLK_Ctrl(CLK_SPI2, DISABLE);
  }
  else if (SPI3 == SPIx){
    CLK_Ctrl(CLK_SPI3, DISABLE);
  }
  else{
    return HL_INVALID;
  }

  SPIx = NULL;
  spiStarted = false;
  return HL_OK;
}



/**
 @brief Wait until the output buffer empty and then send one byte
 @param sendData Data to send
 @retval HL_NOT_START SPI is not started before calling this function
 @retval HL_OK The function is finished successfully
*/
err_t spi_basis_c::Send(uint8_t sendData){
  if (!spiStarted) {return HL_NOT_START;} 
  while (!(SPIx->SR & SPI_I2S_FLAG_TXE)){
    /* wait, DO NOTHING */
  }  
  SPIx->DR = sendData;
  return HL_OK;
}


/**
 @overload
 @brief Send one byte. Wait until data transmision completed and then get receiving data
 @param sendData Data to send
 @param recvData Pointer to variable will hold receiving data
 @retval HL_NOT_START SPI is not started before calling this function
 @retval HL_OK The function is finished successfully
*/
err_t spi_basis_c::Send(uint8_t sendData, uint8_t *recvData){ 
  if (!spiStarted) {return HL_NOT_START;} 
  Send(sendData);
  while (!(SPIx->SR & SPI_I2S_FLAG_TXE)){
    /* wait data to send, DO NOTHING */
  }
  while (SPIx->SR & SPI_I2S_FLAG_BSY);{
    /* wait data send completly, get last received data, DO NOTHING */
  }
  *recvData = (uint8_t) SPIx->DR;
  return HL_OK;
}


/**
 @overload 
 @brief Send an array of data
 @param sendBuf Array of data to send
 @param bufLen Length of array of data
 @retval HL_NOT_START SPI is not started before calling this function
 @retval HL_OK The function is finished successfully
*/
err_t spi_basis_c::Send(uint8_t sendBuf[], uint16_t bufLen){
  uint16_t index;
  
  if (!spiStarted) {return HL_NOT_START;} 
  for (index=0; index<bufLen; index++){
    Send(sendBuf[index]);
  } 
  return HL_OK;
}


/**
 @overload
 @brief Send and receive arrays of data without any stall in SCK
 @param sendBuf Array of data to send
 @param recvBuf Pointer to array of data will hold receiving data
 @param bufLen Length of send/receive array of data
 @retval HL_NOT_START SPI is not started before calling this function
 @retval HL_OK The function is finished successfully
 @attention This function may lost some data if there are some long-time interupts happen.
            In order to ensure data reliable, please use RecvSafe() which sends and receives byte by byte
*/
err_t spi_basis_c::Send(uint8_t sendBuf[], uint16_t bufLen, uint8_t recvBuf[]){
  uint16_t index;

  if (!spiStarted) {return HL_NOT_START;}
  if (bufLen == 0) {return HL_OK;}
  /* not reuse Send(), write new one to get more efficient */
  while (SPIx->SR & SPI_I2S_FLAG_BSY);{
    /* wait previous transmision completly, DO NOTHING */
  }
  /* clear RXNE flag */
  SPIx->SR &= ~(SPI_I2S_FLAG_RXNE);
  /* send first data */
  Send(sendBuf[0]);
  /* send remain data while get receiving data */
  for (index=1; index<bufLen; index++){
    Send(sendBuf[index]);
    while (!(SPIx->SR & SPI_I2S_FLAG_RXNE)){
    /* wait recv data (previous send completed), DO NOTHING */
    }
    recvBuf[index-1] = SPIx->DR;
  }
  /* get last data */
  while (!(SPIx->SR & SPI_I2S_FLAG_RXNE)){
    /* wait the last recv data, DO NOTHING */
  }
  recvBuf[index-1] = SPIx->DR;
  return HL_OK;
}



/**
 @brief Send and receive arrays of data byte by byte
 @param sendBuf Array of data to send
 @param recvBuf Pointer to array of data will hold receiving data
 @param bufLen Length of send/receive array of data
 @retval HL_NOT_START SPI is not started before calling this function
 @retval HL_OK The function is finished successfully
*/
err_t spi_basis_c::RecvSafe(uint8_t sendBuf[], uint16_t bufLen, uint8_t recvBuf[]){
  uint16_t index;

  if (!spiStarted) {return HL_NOT_START;}
  for (index=0; index<bufLen; index++){
    Send(sendBuf[index], &(recvBuf[index]));
  }
  return HL_OK;
}


/**
 @brief Get current CRC polynomial
 @return Current CRC polynomial
*/
uint16_t spi_basis_c::GetCRCPoly(){
  if (NULL != SPIx){ 
    return SPIx->CRCPR;
  }
  else{
    return 0;
  }
}



/**
 @brief Request sending hardware calculated CRC after current transmission completed
 @retval HL_NOT_START SPI is not started before calling this function
 @retval HL_OK The function is finished successfully
*/
err_t spi_basis_c::SendCRC(){ 
  if (!spiStarted) {return HL_NOT_START;}

  SPIx->CR1 |= CR1_CRCNext_Set;
  return HL_OK;
}      



/**
 @brief Get sending CRC value if CRC feature is enabled
 @return Sending CRC
*/
uint16_t spi_basis_c::GetSendCRC(){
  if (NULL != SPIx){
    return SPIx->TXCRCR;
  }
  else{
    return 0;
  }
}



/**
 @brief Get receiving CRC value if CRC feature is enabled
 @return Receiving CRC
*/
uint16_t spi_basis_c::GetRecvCRC(){
  if (NULL != SPIx){
    return SPIx->RXCRCR;
  }
  else{
    return 0;
  }
}



/**
 @brief Clear calculated CRC to prepare for new transmision
 @retval HL_NOT_START SPI is not started before calling this function
 @retval HL_OK The function is finished successfully
 @attention Only use when SPI is not busy or data corruption may happen
*/
err_t spi_basis_c::ClearCRC(){
  if (!spiStarted) {return HL_NOT_START;}
  while (IsBusy()){
    /* wait until SPI finish current operating */
  }
  SPIx->CR1 &= CR1_SPE_Reset;   //Disable SPI
  SPIx->CR1 &= CR1_CRCEN_Reset; //Disable CRC
  SPIx->CR1 |= CR1_CRCEN_Set;   //Enable CRC
  SPIx->CR1 |= CR1_SPE_Set;     //Enable SPI
  return HL_OK;
} 



/**
 @brief Check SPI busy status
 @return TRUE: SPI is busy. FALSE: SPI is not busy or not started
*/
bool spi_basis_c::IsBusy(){
  if (!spiStarted) return false;
  else{
    return (bool) (SPIx->SR & SPI_I2S_FLAG_BSY);
  }
} 



/////////////////////////////////////////////////
extern "C" {
#if defined(STM32F100C8_MCU) || defined(STM32F103RCT6_MCU)
  void SPI1_IRQHandler(void){
	  //use callback to implement interrupt handle
  }
#endif


#if defined(STM32F103RCT6_MCU)
  void SPI2_IRQHandler(void){
	  //use callback to implement interrupt handle
  }

  void SPI3_IRQHandler(void){
	  //use callback to implement interrupt handle
  }
#endif
  
} /* end extern "C" */


} /* namespace */

