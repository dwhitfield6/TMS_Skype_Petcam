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
#include "SYSTEM.h"
#include "TIMERS.h"
#include "USER.h"

/******************************************************************************/
/* Private Variable Declaration		                                          */
/******************************************************************************/
static unsigned char AudioSampleReadyFlag = FALSE;

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
unsigned short Audio_ADC_Counts_Unfiltered_Buffer[AUDIO_ADC_BUFFER_SIZE];
unsigned short Audio_ADC_Counts_Unfiltered_place = 0;
unsigned short AudioProcessingSampleLarge;
unsigned short AudioProcessingSampleSmall;
double AudioProcess1 = 0;
double AudioProcess2 = 0;
ENUM_AUDIO_PROCESSING AudioProcessing;
unsigned int SSRelayOnCount;
unsigned int SSRelayAntiTwitchCount;
TYPE_LOWPASS Audio_ADC_Counts_LowPass_Buffer[LOWPASS_BUFFER_SIZE];
unsigned short Audio_ADC_Counts_LowPass_place;
volatile ENUM_VU AudioVU = ALL;
double AudioTriggerHigh = 1.2;
double AudioTriggerLow = 0.8;

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
	AudioProcessingSampleLarge 	= 200;
	AudioProcessingSampleSmall 	= 20;
	SSRelayAntiTwitchCount		= 20;
	AUD_LOWPASS_Shutdown(OFF);
	AUD_LOWPASS_ClockModulePins(TRUE);
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

/******************************************************************************/
/* AUD_LOWPASS_Shutdown
 *
 * The function controls the shutdown pin of the lowpass filter.  			  */
/******************************************************************************/
void AUD_LOWPASS_Shutdown(unsigned char state)
{
	if(state)
	{
		SYS_WritePin(LOWPASS_SHDN_GPIO, OFF);
	}
	else
	{
		SYS_WritePin(LOWPASS_SHDN_GPIO, ON);
	}
}

/******************************************************************************/
/* AUD_LOWPASS_ClockModulePins
 *
 * The function sets the lowpass audio filters clock pin to PWM mode.		  */
/******************************************************************************/
void AUD_LOWPASS_ClockModulePins(unsigned char state)
{
	SYS_Unlock();
    if(state)
    {
        /* Map the remappable pin */
    	GpioCtrlRegs.GPAGMUX2.bit.GPIO20 = 0b01;	// Configure GPIO20 as EPWM11A
    	GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0b01;		// Configure GPIO20 as EPWM11A
    }
    else
    {
    	GpioCtrlRegs.GPAGMUX2.bit.GPIO20 = 0b00;	// Configure GPIO20 as EPWM11A
    	GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0b00;		// Configure GPIO20 as EPWM11A
    }
	SYS_Lock();
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
