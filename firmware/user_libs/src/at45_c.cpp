#include "hlib.h"
#include "at45_c.h"



////////////////////////////////////////////////////
/* AT45_CSActive and AT45_CSDeactive
 * PRE : sAT45Init.
 * POST : assert/ deassert CS. (PC13)
 * RETVAL : void.
 */

#define AT45_CSActive() GPIO_ResetBits(GPIOC, GPIO_Pin_13)
#define AT45_CSDeactive() 	GPIO_SetBits (GPIOC, GPIO_Pin_13)

////////////////////////////////////////////////////
/* sAT45Init ()
 * PRE : PC10, PC11, PC12, PC13 hasn't been used for others functions.
 * POST : Enable clock for SPI3, GPIOC; Remap SPI3 and Init PC10, 11, 12, 13 use as SPI3_SCK, SPI3_MISO, SPI3_MOSI, SD_CS; 
 * Deassert CS.
 * Init SPI3 and enable SPI3.
 * RETVAL : void.
 */
void at45_c::Start (){
	SPI_InitTypeDef SPI3_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	/* Enable clock for SPI3, and GPIO PC */
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOC, ENABLE);
	
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_SPI3, ENABLE);
	
	/* Init PC13*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init (GPIOC, &GPIO_InitStruct);
	
	/* Init PC10/SPI3_SCK */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init (GPIOC, &GPIO_InitStruct);
	
	/* Init PC11/SPI3_MISO */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init (GPIOC, &GPIO_InitStruct);
	
	/* Init PC12/SPI3_MOSI */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init (GPIOC, &GPIO_InitStruct);
	
	/** End enable clock and Init for GPIOC P10, P11, P12, P13 and SPI3 */
	
	/* Remap GPIOC, SPI3 */
	GPIO_PinRemapConfig(GPIO_Remap_SPI3, ENABLE);
	/* End Remap, PC13 use as SD_CS_N */
	
	/* Init SPI3 */

	SPI3_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI3_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI3_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI3_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	SPI3_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
	SPI3_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI3_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI3_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI3_InitStruct.SPI_CRCPolynomial = 7;
	
	SPI_Init(SPI3, &SPI3_InitStruct);
	
//	SPI_NSSInternalSoftwareConfig (SPI3, SPI_NSSInternalSoft_Set);
	GPIO_SetBits (GPIOC, GPIO_Pin_13);
	
	SPI_Cmd (SPI3, ENABLE);
	
	/* End Init */
}

/* sendNGetAByte (uint8_t aByte)
 * PRE : sAT45Init () .
 * POST : Send aByte out SPI3 and get a byte from SPI3.
 * RETVAL : a byte from SPI3.
 */
