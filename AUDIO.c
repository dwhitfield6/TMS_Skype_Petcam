/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 12/15/15     13.0_DW0a   First coding.
 *                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Contains functions for audio processing. This includes detecting the 20Hz
 *  signal used for the audio protocol.
 *																			  */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "ADC.h"
#include "AUDIO.h"
#include "USER.h"

/******************************************************************************/
/* Private Variable Declaration		                                          */
/******************************************************************************/
static unsigned char AudioSampleReadyFlag = FALSE;

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
unsigned short Audio_ADC_Counts_Buffer[AUDIO_ADC_BUFFER_SIZE];
unsigned short Audio_ADC_Counts_place = 0;
unsigned short AudioProcessingSample;
double AudioProcess1 = 0;
double AudioProcess2 = 0;
ENUM_AUDIO_PROCESSING AudioProcessing;

/******************************************************************************/
/* Inline Functions 														  */
/******************************************************************************/

/******************************************************************************/
/* Functions																  */
/******************************************************************************/

/******************************************************************************/
/* InitAudio
 *
 * The function initializes the audio functionality.	        			  */
/******************************************************************************/
void InitAudio(void)
{
	AudioProcessingSample = 200;
	AUD_Sampling(ON);
	ADC_ForceSampleA(); 		// take next sample
}

/******************************************************************************/
/* AUD_Sampling
 *
 * The function controls ADC sampling for processing.	        			  */
/******************************************************************************/
void AUD_Sampling(unsigned char state)
{
	if(state)
	{
		ADC_InterruptA(ON);
	}
	else
	{
		ADC_InterruptA(OFF);
	}
}

/******************************************************************************/
/* AUD_SetSampleReadyFlag
 *
 * The function returns sets the flag signifying a sample is ready.			  */
/******************************************************************************/
void AUD_SetSampleReadyFlag(void)
{
	AudioSampleReadyFlag = TRUE;
}

/******************************************************************************/
/* AUD_ClearSampleReadyFlag
 *
 * The function returns sets the flag signifying a sample is ready.			  */
/******************************************************************************/
void AUD_ClearSampleReadyFlag(void)
{
	AudioSampleReadyFlag = FALSE;
}

/******************************************************************************/
/* AUD_GetSampleReadyFlag
 *
 * The function returns gets the flag signifying a sample is ready.			  */
/******************************************************************************/
unsigned char AUD_GetSampleReadyFlag(void)
{
	return AudioSampleReadyFlag;
}

/******************************************************************************/
/* AUD_Process
 *
 * The function processes an audio buffer.					       			  */
/******************************************************************************/
void AUD_Process(unsigned short* buffer, unsigned short AmountInBuffer, ENUM_AUDIO_PROCESSING processing, unsigned short AmountToSample, double* result)
{
	double temp1 = 0.0;
	double temp2;
	unsigned short i;

	/* dont overreach the buffer */
	if(AmountToSample > AmountInBuffer)
	{
		AmountToSample = AmountInBuffer;
	}

	switch(processing)
	{
		case AVERAGE:
			for(i=0; i<AmountToSample; i++)
			{
				temp1 += (double) *buffer;
				buffer++;
			}
			temp2 = temp1 / ((double) AmountToSample);
			*result = temp2;
			break;
	}
}

/******************************************************************************/
/* AUD_ShiftoutBuffer
 *
 * The function shifts the buffer a number of places.		       			  */
/******************************************************************************/
void AUD_ShiftoutBuffer(unsigned short* buffer, unsigned short* amount, unsigned short shift)
{
	unsigned short temp = *amount;
	unsigned short i;

	for(i=0; i < (temp - shift); i++)
	{
		buffer[i] = buffer[i + shift];
	}
	buffer[i] = 0;
	*amount -= shift;
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
