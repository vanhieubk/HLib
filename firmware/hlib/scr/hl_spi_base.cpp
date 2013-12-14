/**
 @file hl_spi_base.cpp
 @brief Implementing basis communication methods for SPI in <b> HLib's MBoards  </b>
 
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
 
 @class spi_base_c
 @brief Providing controlling method for SPI peripheral of a STM32
 @attention
 - Only master SPI mode is supported. No slave mode.
 - Only 8-bit data frame mode is supported. No 16-bit data frame mode.
 - DMA has not supported yet
 - Interrupt has not supported yet
*/



#include "hlib.h"

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
 @param spiNum SPI/I2S will be used.   
 @return None
*/
spi_base_c::spi_base_c(uint8_t spiNum){
  switch (spiNum){
    #if defined(STM32F100C8_MCU)
      case 1:  this->spiNum = spiNum; SPIx = SPI1; break;
    #elif defined(STM32F103RCT6_MCU)
      case 1:  this->spiNum = spiNum; SPIx = SPI1; break;
      case 2:  this->spiNum = spiNum; SPIx = SPI2; break;
      case 3:  this->spiNum = spiNum; SPIx = SPI3; break;
	#else
      #error "Unsupported platform"
    #endif
   	  default: this->spiNum = 0; SPIx = NULL;  
  } /* end switch */
  spiStarted    = false;
}



 /**
 @brief Start SPI peripheral.
 @param prescaler Baudrate prescaler of SPI.
 @param idleLevel TRUE : data line is kept at high level in idle state.\n FALSE : data line is kept at low level in idle state.
 @param secondEdge TRUE: data is latched at the second edge.\n FALSE: data is latched at the first edge
 @param firstBitMSB TRUE: first bit is the MSB.\n FALSE: first bit is the LSB
 @param direction Communication direction of the SPI
 @param crcEnable TRUE: hardware CRC calculator is used.\n FALSE: hardware CRC calculator is not used
 @param crcPoly: CRC polynomial 
 @retval HL_INVALID one or some parameters is invalid. The method is cancel
 @retval HL_OK The method is performed OK
*/
err_t spi_base_c::Start(spi_prescaler_t prescaler, bool idleLevel, bool secondEdge, bool firstBitMSB, spi_direction_t direction, bool crcEnable, uint16_t crcPoly){
  SPI_InitTypeDef   SPI_InitStruct;
  
  _SPI_CONSTRUCT_CHECK();

   /* enable SPI/I2S clock */
  switch (spiNum){
    case 1: RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE); break;
	  case 2: RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE); break;
	  case 3: RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE); break;
  }
  
  /*config SPI/I2S */
  SPI_InitStruct.SPI_CPOL              = idleLevel ? SPI_CPOL_High    : SPI_CPOL_Low;
  SPI_InitStruct.SPI_CPHA              = secondEdge    ? SPI_CPHA_2Edge   : SPI_CPHA_1Edge;
  SPI_InitStruct.SPI_FirstBit          = firstBitMSB   ? SPI_FirstBit_MSB : SPI_FirstBit_LSB; 
  SPI_InitStruct.SPI_CPHA              = SPI_CPHA_2Edge;
  SPI_InitStruct.SPI_NSS               = SPI_NSS_Soft;
  SPI_InitStruct.SPI_Mode              = SPI_Mode_Master;
  SPI_InitStruct.SPI_DataSize          = SPI_DataSize_8b;
  SPI_InitStruct.SPI_Direction         = direction;
  SPI_InitStruct.SPI_CRCPolynomial     = crcPoly;  
  SPI_InitStruct.SPI_BaudRatePrescaler = prescaler; 
 
  if (0 != spiNum){
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
  }
  return HL_OK;
}



/**
 @overload
 @brief Start SPI peripheral. Operating mode is: firstBitMSB, SPI_2LINES_RX_TX, CRC disable
 @param prescaler Baudrate prescaler of SPI.
 @param idleLevel TRUE : data line is kept at high level in idle state.\n FALSE : data line is kept at low level in idle state.
 @param secondEdge TRUE: data is latched at the second edge.\n FALSE: data is latched at the first edge
 @retval HL_INVALID one or some parameters is invalid. The method is cancel
 @retval HL_OK The method is performed OK
*/
err_t  spi_base_c::Start(spi_prescaler_t prescaler, bool idleLevel, bool secondEdge){
  return Start(prescaler, idleLevel, secondEdge, true, SPI_2LINES_RX_TX, false, GetCRCPoly());
}



