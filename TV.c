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
/* Contains functions for interacting with the Television and for the SKYPE
 *  audio protocol.
 *
 *  The protocol consists of a 20 Hz audio signal (low pass) to form a code.
 *
 *  A burst is a number of 20Hz cycles. For example a burst of 3 is 3 full
 *   20Hz waves. 1 burst is .05 of a second.
 *
 *  A space is 1 .05 seconds rest.
 *
 *  A code consists of these parts:
 *
 *  1) 6 burst header pulse.
 *  2) 3 space
 *  3) 2 bit code (4 possible combinations)
 *     a) for a 0 this consists of 2 spaces followed by 2 bursts.
 *     b) for a 1 this consists of 2 bursts followed by 2 spaces.
 *  4) 5 spaces for sync
 *
 *  A total code takes (6 + 3 + 4*2 + 5) *.05sec = 1.1 seconds
 *
 *  The audio signal source is the input audio stream from the computer
 *   passed through a switched capacitor low pass filter.
 *
 *   *Note a pusle starts at the highest point. aka ---\               /
 *                                                      \             /
 *                                                       \           /
 *                                                        \         /
 *                                                         \       /
 *                                                          \     /
 *                                                           \   /
 *                                                            ---
 *																			  */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "IR.h"
#include "LED.h"
#include "MISC.h"
#include "RELAY.h"
#include "TV.h"
#include "USER.h"

/******************************************************************************/
/* SKYPE codes
 *
 * This is the Skype codes that we receive usignthe audio protocol.
 *                              											  */
/******************************************************************************/
/*~~~~~~~~~~~~~~ Sanyo TV ~~~~~~~~~~~~~~~~~~~~~~~~*/
const TYPE_SKYPE_CODE SKYPE_Codes[] =
{
	{"Call Start",	0x01},
	{"Call End",  	0x02},
};

/******************************************************************************/
/* Private Variable Declaration		                                          */
/******************************************************************************/
static ENUM_SKYPE_MODE TV_Skype_Mode = ORIGINAL;
static unsigned char SKYPE_AudioDecodeFlag = FALSE;

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
ENUM_TV_INPUT Original_TV_inputMode;
ENUM_TV_INPUT Current_TV_inputMode;
unsigned char Original_TV_Power;
unsigned char Current_TV_Power;
unsigned char TV_SKYPE_Audio_Code_Started = FALSE;
double TV_SKYPE_Audio_ProtocolTotalMicroseconds = 0.0;
unsigned char NumSKYPE;

/******************************************************************************/
/* Inline Functions                                                           */
/******************************************************************************/

/******************************************************************************/
/* Functions																  */
/******************************************************************************/

/******************************************************************************/
/* InitTV
 *
 * The function initializes the televison.									  */
/******************************************************************************/
void InitTV(void)
{
	NumSKYPE = sizeof(TYPE_SKYPE_CODE) / sizeof(SKYPE_Codes);
	Original_TV_inputMode = HDMI2;
	Current_TV_inputMode = Original_TV_inputMode;
	Original_TV_Power = ON;
	Current_TV_Power = Original_TV_Power;
}

/******************************************************************************/
/* TV_GoToSkypeMode
 *
 * The function puts the TV input to the mode for skype.					  */
/******************************************************************************/
void TV_GoToSkypeMode(void)
{
	LED_RedLED(OFF);
	LED_GreenLED(ON);
	RLY_MechRelay(ON);
	TV_SetMode(SKYPE);
	if(!Current_TV_Power)
	{
		IR_SendNECWithRepeatASCII("Power", Sanyo);
		MSC_DelayUS(1000000);
		Current_TV_Power = ON;
	}
	while(Current_TV_inputMode != HDMI1)
	{
		IR_SendNECWithRepeatASCII("Source", Sanyo);
		MSC_DelayUS(1000000);
		Current_TV_inputMode++;
		if(Current_TV_inputMode > VIDEO)
		{
			Current_TV_inputMode = HDMI1;
		}
	}
}

/******************************************************************************/
/* TV_GoToOriginalMode
 *
 * The function puts the TV input to the origian mode before switching to
 *  skype mode.																  */
