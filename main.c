/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 01/18/16     13.0_DW0a   New project creation.
 * 							Added IR send and commands.
 *                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Contains main function.
 *                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "ADC.h"
#include "AUDIO.h"
#include "BUTTON.h"
#include "CMD.h"
#include "IR.h"
#include "LED.h"
#include "MISC.h"
#include "RELAY.h"
#include "SYSTEM.h"
#include "TV.h"
#include "UART.h"
#include "USER.h"

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Global Variable                                                            */
/******************************************************************************/

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int main (void)
{
	unsigned char index;
	unsigned char IR_repeat_times;
	unsigned long temp_NEC = 0;
	unsigned char IR_process;

	/* initialize pins and clocks */
    SYS_Interrupts(OFF);
	SYS_ConfigureOscillator();
    SYS_ClearPIE();

    /* Disable CPU interrupts and clear all CPU interrupt flags */
	IER = 0x0000;
	IFR = 0x0000;

	/* set up the Peripheral interupts */
	SYS_PerInterrupts(ON);

	/* Enable global Interrupts and higher priority real-time debug events */
	SYS_Interrupts(ON);
	SYS_EnableRealTime();

	/* initialize the GPIO pins */
	Init_Pins();

	/* initialize the hardware modules */
	Init_Modules();

	/* print banner */
	UART_SendBanner();

	/* print prompt */
	UART_SendPrompt();

	/* start sampling */
	AUD_Sampling(ON);
	ADC_ForceSampleA(); 		// take next sample
	AUD_Sampling(ON);
	ADC_ForceSampleA(); 		// take next sample
	AUD_Sampling(ON);
	ADC_ForceSampleA(); 		// take next sample

	/* throw away first samples */
	Audio_ADC_Counts_Unfiltered_place = 0;

    while(1)
    {
    	/* check for a new entered UART command */
    	if(CMD_GetNewCommandFlag())
    	{
    		/* process new command */
    		if(!CMD_CheckMatch(CommandString, Commands, LARGEST_COMMAND))
    		{
    			UART_SendStringCRLN(BAD_COMMAND);
    		}
    		else
    		{
    			UART_SendStringCRLN("");
    		}
    		CMD_SetNewCommandFlag(FALSE);
			UART_SendPrompt();
    	}

    	/* check for a new IR code received */
    	if(IR_GetReceiveFlag())
    	{
    		/* a new IR code was received */
    		IR_process = FALSE;
    		if(IR_ProcessReceiveNEC(&temp_NEC))
    		{
				if(temp_NEC != 0xFFFFFFFF)
				{
					IR_repeat_times = 0;
					NEC = temp_NEC;
					IR_process = TRUE;
				}
				else
				{
					if(IR_repeat_times >= TV_REPEAT_NEC_TIMES)
					{
						IR_repeat_times = 0;
						IR_process = TRUE;
					}
					IR_repeat_times++;
				}
				sprintf((char*)SPRINTBuffer, "Received IR NEC code: 0x%lx", temp_NEC);
				UART_SendStringCRLN(SPRINTBuffer);

				if(IR_process)
				{
					/* check the Known codes */
					if(IR_CheckForNECMatch(NEC, Sanyo, &index))
					{
						/* Sanyo match */
						UART_SendString("Sanyo code : ");
						UART_SendStringCRLN((unsigned char*)Sanyo[index].Description);
						if(MSC_StringMatch((unsigned char*)Sanyo[index].Description, "Source"))
						{
							Original_TV_inputMode++;
							if(Original_TV_inputMode > VIDEO)
							{
								Original_TV_inputMode = HDMI1;
							}
						}
						else if(MSC_StringMatch((unsigned char*)Sanyo[index].Description, "Back"))
						{

							if(Original_TV_inputMode == HDMI1)
							{
								Original_TV_inputMode = VIDEO;
							}
							else
							{
								Original_TV_inputMode--;
							}
						}
						else if(MSC_StringMatch((unsigned char*)Sanyo[index].Description, "Power"))
						{
							if(Original_TV_Power)
							{
								Original_TV_Power = FALSE;
							}
							else
							{
								Original_TV_Power = TRUE;
							}
						}
					}
					else if(IR_CheckForNECMatch(NEC, Visio, &index))
					{
						/* Visio match */
						UART_SendString("Visio code : ");
						UART_SendStringCRLN((unsigned char*)Visio[index].Description);
					}
					else if(IR_CheckForNECMatch(NEC, Idylis, &index))
					{
						/* Idylis match */
						UART_SendString("Idylis code : ");
						UART_SendStringCRLN((unsigned char*)Idylis[index].Description);
					}
				}
    		}
    		memset(IR_Receive_Timing_Counts, 0, MAX_IR_RECEIVE_EVENTS);
    		memset(IR_Receive_Timing_MicroSeconds, 0, MAX_IR_RECEIVE_EVENTS);
    		IR_NEC_Start = FALSE;
    		IR_ReceiverInterrupt(ON);
    		IR_ClearReceiveFlag();
    	}

    	/* check for a new audio sample received */
    	if(AUD_GetSampleReadyFlag())
    	{
    		/* a new audio sample was received and put in the buffer */
    		if(Audio_ADC_Counts_Unfiltered_place >= AudioProcessingSampleLarge)
    		{
				if(AudioProcessing == AVERAGE)
				{
					AUD_Process(Audio_ADC_Counts_Unfiltered_Buffer, Audio_ADC_Counts_Unfiltered_place, AVERAGE, AudioProcessingSampleLarge, &AudioProcess1); 	// long average
					AUD_Process(&Audio_ADC_Counts_Unfiltered_Buffer[AudioProcessingSampleLarge - AudioProcessingSampleSmall - 1], Audio_ADC_Counts_Unfiltered_place, AVERAGE, AudioProcessingSampleSmall, &AudioProcess2);						// short average
					if((AudioProcess2 > (AudioProcess1 * 1.1)) || (AudioProcess2 < (AudioProcess1 * 0.9)))
					{
						SSRelayOnCount = SSRelayAntiTwitchCount;
					}
					else
					{
						if(SSRelayOnCount > 1)
						{
							SSRelayOnCount--;
						}
					}
					if(SSRelayOnCount)
					{
						#ifdef SOLID_STATE_RELAY_WITH_ZEROCROSS_DETECTION
							RLY_SetSSRelayDutyCycle(100);
						#endif
					}
					else
					{
						#ifdef SOLID_STATE_RELAY_WITH_ZEROCROSS_DETECTION
							RLY_SetSSRelayDutyCycle(0);
						#endif
					}
					AUD_ShiftoutBuffer(Audio_ADC_Counts_Unfiltered_Buffer, &Audio_ADC_Counts_Unfiltered_place, 1);
				}
    		}
    		AUD_ClearSampleReadyFlag();
    		AUD_Sampling(ON);
    		ADC_ForceSampleA(); 		// take next sample
    	}

    	/* check if a button was pressed */
    	if(BUT_GetButtonFlag())
    	{
    		/* a button was pressed */
    		if(TV_GetMode() == SKYPE)
    		{
    			TV_GoToOriginalMode();
    			TV_SetMode(ORIGINAL);
    		}
    		else
    		{
    			TV_GoToSkypeMode();
    			TV_SetMode(SKYPE);
    		}
    		BUT_SetButtonFlag(FALSE);
    		BUT_ButtonInterrupt(ON);
    	}

    	/* check for an audio SKYPE sound being received */
    	if(TV_SKYPE_GetDecodeFlag())
    	{
    		/* decode an audio skype code */
    		if(TV_SKYPE_Decode(Audio_ADC_Counts_LowPass_Buffer, Audio_ADC_Counts_LowPass_place, SKYPE_Codes, &index))
    		{
    			/* a valid audio skype code was received */
				UART_SendString("Audio Skype code: ");
				UART_SendStringCRLN((unsigned char*)SKYPE_Codes[index].Description);
				if(MSC_StringMatch((unsigned char*)SKYPE_Codes[index].Description, "Call Start"))
				{
		    		/* a button was pressed */
		    		if(TV_GetMode() != SKYPE)
		    		{
		    			TV_GoToSkypeMode();
		    			TV_SetMode(SKYPE);
		    		}
				}
				if(MSC_StringMatch((unsigned char*)SKYPE_Codes[index].Description, "Call End"))
				{
		    		/* a button was pressed */
		    		if(TV_GetMode() != ORIGINAL)
		    		{
		    			TV_GoToOriginalMode();
		    			TV_SetMode(ORIGINAL);
		    		}
				}
    		}
    		TV_SKYPE_SetDecodeFlag(FALSE);
    	}
    }
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