uint8_t at45_c::SnGAByte (uint8_t aByte){
	while(SPI_I2S_GetFlagStatus (SPI3, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData (SPI3, aByte);	
	
	while(SPI_I2S_GetFlagStatus (SPI3, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData (SPI3);
}



/** High level function **/

/* AT45_Buffer_Write (uint32_t BufferX, uint32_t Address, uint8_t * BufferWrite_ptr, uint32_t n)
 * PRE : sAT45Init, CS is not asserted, n <= size of BufferWrite, BufferX can be only 1 or 2.
 * POST : Write n byte from BufferWrite_ptr to BufferX begin with address in Address; deassert CS after send.
 * RETVAL : sAT_EC :
 *	- AT45_Buffer_Write_Success.
 *	- AT45_Buffer_Write_Out_of_Range: if Address + n > 264 (BufferX's size = 264).
 *	- AT45_Buffer_Write_Not_A_Buff: if BufferX is not 1 or 2.
 */
at45_ec_t at45_c::Buffer_Write (uint32_t BufferX, uint32_t Address, uint8_t * BufferWrite_ptr, uint32_t n){
	uint8_t opcode;
	uint8_t AH, AL;
	uint32_t numOfByteSended;
	/* Check conditions */
	if(BufferX != 1 && BufferX != 2)
		return AT45_Buffer_Write_Not_A_Buff;
	
	if (( Address + n) > 264)
		return AT45_Buffer_Write_Out_of_Range;
	/* end check, BufferX ok, Address, n ok, BufferWrite_ptr not check */
	
	/* Assert CS */
	AT45_CSActive ();
	
	/* Send opcode */
	if (BufferX == 1)
		opcode = AT45_Buffer1_Write;
	else
		opcode = AT45_Buffer2_Write;
	
	AT45_SnGAByte (opcode);
	
	/* calculate Address and send Address */
	AH = (uint8_t) ( (Address & 0x0000FF00) >> 8 );
	AL = (uint8_t) ( Address & 0x000000FF );
	
	AT45_SnGAByte (AT45_DUMMY_BYTE);
	AT45_SnGAByte (AH);
	AT45_SnGAByte (AL);
	
	/* Send Data */
	numOfByteSended = 0;
	while(numOfByteSended < n){
		AT45_SnGAByte ( BufferWrite_ptr[numOfByteSended] );
		
		numOfByteSended ++;
	}
	
	/* Deassert CS */
	AT45_CSDeactive();
	
	return AT45_Buffer_Write_Success;
}

/* AT45_Buffer_Read (uint32_t BufferX, uint32_t Address, uint8_t * BufferRead_ptr, uint32_t n)
 * PRE : sAT45Init, CS is not asserted, n <= BufferRead's size, BufferX can be only 1 or 2.
 * POST : n byte from BufferX is read to BufferRead, begin with Address is @ of BufferX, deassert CS.
 * RETVAL : at45_ec_t
 *	- AT45_Buffer_Read_Not_A_Buff : if BufferX is not 1 or 2.
 *	- AT45_Buffer_Read_Out_of_Range : if Address + n > 264.
 *	- AT45_Buffer_Read_Success.
 * NOTE : Read at HIGH FREQUENCY.
 */
at45_ec_t at45_c::Buffer_Read (uint32_t BufferX, uint32_t Address, uint8_t * BufferRead_ptr, uint32_t n){
	uint8_t opcode, AH, AL;
	uint32_t numOfByteReceived = 0;
	/* check conditions */
	if(BufferX != 1 && BufferX != 2)
		return AT45_Buffer_Read_Not_A_Buff;
	if( (Address + n) > 264 ) 
		return AT45_Buffer_Read_Out_of_Range;
	/* End check conditions, BufferX ok, Address, n ok, BufferRead_ptr not check */
	
	/* assert CS */
	AT45_CSActive();
	
	/* Send Read opcode */
	if(BufferX == 1)
		opcode = AT45_Buffer1_Read_HF;
	else
		opcode = AT45_Buffer2_Read_HF;
	
	AT45_SnGAByte (opcode);
	
	/* Caculate and send Address */
	AH = (uint8_t) ( (Address & 0x0000FF00) >> 8 );
	AL = (uint8_t) ( Address & 0x000000FF );
	
	AT45_SnGAByte (AT45_DUMMY_BYTE);
	AT45_SnGAByte (AH);
	AT45_SnGAByte (AL);
	AT45_SnGAByte (AT45_DUMMY_BYTE);
	/* Get Data */	
	while(numOfByteReceived < n){
		BufferRead_ptr[numOfByteReceived] = AT45_SnGAByte (AT45_DUMMY_BYTE);
		
		numOfByteReceived ++;
	}
	
	/* Deassert CS */
	AT45_CSDeactive();
	
	return AT45_Buffer_Read_Success;
}

/* AT45_Status_Register_Read (uint32_t CSLowAfter)
 * PRE : sAT45Init, CS is HIGH.
 * POST : read status register and remain CS Low if CSLowAfter > 0, otherwise, CS will be deasserted before return.
 * RETVAL : status register's value.
 * NOTE : if CS remain Low after return, we can receive updated status Register just by AT45_SnGAByte (Dummy), and remember to 
 * CS_High() after finish with this.
 */
uint8_t at45_c::Status_Register_Read (uint32_t CSLowAfter){
	uint8_t statusReg;
	
	/* assert CS */
	AT45_CSActive ();
	
	/* Send opcode */
	AT45_SnGAByte (AT45_Status_Register_Read_cmd);
	
	/* Get status register */
	statusReg = AT45_SnGAByte (AT45_DUMMY_BYTE);
	
	/* Deassert or Not */
	if(CSLowAfter == 0)
		AT45_CSDeactive ();
	
	return statusReg;
}

/* AT45_Buffer_to_MainMemory (uint32_t BufferX, uint32_t PageAddress)
 * PRE : sAT45Init, CS is High, BufferX can be only 1 or 2, PageAddress in [0, 2047], BufferX has the data we need.
 * POST : check status reg and wait until AT45 is not busy, then write BufferX to page with PageAddress.
 * RETVAL : at45_ec_t
 *	- AT45_Buffer2Main_Success.
 *	- AT45_Buffer2Main_Out_of_Range : if Page Address is not in [0, 2047].
 *	- AT45_Buffer2Main_Not_A_Buff : if BufferX is not 1 or 2.
 */
at45_ec_t at45_c::Buffer_to_MainMemory (uint32_t BufferX, uint32_t PageAddress){
	uint8_t opcode, PAH, PAM, PAL;
	/* check conditions */
	if(BufferX != 0 && BufferX != 1)
		return AT45_Buffer2Main_Not_A_Buff;
	if( (PageAddress > 2047) )
		return AT45_Buffer2Main_Out_of_Range;
	/* end check : BufferX ok, PageAddress ok */
	
	/* check status reg and wait until AT45 is not busy, deassert CS */
	if (  ( (AT45_Status_Register_Read (1)) & 0x80) == 0x00 )
		while ( (AT45_SnGAByte (AT45_DUMMY_BYTE) & 0x80) == 0x00 );
	
	AT45_CSDeactive();
	/* AT45 is ready */
	
	/* assert CS and send opcode */
	AT45_CSActive ();
	
	if(BufferX == 1)
		opcode = AT45_Buffer1_to_Main_wBIn_Erase;
	else
		opcode = AT45_Buffer2_to_Main_wBIn_Erase;
	
	AT45_SnGAByte (opcode);
	
	/* caculate and send address */
	PageAddress = PageAddress << 9 ;
	PAH = (uint8_t) ( (PageAddress & 0x00FF0000) >> 16);
	PAM = (uint8_t) ( (PageAddress & 0x0000FF00) >> 8 );
	PAL = (uint8_t) (PageAddress & 0x000000FF);
	
	AT45_SnGAByte (PAH);
	AT45_SnGAByte (PAM);
	AT45_SnGAByte (PAL);
	
	/* deassert CS to begin */
	AT45_CSDeactive ();
	
	/* check status reg and wait until AT45 is not busy, deassert CS */
	if (  ( (AT45_Status_Register_Read (1)) & 0x80) == 0x00 )
		while ( (AT45_SnGAByte (AT45_DUMMY_BYTE) & 0x80) == 0x00 );
	
	AT45_CSDeactive();
	/* AT45 is ready */
	
	return AT45_Buffer2Main_Success;	
}

/* AT45_Continuous_Array_Read_HF (uint32_t PageAddress, uint32_t ByteAddress, uint8_t * BufferRead_ptr, uint32_t n)
 * PRE : sAT45Init, CS is HIGH, buadrate < 66MHz.
 * POST : check AT45 is ready or not, assert CS, read n byte begin with Address and write to BufferRead, deassert CS.
 * RETVAL : at45_ec_t
 *	- AT45_Cont_Array_Read_Success.
 *	- AT45_Cont_Array_Read_OutOfRange_Byte : if byte address > 263.
 *	- AT45_Cont_Array_Read_OutOfRange_Page : if page address > 2047.
 * NOTE : if Address + n is to lagre it will read to the end of Array then continue read from begin of Array, be careful.
 */
at45_ec_t at45_c::Continuous_Array_Read_HF (uint32_t PageAddress, uint32_t ByteAddress, uint8_t * BufferRead_ptr, uint32_t n){
	uint32_t numOfByteReceived = 0;
	uint32_t Address;
	/* check conditions */
	if( ByteAddress > 263 )
		return AT45_Cont_Array_Read_OutOfRange_Byte;
	if( PageAddress > 2047)
		return AT45_Cont_Array_Read_OutOfRange_Page;
	/* end check, Page Address ok, Byte Address ok */
	
	/* check status reg and wait until AT45 is not busy, deassert CS */
	if (  ( (AT45_Status_Register_Read (1)) & 0x80) == 0x00 )
		while ( (AT45_SnGAByte (AT45_DUMMY_BYTE) & 0x80) == 0x00 );
	
	AT45_CSDeactive();
	/* AT45 is ready */
	
	/* assert CS */
	AT45_CSActive();
	
	/* send opcode */
	AT45_SnGAByte (AT45_Cont_Array_Read_HF);
	
	/* send Address */
	Address = (PageAddress << 9) | ByteAddress;
	
	AT45_SnGAByte ( (uint8_t) ( (Address & 0x00FF0000) >> 16) );
	AT45_SnGAByte ( (uint8_t) ( (Address & 0x0000FF00) >> 8 ) );
	AT45_SnGAByte ( (uint8_t) (Address & 0x000000FF) );
	AT45_SnGAByte (AT45_DUMMY_BYTE);
	
	/* get data */
	while (numOfByteReceived < n){
		BufferRead_ptr[numOfByteReceived] = AT45_SnGAByte (AT45_DUMMY_BYTE);
		
		numOfByteReceived ++;
	}
	
	/* deassert CS */
	AT45_CSDeactive();
	
	return AT45_Cont_Array_Read_Success;
}
/* AT45_Read_HA_or_LA (uint32_t HAorLA, uint32_t * PageAddress, uint32_t * ByteAddress)
 * PRE : sAT45Init, CS is HIGH. (HAorLA > 0 then read HA, = 0 then read RA).
 * POST : get HA (first 3 byte in page 0) or LA (next 3 byte in page 0), return in PageAddress and ByteAddress, deassert CS.
 * RETVAL : at45_ec_t
 *	- AT45_Success or AT45_Failed.
 */
at45_ec_t at45_c::Read_HA_or_LA (uint32_t HAorLA, uint32_t * PageAddress, uint32_t * ByteAddress){
	uint8_t TempBuffer[6];
	/* Read first 6 bytes of page 0 */
	AT45_Continuous_Array_Read_HF (0, 0, TempBuffer, 6);
	/* Caculate HA and LA */
	if(HAorLA > 0){//Read HA
		(*PageAddress) = ( (uint32_t) TempBuffer[2] ) << 8;
		(*PageAddress) = ( (*PageAddress) | (uint32_t) TempBuffer[1] ) >> 1;

		(*ByteAddress) = ( (uint32_t) (TempBuffer[1] & 0x01) ) << 8;
		(*ByteAddress) = (*ByteAddress) | TempBuffer[0];
	}
	else{ // Read LA
		(*PageAddress) = ( (uint32_t) TempBuffer[5] ) << 8;
		(*PageAddress) = ( (*PageAddress) | (uint32_t) TempBuffer[4] ) >> 1;

		(*ByteAddress) = ( (uint32_t) (TempBuffer[4] & 0x01) ) << 8;
		(*ByteAddress) = (*ByteAddress) | TempBuffer[3];
	}
	
	return AT45_Success;
}
/* AT45_Write_HA_or_LA (uint32_t HAorLA, uint32_t PageAddress, uint32_t ByteAddress)
 * PRE : sAT45Init, CS is HIGH.
 * POST : Write back PageAddress and ByteAddress of HA (HAorLA > 0) or LA (HAorLA == 0), CS is HIGH.
 * RETVAL : at45_ec_t
 *	- AT45_Success.
 */
at45_ec_t at45_c::Write_HA_or_LA (uint32_t HAorLA, uint32_t PageAddress, uint32_t ByteAddress){
	uint8_t TempBuffer[6];
	uint32_t Address;
	
	AT45_Continuous_Array_Read_HF (0, 0, TempBuffer, 6);
	
	if(HAorLA > 0){
		Address = (PageAddress << 9) | ByteAddress;
		TempBuffer[2] = (uint8_t) ( (Address & 0x00FF0000) >> 16);
		TempBuffer[1] = (uint8_t) ( (Address & 0x0000FF00) >> 8);
		TempBuffer[0] = (uint8_t) (Address & 0x000000FF);
		
		AT45_Buffer_Write (1, 0, TempBuffer, 6);
		AT45_Buffer_to_MainMemory (1, 0);
	}
	else{ 
		Address = (PageAddress << 9) | ByteAddress;
		TempBuffer[5] = (uint8_t) ( (Address & 0x00FF0000) >> 16);
		TempBuffer[4] = (uint8_t) ( (Address & 0x0000FF00) >> 8);
		TempBuffer[3] = (uint8_t) (Address & 0x000000FF);
		
		AT45_Buffer_Write (1, 0, TempBuffer, 6);
		AT45_Buffer_to_MainMemory (1, 0);
	}
	
	return AT45_Success;
}

/* AT45_NewFile
 * PRE : sAT45Init, CS is HIGH.
 * POST : for begin write a new file, init LA and HA : PageAddress = 1, ByteAddress = 0.
 */
void at45_c::NewFile (){
	AT45_Write_HA_or_LA (0, 1, 0);
	AT45_Write_HA_or_LA (1, 1, 0);
	return;
}

/* at45_ec_t AT45_Write_Next (uint8_t * BufferWrite, uint32_t n) (STILL TOO BUGGY!!!)
 * PRE : sAT45Init, CS is HIGH.
 * POST : Write n bytes from BufferWrite to Buffer1 begin with address in HA-ByteAddress, when Buffer1 is full (264 bytes) then
 * write Buffer1 to Main Memory with page address HA-PageAddress, update HA.
 * RETVAL : at45_ec_t
 *	- AT45_Write_Next_OverFlow : if HA-PageAddress == 2047 and HByteAddress + n > 264, no write.
 *	- AT45_Success.
 */
at45_ec_t at45_c::Write_Next (uint8_t * BufferWrite, uint32_t n){
	uint32_t HPageAddress, HByteAddress;
	uint32_t NumOfBytesWrite;
	
	/* Read HA */
	AT45_Read_HA_or_LA (1, &HPageAddress, &HByteAddress);
	
	/* if HByteAddress + n > 264 then write (264-HByteAddress) bytes, flush Buffer1 to main, update HPageAddress, and begin write Buffer 1 from begin */
	while( (HByteAddress + n) > 264){
		
		/* check conditions */
		if( (HPageAddress == 2047) && (HByteAddress + n > 264) ){
			AT45_Write_HA_or_LA (1, HPageAddress, HByteAddress);			
			return AT45_Write_Next_OverFlow;
		}
		
		NumOfBytesWrite = 264-HByteAddress;
		
		AT45_Buffer_Write (1, HByteAddress, BufferWrite, NumOfBytesWrite );
		
		AT45_Buffer_to_MainMemory (1, HPageAddress);
		HPageAddress ++;
		
		BufferWrite += NumOfBytesWrite;
		n -= NumOfBytesWrite;
		HByteAddress = 0;
	} /* end while : HByteAddress + n < 264 */

	AT45_Buffer_Write (1, HByteAddress, BufferWrite, n);
	HByteAddress = ( HByteAddress + n ) % 264;
	
//	AT45_Write_HA_or_LA (1, HPageAddress, HByteAddress);
	
	return AT45_Success;
}

/* AT45_EndFile
 * PRE : sAT45Init, Buffer 1 is not full.
 * POST : flush buffer 1 to main.
 */
void at45_c::EndFile (void){
	uint32_t PageAddress, ByteAddress;
	
	AT45_Read_HA_or_LA (1, &PageAddress, &ByteAddress);
	
	AT45_Buffer_to_MainMemory (1, PageAddress);
	
	return;
}

/* AT45_Write_Next_aPage (uint8_t * BufferWrite)
 * PRE : sAT45Init, AT45_NewFile.
 * POST : Write 264 bytes of BufferWrite to page with address in HA-PageAdress, update HA-PageAddress.
 * RETVAT : at45_ec_t
 *	- AT45_Write_Next_OverFlow : if HA-PageAddress is already = 2047, no write.
 *	- AT45_Success.
 */
at45_ec_t at45_c::Write_Next_aPage (uint8_t * BufferWrite){
	uint32_t PageAddress, ByteAddress;
	
	/* Read HA */
	AT45_Read_HA_or_LA (1, &PageAddress, &ByteAddress);
	/* check conditions */
	if (PageAddress == 2047)
		return AT45_Write_Next_OverFlow;
	
	/* Write 264 bytes to buffer 1 then write to main */
	AT45_Buffer_Write (1, 0, BufferWrite, 264);
	AT45_Buffer_to_MainMemory (1, PageAddress);
	
	/* update PageAddress */
	PageAddress ++;
	AT45_Write_HA_or_LA (1, PageAddress, ByteAddress);
	
	return AT45_Success;	
}

/* AT45_Read (uint32_t PageAddress, uint32_t ByteAddress, uint8_t * BufferRead, uint32_t n) */
at45_ec_t at45_c::Read (uint32_t PageAddress, uint32_t ByteAddress, uint8_t * BufferRead, uint32_t n){
	return Continuous_Array_Read_HF (PageAddress, ByteAddress, BufferRead, n);
}