/******************************************************************************/
void TV_GoToOriginalMode(void)
{
	LED_RedLED(ON);
	LED_GreenLED(OFF);
	RLY_MechRelay(OFF);
	TV_SetMode(ORIGINAL);
	if(Original_TV_Power != Current_TV_Power)
	{
		if(Original_TV_Power)
		{
			IR_SendNECWithRepeatASCII("Power", Sanyo);
			Current_TV_Power = OFF;
		}
		else
		{
			IR_SendNECWithRepeatASCII("Power", Sanyo);
			Current_TV_Power = ON;
		}
		MSC_DelayUS(2000000);
	}
	if(Original_TV_inputMode != Current_TV_inputMode)
	{
		while(Original_TV_inputMode != Current_TV_inputMode)
		{
			IR_SendNECWithRepeatASCII("Source", Sanyo);
			MSC_DelayUS(1000000);
			Current_TV_inputMode++;
			if(Current_TV_inputMode > VIDEO)
			{
				Current_TV_inputMode = HDMI1;
			}
		}
	}
}

/******************************************************************************/
/* TV_SetMode
 *
 * The function sets the TV skype mode.										  */
/******************************************************************************/
void TV_SetMode(ENUM_SKYPE_MODE mode)
{
	TV_Skype_Mode = mode;
}

/******************************************************************************/
/* TV_GetMode
 *
 * The function gets the TV skype mode.										  */
/******************************************************************************/
ENUM_SKYPE_MODE TV_GetMode(void)
{
	return TV_Skype_Mode;
}

/******************************************************************************/
/* TV_SKYPE_SetDecodeFlag
 *
 * The function sets the audio skype code decode flag.						  */
/******************************************************************************/
void TV_SKYPE_SetDecodeFlag(unsigned char state)
{
	SKYPE_AudioDecodeFlag = state;
}

/******************************************************************************/
/* TV_SKYPE_SetDecodeFlag
 *
 * The function gets the audio skype code decode flag.						  */
/******************************************************************************/
unsigned char TV_SKYPE_GetDecodeFlag(void)
{
	return SKYPE_AudioDecodeFlag;
}

/******************************************************************************/
/* TV_SKYPE_Decode
 *
 * The function decodes an audio buffer to see if it matches one of the
 *  SKYPE codes. 															  */
/******************************************************************************/
unsigned char TV_SKYPE_Decode(TYPE_LOWPASS* buffer, unsigned short amount, const TYPE_SKYPE_CODE* codes, unsigned char* index)
{
	double timeUs = 0.0;
	unsigned short localindex[6];
	unsigned long i;

	/* look for header burst of 6 bursts. The 6 bursts takes .3 seconds */
	for(i=0;i<amount;i++)
	{
		/* find the sample that corresponds to the end of the 6th burst */
		timeUs += buffer[i].MicroSeconds;
		if(timeUs >= 300000.0)
		{
			break;
		}
	}

	/* find first local max location */
	if(!TV_SKYPE_FindFirstLocalMaximum(buffer,0,i, &localindex[0]))
	{
		/* couldnt find the local maximum */
		return FAIL;
	}
	if(localindex[0] >= i)
	{
		/* cant find valid loacal max */
		return FAIL;
	}
	if((buffer[localindex[0]].MicroSeconds < (50000.0 * 0.9)) || (buffer[localindex[0]].MicroSeconds > (50000.0 * 1.1)))
	{
		/* first pulse of header is out of place */
		return FAIL;
	}
	return TRUE;
}

/******************************************************************************/
/* TV_SKYPE_FindFirstLocalMaximum
 *
 * The function searches through an audio stream looking for the first local
 *  maximum.																  */
/******************************************************************************/
unsigned char TV_SKYPE_FindFirstLocalMaximum(TYPE_LOWPASS* buffer, unsigned short start, unsigned short finish, unsigned short* index)
{
	double average = 0.0;
	double sample = 0.0;
	double localmax = 0.0;
	unsigned short startingpoint = start;
	unsigned short i;
	double temp = 0.0;

	for(i=start;i<finish;i++)
	{
		temp = (double) buffer[i].ADC;
		average += temp;
		sample += 1.0;
	}
	average /= sample;

	for(i=start;i<finish;i++)
	{
		temp = (double) buffer[i].ADC;
		if(temp > average)
		{
			localmax = temp;
			break;
		}
	}
	startingpoint = i;

	for(i=startingpoint;i<finish;i++)
	{
		temp = (double) buffer[i].ADC;
		if(temp > localmax)
		{
			localmax = temp;
		}
		if(temp < average)
		{
			*index = i;
			return PASS;
		}
	}
	return FAIL;
}
/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
