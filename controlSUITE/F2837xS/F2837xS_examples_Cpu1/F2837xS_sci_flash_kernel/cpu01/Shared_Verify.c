//###########################################################################
//
// FILE:    Shared_Boot.c
//
// TITLE:   Boot loader shared functions
//
// Functions:
//
//     void   CopyData(void)
//     Uint32 GetLongData(void)
//     void ReadReservedFn(void)
//
//###########################################################################
// $TI Release: F2837xS Support Library v180 $
// $Release Date: Fri Nov  6 16:27:58 CST 2015 $
// $Copyright: Copyright (C) 2014-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "c1_bootrom.h"
#include "F021_F2837xD_C28x.h"
//Include Flash API example header file
#include "flash_programming_c28.h"

// GetWordData is a pointer to the function that interfaces to the peripheral.
// Each loader assigns this pointer to it's particular GetWordData function.
extern uint16fptr GetWordData;

typedef struct
{
   Uint16 status;
   Uint32 address;
}  StatusCode;
extern StatusCode statusCode;

#define NO_ERROR					0x1000
#define BLANK_ERROR					0x2000
#define VERIFY_ERROR				0x3000
#define PROGRAM_ERROR				0x4000
#define COMMAND_ERROR				0x5000

// Function prototypes
void VerifyData(void);
extern Uint32 GetLongData(void);
extern void ReadReservedFn(void);
extern Uint16 SCIA_GetWordData(void);

//#################################################
// void VerifyData(void)
//-----------------------------------------------------
// This routine copies multiple blocks of data from the host
// and verifies that data with the flash in the device.
// An error is returned if the flash is not verified.
//
// Multiple blocks of data are copied until a block
// size of 00 00 is encountered.
//-----------------------------------------------------
void VerifyData()
{
	statusCode.status = NO_ERROR;
	statusCode.address = 0x12346578;

	struct HEADER {
	 Uint16 BlockSize;
	 Uint32 DestAddr;
	} BlockHeader;

	Uint16 wordData;
	Uint16 i;
	Uint16 j;
	Uint16 Buffer[4];
	int fail = 0;

    // Assign GetWordData to the SCI-A version of the
    // function. GetWordData is a pointer to a function.
    GetWordData = SCIA_GetWordData;

	// If the KeyValue was invalid, abort the load
	// and return the flash entry point.
	if (SCIA_GetWordData() != 0x08AA)
	{
		statusCode.status = VERIFY_ERROR;
		statusCode.address = FLASH_ENTRY_POINT;
	}

	ReadReservedFn(); //reads and discards 8 reserved words

	//Uint32 EntryAddr = GetLongData();
	GetLongData();

	// Get the size in words of the first block
	BlockHeader.BlockSize = (*GetWordData)();

	// While the block size is > 0 copy the data
	// to the DestAddr.  There is no error checking
	// as it is assumed the DestAddr is a valid
	// memory location

	EALLOW;
	while(BlockHeader.BlockSize != (Uint16)0x0000)
	{
	   Fapi_StatusType oReturnCheck;
	   Fapi_FlashStatusWordType oFlashStatusWord;
	   //Fapi_FlashStatusType oFlashStatus;
	   BlockHeader.DestAddr = GetLongData();
	   for(i = 0; i < BlockHeader.BlockSize; i += 0)
	   {
		   for(j = 0; j < 4; j++){
			   if(i == BlockHeader.BlockSize){
				   Buffer[j] = 0xFFFF;
			   }
			   else{
				   wordData = (*GetWordData)();
				   Buffer[j] = wordData;
				   i++;
			   }
		   }
		   //check that Buffer is not already all erased data
		   if(!((Buffer[0] == 0xFFFF) && (Buffer[1] == 0xFFFF) && (Buffer[2] == 0xFFFF)
				   && (Buffer[3] == 0xFFFF)))
		   {
				while(Fapi_checkFsmForReady() == Fapi_Status_FsmBusy);
				//oFlashStatus = Fapi_getFsmStatus();
				for(j = 0; j < 4; j += 2)
				{
				   Uint32 toVerify = Buffer[j+1];
				   toVerify = toVerify << 16;
				   toVerify |= Buffer[j];
				   oReturnCheck = Fapi_doVerify((uint32 *)(BlockHeader.DestAddr+j),
						  1,
						  (uint32 *)(&toVerify),
						  &oFlashStatusWord);
				   if(oReturnCheck != Fapi_Status_Success)
				   {
					   if(fail == 0) //first fail
					   {
							statusCode.status = VERIFY_ERROR;
							statusCode.address = oFlashStatusWord.au32StatusWord[0];
					   }
				       fail++;
				   }
				}
		   }
	       BlockHeader.DestAddr += 0x4;
	   }
	   //get the size of the next block
	   BlockHeader.BlockSize = (*GetWordData)();
	}
	EDIS;
	return;
}
