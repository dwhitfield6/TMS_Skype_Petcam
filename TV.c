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
#include "TOGGLE.h"
#include "TV.h"
#include "UART.h"
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
static unsigned char SKYPE_AudioProtocol = FALSE;

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
	NumSKYPE = sizeof(SKYPE_Codes) / sizeof(TYPE_SKYPE_CODE);
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
	UART_SendStringCRLNA("");
	UART_SendStringCRLNC("");
	UART_SendStringCRLNA("Changing modes...");
	UART_SendStringCRLNC("Changing modes...");
	LED_SetMode(GREEN_BLINKING);
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

	UART_SendStringCRLNA("Mode = SKYPE");
	UART_SendStringCRLNC("Mode = SKYPE");
	UART_SendStringCRLNA("");
	UART_SendStringCRLNC("");
}

/******************************************************************************/
/* TV_GoToOriginalMode
 *
 * The function puts the TV input to the origian mode before switching to
 *  skype mode.																  */
/******************************************************************************/
void TV_GoToOriginalMode(void)
{
	UART_SendStringCRLNA("");
	UART_SendStringCRLNC("");
	UART_SendStringCRLNA("Changing modes...");
	UART_SendStringCRLNC("Changing modes...");
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

	UART_SendStringCRLNA("Mode = Original");
	UART_SendStringCRLNC("Mode = Original");
	UART_SendStringCRLNA("");
	UART_SendStringCRLNC("");
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
	unsigned short a_low, a_high, a;
	unsigned short b_low, b_high, b;
	unsigned short c_low, c_high, c;
	unsigned short d_low, d_high, d;
	unsigned short e_low, e_high, e;
	unsigned short f_low, f_high, f;
	unsigned short g_low, g_high, g;
	unsigned short h_low, h_high, h;
	unsigned short i_low, i_high, i;
	unsigned short j_low, j_high, j;
	unsigned short c0a_low, c0a_high, c0a;
	unsigned short c0b_low, c0b_high, c0b;
	unsigned short c1a_low, c1a_high, c1a;
	unsigned short c1b_low, c1b_high, c1b;
	unsigned short c0a_i_low, c0a_i_high, c0a_i;
	unsigned long ii;
	unsigned long TotalCodeIndex;
	double AccumulatedTime;
	unsigned char tempcode[2];
	unsigned char code = 0;
	unsigned char tempindex;

	/* look for header burst of 6 bursts. The 6 bursts takes .3 seconds */
	for(ii=0;ii<amount;ii++)
	{
		/* find the sample that corresponds to the end of the 6th burst */
		timeUs += buffer[i].MicroSeconds;
		if(timeUs >= TV_SKYPE_AUDIO_CODE_LENGTH_MICROSECONDS)
		{
			break;
		}
	}
	TotalCodeIndex = ii;

	/*~~~~~~~~~~~~~~~~~~~~~~ First measurement (a to b) ~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/* find first local max location (a) looking right in ProtocolTimingDiagram0.png */
	if(!TV_SKYPE_FindFirstLocalMaximumIncreasing(buffer,0,TotalCodeIndex, &a_low)) // a
	{
		/* couldnt find the local maximum */
		return FAIL;
	}
	if(a_low >= TotalCodeIndex)
	{
		/* cant find valid local max */
		return FAIL;
	}

	/* find first local min location (b) looking right in ProtocolTimingDiagram0.png */
	if(!TV_SKYPE_FindFirstLocalMinimumIncreasing(buffer,a_low,TotalCodeIndex, &b_low)) // b
	{
		/* couldnt find the local maximum */
		return FAIL;
	}
	if(b_low >= TotalCodeIndex)
	{
		/* cant find valid local min */
		return FAIL;
	}

	/* find second local max location (c) in ProtocolTimingDiagram0.png */
	if(!TV_SKYPE_FindFirstLocalMaximumIncreasing(buffer,b_low,TotalCodeIndex, &c_low)) // c
	{
		/* couldnt find the local maximum */
		return FAIL;
	}
	if(c_low >= TotalCodeIndex)
	{
		/* cant find valid local max */
		return FAIL;
	}

	/* find first local max location (a) looking left in ProtocolTimingDiagram0.png */
	if(!TV_SKYPE_FindFirstLocalMaximumDecreasing(buffer,b_low,0, &a_high)) // a
	{
		/* couldnt find the local maximum */
		return FAIL;
	}

	/* find first local min location (b) looking left in ProtocolTimingDiagram0.png */
	if(!TV_SKYPE_FindFirstLocalMinimumDecreasing(buffer,c_low,0, &b_high)) // b
	{
		/* couldnt find the local maximum */
		return FAIL;
	}
	if(b_high == 0)
	{
		/* cant find valid local min */
		return FAIL;
	}

	a = (a_low + a_high) / 2;
	b = (b_low + b_high) / 2;

	AccumulatedTime = TV_SKYPE_AccumulatedTime(buffer, a, b);
	if((AccumulatedTime < (25000.0 * AUDIO_ADC_TIMING_LOW_LIMIT)) || (AccumulatedTime > (25000.0 * AUDIO_ADC_TIMING_HIGH_LIMIT)))
	{
		/* wrong frequency */
		return FAIL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~ Second measurement (b to c) ~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/* find second local min location (d) looking right in ProtocolTimingDiagram0.png */
	if(!TV_SKYPE_FindFirstLocalMinimumIncreasing(buffer,c_low,TotalCodeIndex, &d_low)) // d
	{
		/* couldnt find the local minimum */
		return FAIL;
	}
	if(d_low >= TotalCodeIndex)
	{
		/* cant find valid local min */
		return FAIL;
	}

	/* find second local max location (c) looking left in ProtocolTimingDiagram0.png */
	if(!TV_SKYPE_FindFirstLocalMaximumDecreasing(buffer,d_low,0, &c_high)) // c
	{
		/* couldnt find the local maximum */
		return FAIL;
	}
	if(c_high == 0)
	{
		/* cant find valid local max */
		return FAIL;
	}

	c = (c_low + c_high) / 2;

	AccumulatedTime = TV_SKYPE_AccumulatedTime(buffer, b, c);
	if((AccumulatedTime < (25000.0 * AUDIO_ADC_TIMING_LOW_LIMIT)) || (AccumulatedTime > (25000.0 * AUDIO_ADC_TIMING_HIGH_LIMIT)))
	{
		/* wrong frequency */
		return FAIL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~ Third measurement (c to d) ~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/* find third local max location (e) looking right in ProtocolTimingDiagram0.png */
	if(!TV_SKYPE_FindFirstLocalMaximumIncreasing(buffer,d_low,TotalCodeIndex, &e_low)) // e
	{
		/* couldnt find the local maximum */
		return FAIL;
	}
	if(e_low >= TotalCodeIndex)
	{
		/* cant find valid local max */
		return FAIL;
	}

	/* find second local min location (d) looking left in ProtocolTimingDiagram0.png */
	if(!TV_SKYPE_FindFirstLocalMinimumDecreasing(buffer,e_low,0, &d_high)) // d
	{
		/* couldnt find the local minimum */
		return FAIL;
	}
	if(d_high == 0)
	{
		/* cant find valid local min */
		return FAIL;
	}

	d = (d_low + d_high) / 2;

	AccumulatedTime = TV_SKYPE_AccumulatedTime(buffer, c, d);
	if((AccumulatedTime < (25000.0 * AUDIO_ADC_TIMING_LOW_LIMIT)) || (AccumulatedTime > (25000.0 * AUDIO_ADC_TIMING_HIGH_LIMIT)))
	{
		/* wrong frequency */
		return FAIL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~ forth measurement (d to e) ~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/* find third local max location (e) looking right in ProtocolTimingDiagram0.png */
	if(!TV_SKYPE_FindFirstLocalMaximumIncreasing(buffer,e_low,TotalCodeIndex, &f_low)) // e
	{
		/* couldnt find the local maximum */
		return FAIL;
	}
	if(f_low >= TotalCodeIndex)
	{
		/* cant find valid local max */
		return FAIL;
	}

	/* find third local min location (f) looking left in ProtocolTimingDiagram0.png */
	if(!TV_SKYPE_FindFirstLocalMaximumDecreasing(buffer,f_low,0, &e_high)) // e
	{
		/* couldnt find the local maximum */
		return FAIL;
	}
	if(e_high == 0)
	{
		/* cant find valid local max */
		return FAIL;
	}

	e = (e_low + e_high) / 2;

	AccumulatedTime = TV_SKYPE_AccumulatedTime(buffer, d, e);
	if((AccumulatedTime < (25000.0 * AUDIO_ADC_TIMING_LOW_LIMIT)) || (AccumulatedTime > (25000.0 * AUDIO_ADC_TIMING_HIGH_LIMIT)))
	{
		/* wrong frequency */
		return FAIL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~ forth measurement (e to f) ~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/* find forth local max location (g) looking right in ProtocolTimingDiagram0.png */
	if(!TV_SKYPE_FindFirstLocalMaximumIncreasing(buffer,f_low,TotalCodeIndex, &g_low)) // g
	{
		/* couldnt find the local maximum */
		return FAIL;
	}
	if(g_low >= TotalCodeIndex)
	{
		/* cant find valid local max */
		return FAIL;
	}

	/* find third local min location (f) looking left in ProtocolTimingDiagram0.png */
	if(!TV_SKYPE_FindFirstLocalMinimumDecreasing(buffer,g_low,0, &f_high)) // f
	{
		/* couldnt find the local minimum */
		return FAIL;
	}
	if(f_high == 0)
	{
		/* cant find valid local min */
		return FAIL;
	}

	f = (f_low + f_high) / 2;

	AccumulatedTime = TV_SKYPE_AccumulatedTime(buffer, e, f);
	if((AccumulatedTime < (25000.0 * AUDIO_ADC_TIMING_LOW_LIMIT)) || (AccumulatedTime > (25000.0 * AUDIO_ADC_TIMING_HIGH_LIMIT)))
	{
		/* wrong frequency */
		return FAIL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~ fifth measurement (f to g) ~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/* find forth local min location (h) looking right in ProtocolTimingDiagram0.png */
	if(!TV_SKYPE_FindFirstLocalMinimumIncreasing(buffer,g_low,TotalCodeIndex, &h_low)) // h
	{
		/* couldnt find the local minimum */
		return FAIL;
	}
	if(h_low >= TotalCodeIndex)
	{
		/* cant find valid local min */
		return FAIL;
	}

	/* find forth local max location (g) looking left in ProtocolTimingDiagram0.png */
	if(!TV_SKYPE_FindFirstLocalMaximumDecreasing(buffer,h_low,0, &g_high)) // g
	{
		/* couldnt find the local maximum */
		return FAIL;
	}
	if(g_high == 0)
	{
		/* cant find valid local max */
		return FAIL;
	}

	g = (g_low + g_high) / 2;

	AccumulatedTime = TV_SKYPE_AccumulatedTime(buffer, f, g);
	if((AccumulatedTime < (175000.0 * AUDIO_ADC_TIMING_LOW_LIMIT)) || (AccumulatedTime > (175000.0 * AUDIO_ADC_TIMING_HIGH_LIMIT)))
	{
		/* wrong frequency */
		return FAIL;
	}




	/*~~~~~~~~~~~~~~~~~~~~~~ sixth measurement (g to h) ~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/* find forth local min location (h) in ProtocolTimingDiagram0.png */
	if(!TV_SKYPE_FindFirstLocalMinimumIncreasing(buffer,g,TotalCodeIndex, &h)) // h
	{
		/* couldnt find the local minimum */
		return FAIL;
	}
	if(h >= TotalCodeIndex)
	{
		/* cant find valid local min */
		return FAIL;
	}

	AccumulatedTime = TV_SKYPE_AccumulatedTime(buffer, g, h);
	if((AccumulatedTime < (25000.0 * AUDIO_ADC_TIMING_LOW_LIMIT)) || (AccumulatedTime > (25000.0 * AUDIO_ADC_TIMING_HIGH_LIMIT)))
	{
		/* wrong frequency */
		return FAIL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~ seventh measurement (h to c0a or i) ~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/* find fifth local max location (i or c0a) in ProtocolTimingDiagram0.png */
	if(!TV_SKYPE_FindFirstLocalMaximumIncreasing(buffer,h,TotalCodeIndex, &c0a_i)) // c0a or i
	{
		/* couldnt find the local maximum */
		return FAIL;
	}
	if(c0a_i >= TotalCodeIndex)
	{
		/* cant find valid local max */
		return FAIL;
	}

	AccumulatedTime = TV_SKYPE_AccumulatedTime(buffer, h, c0a_i);
	if((AccumulatedTime >= (25000.0 * AUDIO_ADC_TIMING_LOW_LIMIT)) && (AccumulatedTime <= (25000.0 * AUDIO_ADC_TIMING_HIGH_LIMIT)))
	{
		/* code is starting out as a 1 so use c0a */
		c0a = c0a_i;
		tempcode[0] = 1;
	}
	else if((AccumulatedTime >= (125000.0 * AUDIO_ADC_TIMING_LOW_LIMIT)) && (AccumulatedTime <= (125000.0 * AUDIO_ADC_TIMING_HIGH_LIMIT)))
	{
		/* code is starting out as a 0 so use i */
		i = c0a_i;
		tempcode[0] = 0;
	}
	else
	{
		/*code out of sync */
		return FAIL;
	}

	if(tempcode[0] == 1)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~ optional 1 measurement (c0a to c0b) ~~~~~~~~~~~~~~~~~~~~~~~~~*/
		/* find fifth local min location (c0b) in ProtocolTimingDiagram1.png */
		if(!TV_SKYPE_FindFirstLocalMinimumIncreasing(buffer,c0a,TotalCodeIndex, &c0b)) // c0b
		{
			/* couldnt find the local minimum */
			return FAIL;
		}
		if(c0b >= TotalCodeIndex)
		{
			/* cant find valid local min */
			return FAIL;
		}

		AccumulatedTime = TV_SKYPE_AccumulatedTime(buffer, c0a, c0b);
		if((AccumulatedTime < (25000.0 * AUDIO_ADC_TIMING_LOW_LIMIT)) || (AccumulatedTime > (25000.0 * AUDIO_ADC_TIMING_HIGH_LIMIT)))
		{
			/* wrong frequency */
			return FAIL;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~ eighth measurement (c0b to i) ~~~~~~~~~~~~~~~~~~~~~~~~~*/
		/* find sixth local max location (i) in ProtocolTimingDiagram1.png */
		if(!TV_SKYPE_FindFirstLocalMaximumIncreasing(buffer,c0b,TotalCodeIndex, &i)) // i
		{
			/* couldnt find the local maximum */
			return FAIL;
		}
		if(i >= TotalCodeIndex)
		{
			/* cant find valid local max */
			return FAIL;
		}

		AccumulatedTime = TV_SKYPE_AccumulatedTime(buffer, c0b, i);
		if((AccumulatedTime < (75000.0 * AUDIO_ADC_TIMING_LOW_LIMIT)) || (AccumulatedTime > (75000.0 * AUDIO_ADC_TIMING_HIGH_LIMIT)))
		{
			/* wrong frequency */
			return FAIL;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~ sixth measurement (g to h) ~~~~~~~~~~~~~~~~~~~~~~~~~*/
		/* find forth local min location (h) in ProtocolTimingDiagram0.png */
		if(!TV_SKYPE_FindFirstLocalMinimumIncreasing(buffer,g,TotalCodeIndex, &h)) // h
		{
			/* couldnt find the local minimum */
			return FAIL;
		}
		if(h >= TotalCodeIndex)
		{
			/* cant find valid local min */
			return FAIL;
		}

		AccumulatedTime = TV_SKYPE_AccumulatedTime(buffer, g, h);
		if((AccumulatedTime < (25000.0 * AUDIO_ADC_TIMING_LOW_LIMIT)) || (AccumulatedTime > (25000.0 * AUDIO_ADC_TIMING_HIGH_LIMIT)))
		{
			/* wrong frequency */
			return FAIL;
		}
	}

	/*~~~~~~~~~~~~~~~~~~~~~~ eleventh measurement (i to j) ~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/* find sixth local min location (j) in ProtocolTimingDiagram0.png */
	if(!TV_SKYPE_FindFirstLocalMinimumIncreasing(buffer,i,TotalCodeIndex, &j)) // j
	{
		/* couldnt find the local minimum */
		return FAIL;
	}
	if(j >= TotalCodeIndex)
	{
		/* the minimum is the last entry */
		return FAIL;
	}

	AccumulatedTime = TV_SKYPE_AccumulatedTime(buffer, i, j);
	if((AccumulatedTime < (25000.0 * AUDIO_ADC_TIMING_LOW_LIMIT)) || (AccumulatedTime > (25000.0 * AUDIO_ADC_TIMING_HIGH_LIMIT)))
	{
		/* wrong frequency */
		return FAIL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~ twelth measurement (j to c1a or end) ~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/* find seventh local max location (c1a or end) in ProtocolTimingDiagram0.png */
	if(!TV_SKYPE_FindFirstLocalMaximumIncreasing(buffer,j,TotalCodeIndex, &c1a)) // c1a or end
	{
		/* couldnt find the local maximum */
		tempcode[1] = 0;
		goto END;
	}
	if(c1a >= TotalCodeIndex)
	{
		/* cant find valid local max */
		tempcode[1] = 0;
		goto END;
	}

	AccumulatedTime = TV_SKYPE_AccumulatedTime(buffer, j, c1a);
	if((AccumulatedTime < (25000.0 * AUDIO_ADC_TIMING_LOW_LIMIT)) || (AccumulatedTime > (25000.0 * AUDIO_ADC_TIMING_HIGH_LIMIT)))
	{
		/* wrong frequency */
		return FAIL;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~ thirteenth measurement (c1a to c1b) ~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/* find forth local min location (h) in ProtocolTimingDiagram0.png */
	if(!TV_SKYPE_FindFirstLocalMinimumIncreasing(buffer,c1a,TotalCodeIndex, &c1b)) // c1b
	{
		/* couldnt find the local minimum */
		return FAIL;
	}
	if(c1b >= TotalCodeIndex)
	{
		/* cant find valid local min */
		return FAIL;
	}

	AccumulatedTime = TV_SKYPE_AccumulatedTime(buffer, c1a, c1b);
	if((AccumulatedTime < (25000.0 * AUDIO_ADC_TIMING_LOW_LIMIT)) || (AccumulatedTime > (25000.0 * AUDIO_ADC_TIMING_HIGH_LIMIT)))
	{
		/* wrong frequency */
		return FAIL;
	}
	else
	{
		tempcode[1] = 1;
	}

	END:
	code |= tempcode[1];
	code |= (tempcode[0] << 1);
	for(tempindex = 0; tempindex < NumSKYPE; tempindex++)
	{
		if(codes[tempindex].AudioCode == code)
		{
			*index = tempindex;
			return PASS;
		}
	}

	return FAIL;
}

/******************************************************************************/
/* TV_SKYPE_FindFirstLocalMaximumIncreasing
 *
 * The function searches through an audio stream looking for the first local
 *  maximum increaseing the index (searching right).						  */
/******************************************************************************/
unsigned char TV_SKYPE_FindFirstLocalMaximumIncreasing(TYPE_LOWPASS* buffer, unsigned short start, unsigned short finish, unsigned short* index)
{
	double average = 0.0;
	double sample = 0.0;
	double localmax = 0.0;
	short startingpoint = (short)start;
	short i;
	double temp = 0.0;
	unsigned char count = 0;
	short tempstart = (short) start;
	short tempfinish = (short) finish;

	for(i=tempstart;i<=tempfinish;i++)
	{
		temp = (double) buffer[i].ADC;
		average += temp;
		sample += 1.0;
	}
	average /= sample;

	for(i=tempstart;i<=tempfinish;i++)
	{
		temp = (double) buffer[i].ADC;
		if(temp > average)
		{
			localmax = temp;
			break;
		}
	}
	startingpoint = i;

	for(i=startingpoint;i<=tempfinish;i++)
	{
		temp = (double) buffer[i].ADC;
		if(temp > localmax)
		{
			localmax = temp;
			*index = i;
		}
		if((temp <= localmax) || (i == tempfinish))
		{
			count++;
			if((count > FIND_LOCAL_WRONG_WAY_COUNT) || (i == tempfinish))
			{
				/* we have been traveling in the wrong direction for 20 sample in a row */
				if(localmax >= TV_SKYPE_AUDIO_ADC_HIGH)
				{
					return PASS;
				}
				return FAIL;
			}
		}
		else
		{
			count = 0;
		}

	}
	return FAIL;
}

/******************************************************************************/
/* TV_SKYPE_FindFirstLocalMaximumDecreasing
 *
 * The function searches through an audio stream looking for the first local
 *  maximum decreasing the index (searching left).							  */
/******************************************************************************/
unsigned char TV_SKYPE_FindFirstLocalMaximumDecreasing(TYPE_LOWPASS* buffer, unsigned short start, unsigned short finish, unsigned short* index)
{
	double average = 0.0;
	double sample = 0.0;
	double localmax = 0.0;
	short startingpoint = (short)start;
	short i;
	double temp = 0.0;
	unsigned char count = 0;
	short tempstart = (short) start;
	short tempfinish = (short) finish;

	for(i=tempstart;i>=tempfinish;i--)
	{
		temp = (double) buffer[i].ADC;
		average += temp;
		sample += 1.0;
	}
	average /= sample;

	for(i=tempstart;i>=tempfinish;i--)
	{
		temp = (double) buffer[i].ADC;
		if(temp > average)
		{
			localmax = temp;
			break;
		}
	}
	if(i < 0)
	{
		return FAIL;
	}
	startingpoint = i;

	for(i=startingpoint;i>=tempfinish;i--)
	{
		temp = (double) buffer[i].ADC;
		if(temp > localmax)
		{
			localmax = temp;
			*index = i;
		}
		if(temp <= localmax || (i == 0))
		{
			count++;
			if(count > FIND_LOCAL_WRONG_WAY_COUNT || (i == 0))
			{
				/* we have been traveling in the wrong direction for 20 sample in a row */
				if(localmax >= TV_SKYPE_AUDIO_ADC_HIGH)
				{
					return PASS;
				}
				return FAIL;
			}
		}
		else
		{
			count = 0;
		}

	}
	return FAIL;
}

/******************************************************************************/
/* TV_SKYPE_FindFirstLocalMinimumIncreasing
 *
 * The function searches through an audio stream looking for the first local
 *  minimum increaseing the index (searching right).						  */
/******************************************************************************/
unsigned char TV_SKYPE_FindFirstLocalMinimumIncreasing(TYPE_LOWPASS* buffer, unsigned short start, unsigned short finish, unsigned short* index)
{
	double average = 0.0;
	double sample = 0.0;
	double localmin = 4095.0;
	short startingpoint = (short)start;
	short i;
	double temp = 0.0;
	unsigned char count = 0;
	short tempstart = (short) start;
	short tempfinish = (short) finish;

	for(i=tempstart;i<=tempfinish;i++)
	{
		temp = (double) buffer[i].ADC;
		average += temp;
		sample += 1.0;
	}
	average /= sample;

	for(i=tempstart;i<=tempfinish;i++)
	{
		temp = (double) buffer[i].ADC;
		if(temp < average)
		{
			localmin = temp;
			break;
		}
	}

	startingpoint = i;

	for(i=startingpoint;i<=tempfinish;i++)
	{
		temp = (double) buffer[i].ADC;
		if(temp < localmin)
		{
			localmin = temp;
			*index = i;
		}
		if((temp >= localmin) || (i == tempfinish))
		{
			count++;
			if((count > FIND_LOCAL_WRONG_WAY_COUNT) || (i == tempfinish))
			{
				/* we have been traveling in the wrong direction for 20 sample in a row */
				if(localmin <= TV_SKYPE_AUDIO_ADC_LOW)
				{
					return PASS;
				}
				return FAIL;
			}
		}
		else
		{
			count = 0;
		}
	}
	return FAIL;
}

/******************************************************************************/
/* TV_SKYPE_FindFirstLocalMinimumDecreasing
 *
 * The function searches through an audio stream looking for the first local
 *  minimum decreasing the index (searching left).							  */
/******************************************************************************/
unsigned char TV_SKYPE_FindFirstLocalMinimumDecreasing(TYPE_LOWPASS* buffer, unsigned short start, unsigned short finish, unsigned short* index)
{
	double average = 0.0;
	double sample = 0.0;
	double localmin = 4095.0;
	short startingpoint = (short)start;
	short i;
	double temp = 0.0;
	unsigned char count = 0;
	short tempstart = (short) start;
	short tempfinish = (short) finish;

	for(i=tempstart;i>=tempfinish;i--)
	{
		temp = (double) buffer[i].ADC;
		average += temp;
		sample += 1.0;
	}
	average /= sample;

	for(i=tempstart;i>=tempfinish;i--)
	{
		temp = (double) buffer[i].ADC;
		if(temp < average)
		{
			localmin = temp;
			break;
		}
	}
	if(i < 0)
	{
		return FAIL;
	}
	startingpoint = i;

	for(i=startingpoint;i>=tempfinish;i--)
	{
		temp = (double) buffer[i].ADC;
		if(temp < localmin)
		{
			localmin = temp;
			*index = i;
		}
		if((temp >= localmin) || (i == 0))
		{
			count++;
			if((count > FIND_LOCAL_WRONG_WAY_COUNT) || (i == 0))
			{
				/* we have been traveling in the wrong direction for 20 sample in a row */
				if(localmin <= TV_SKYPE_AUDIO_ADC_LOW)
				{
					return PASS;
				}
				return FAIL;
			}
		}
		else
		{
			count = 0;
		}
	}
	return FAIL;
}

/******************************************************************************/
/* TV_SKYPE_SearchingEnabled
 *
 * The function sets the SKYPE audio sampling state.						  */
/******************************************************************************/
void TV_SKYPE_SearchingEnabled(unsigned char mode)
{
	SKYPE_AudioProtocol = mode;
}

/******************************************************************************/
/* TV_SKYPE_GetSearchingStatus
 *
 * The function gets the SKYPE audio sampling state.						  */
/******************************************************************************/
unsigned char TV_SKYPE_GetSearchingStatus(void)
{
	return SKYPE_AudioProtocol;
}

/******************************************************************************/
/* TV_SKYPE_AccumulatedTime
 *
 * The function calculates the total time from the start index tothe finish
 *  index.																	  */
/******************************************************************************/
double TV_SKYPE_AccumulatedTime(TYPE_LOWPASS* buffer, unsigned short start, unsigned short finish)
{
	double total = 0.0;
	unsigned short i;

	if(start > finish)
	{
		return total;
	}
	for(i = start; i <= finish; i++)
	{
		total += buffer[i].MicroSeconds;
	}
	return total;
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