/**
 @brief Stop SPI/I2S and then disable its clock
 @return None
*/
void spi_base_c::Shutdown(){
  SPIx->CR1 &= CR1_SPE_Reset;
  switch (spiNum){
    case 1:	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, DISABLE); break;
   	case 2:	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, DISABLE);	break;
	  case 3:	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, DISABLE);	break;
  }
}



/**
 @brief Wait until the output buffer empty and then send one byte
 @param sendData Data to send
 @return None
*/
void spi_base_c::Send(uint8_t sendData){ 
  while (!(SPIx->SR & SPI_I2S_FLAG_TXE)){
    /* wait, DO NOTHING */
  }  
  SPIx->DR = sendData;
}



/**
 @overload 
 @brief Send an array of data
 @param sendBuf Array of data to send
 @param bufLen Length of array of data
 @return None
*/
void spi_base_c::Send(uint8_t sendBuf[], uint16_t bufLen){
  uint16_t index;
  for (index=0; index<bufLen; index++){
    Send(sendBuf[index]);
  }  
}


/**
 @overload
 @brief Send one byte. Wait until data transmision completed and then return receiving data
 @param sendData Data to send
 @return Received data
*/
uint8_t spi_base_c::SendRecv(uint8_t sendData){
	Send(sendData);
  while (!(SPIx->SR & SPI_I2S_FLAG_TXE)){
    /* wait data to send, DO NOTHING */
  }
  while (SPIx->SR & SPI_I2S_FLAG_BSY);{
    /* wait data send completly, get last received data, DO NOTHING */
  }
  return (uint8_t) SPIx->DR;
}



/**
 @overload
 @brief Send one byte. Wait until data transmision completed and then get receiving data
 @param sendData Data to send
 @param recvData Pointer to variable will hold receiving data
 @return None
*/
void spi_base_c::SendRecv(uint8_t sendData, uint8_t *recvData){ 
  Send(sendData);
  while (!(SPIx->SR & SPI_I2S_FLAG_TXE)){
    /* wait data to send, DO NOTHING */
  }
  while (SPIx->SR & SPI_I2S_FLAG_BSY);{
    /* wait data send completly, get last received data, DO NOTHING */
  }
  *recvData = (uint8_t) SPIx->DR;
}



/**
 @overload
 @brief Send and receive arrays of data
 @param sendBuf Array of data to send
 @param recvBuf Pointer to array of data will hold receiving data
 @param bufLen Length of send/receive array of data
 @return None
*/
void spi_base_c::SendRecv(uint8_t sendBuf[], uint8_t recvBuf[], uint16_t bufLen){
  uint16_t index;

  if (bufLen == 0) return;
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
}



/**
 @brief Get current CRC polynomial
 @return Current CRC polynomial
*/
uint16_t spi_base_c::GetCRCPoly(){ 
  return SPIx->CRCPR;
}



/**
 @brief Request sending hardware calculated CRC after current transmission completed
 @return None
*/
void spi_base_c::SendCRC(){ 
  SPIx->CR1 |= CR1_CRCNext_Set;
}      



/**
 @brief Get sending CRC value if CRC feature is enabled
 @return Sending CRC
*/
uint16_t spi_base_c::GetSendCRC(){
  return SPIx->TXCRCR;
}



/**
 @brief Get receiving CRC value if CRC feature is enabled
 @return Receiving CRC
*/
uint16_t spi_base_c::GetRecvCRC(){
  return SPIx->RXCRCR;
}



/**
 @brief Clear calculated CRC to prepare for new transmision
 @return None
 @attention Only use when SPI is not busy or data corruption may happen
*/
void spi_base_c::ClearCRC(){
  SPIx->CR1 &= CR1_SPE_Reset;   //Disable SPI
  SPIx->CR1 &= CR1_CRCEN_Reset; //Disable CRC
  SPIx->CR1 |= CR1_CRCEN_Set;   //Enable CRC
  SPIx->CR1 |= CR1_SPE_Set;     //Enable SPI
} 



/**
 @brief Check SPI busy status
 @return TRUE: SPI is busy. FALSE: SPI is not busy
*/
bool spi_base_c::IsBusy(){
  return (SPIx->SR & SPI_I2S_FLAG_BSY);
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
