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
static unsigned char AudioSamplingFlag = FALSE;

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
	AudioProcessingSample = 20;
	AUD_Sampling(ON);
}

/******************************************************************************/
/* AUD_Sampling
 *
 * The function controls ADC sampling for processing.	        			  */
/******************************************************************************/
void AUD_Sampling(unsigned char state)
{
	AUD_SetSamplingEnabledFlag(state);

	if(state)
	{
		AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
		ADC_InterruptA(ON);
		ADC_ForceSampleA();
	}
	else
	{
		ADC_InterruptA(OFF);
	}
}

/******************************************************************************/
/* AUD_GetSamplingEnabledFlag
 *
 * The function returns flag used for audio sampling.		       			  */
/******************************************************************************/
void AUD_SetSamplingEnabledFlag(unsigned char state)
{
	if(state)
	{
		AudioSamplingFlag = TRUE;
	}
	else
	{
		AudioSamplingFlag = FALSE;
	}
}

/******************************************************************************/
/* AUD_GetSamplingEnabledFlag
 *
 * The function returns flag used for audio sampling.		       			  */
/******************************************************************************/
unsigned char AUD_GetSamplingEnabledFlag(void)
{
	return AudioSamplingFlag;
}

/******************************************************************************/
/* AUD_Process
 *
 * The function processes an audio buffer.					       			  */
/******************************************************************************/
void AUD_Process(unsigned short* buffer, unsigned short AmountInBuffer, ENUM_AUDIO_PROCESSING processing, unsigned short AmountToSample, double* result)
{
	double temp1;
	double temp2;
	unsigned short i;

	/* dont overreach the buffer */
	if(AmountInBuffer < AmountToSample)
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
