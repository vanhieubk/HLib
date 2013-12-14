#ifndef __AT45_C_H
#define __AT45_C_H

/** define command opcode n dummy byte **/
/* Note : just a basic cmds, for more read AT45DB041D datasheet */
//Read cmd.
#define AT45_CONT_ARR_READ_HF 	0x0B
#define AT45_BUF1_READ_HF 			0xD4
#define AT45_BUF2_READ_HF 			0xD6

//Program and Erase cmd.
#define AT45_BUF1_WRITE 				0x84
#define AT45_BUF2_WRITE 				0x87

#define AT45_BUF1_TO_MEM_WBIN_ERASE			0x83
#define AT45_BUF2_TO_MEM_WBIN_ERASE	 		0x86
#define AT45_BUF1_TO_MEM_NO_BIN_ERASE  	0x88
#define AT45_BUF2_TO_MEM_NO_BIN_ERASE 	0x89
#define AT45_MEM_PROGRAM_THROUGH_BUF1 	0x82
#define AT45_MEM_PROGRAM_THROUGH_BUF2 	0x85

//Additional cmd.
#define AT45_ID_READ 0x9F
#define AT45_STATUS_REGISTER_READ				 0xD7

//Dummy byte.
#define AT45_DUMMY_BYTE 0xA5


/** Define AT45_Error_code **/
typedef enum{
	//Buffer read error codes.
	AT45_Buffer_Read_Success = 0,
	AT45_Buffer_Read_Out_of_Range = 2,
	AT45_Buffer_Read_Not_A_Buff = 3,
	
	//Buffer write error codes.
	AT45_Buffer_Write_Success = 10,
	AT45_Buffer_Write_Overflow = 11,
	AT45_Buffer_Write_Out_of_Range = 12,
	AT45_Buffer_Write_Not_A_Buff = 13,
	
	//Buffer to Main memory error codes.
	AT45_Buffer2Main_Success = 20,
	AT45_Buffer2Main_Out_of_Range = 22,
	AT45_Buffer2Main_Not_A_Buff = 23,
	
	//Cont Array read error codes.
	AT45_Cont_Array_Read_Success = 30,
	AT45_Cont_Array_Read_OutOfRange_Byte = 32,
	AT45_Cont_Array_Read_OutOfRange_Page = 33,
	
	//Write next error codes.
	AT45_Write_Next_OverFlow = 41,
	
	// Genernal error codes.
	AT45_Success = 90,
	AT45_Failed = 91
} at45_ec_t;
/** End define Error_code **/

/** Define Functions **/

class at45_c{
	at45_c();
  void 			Start(void);
	uint8_t 	Status_Register_Read (uint32_t);
  uint8_t 		SnGAByte (uint8_t);
  /* High level functions */
  
	at45_ec_t 	Buffer_Write (uint32_t , uint32_t, uint8_t *, uint32_t);
  at45_ec_t 	Buffer_Read (uint32_t, uint32_t, uint8_t *, uint32_t);

  at45_ec_t 	Buffer_to_MainMemory (uint32_t, uint32_t);
at45_ec_t 	Continuous_Array_Read_HF (uint32_t, uint32_t, uint8_t *, uint32_t);

/* Wrap-up functions */
at45_ec_t 	Read_HA_or_LA (uint32_t HAorLA, uint32_t * PageAddress, uint32_t * ByteAddress);
at45_ec_t 	Write_HA_or_LA (uint32_t HAorLA, uint32_t PageAddress, uint32_t ByteAddress);

void 				NewFile (void);
void 				EndFile (void);
at45_ec_t 	Write_Next (uint8_t * BufferWrite, uint32_t n); /* Still too buggy ! */
at45_ec_t 	Write_Next_aPage (uint8_t * BufferWrite);
at45_ec_t 	Read (uint32_t PageAddress, uint32_t ByteAddress, uint8_t * BufferRead, uint32_t n);
};

#endif //__AT45_C_H
