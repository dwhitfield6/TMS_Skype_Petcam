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
#include "TOGGLE.h"
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
	UART_SendBannerA();
	UART_SendBannerC();

	/* print prompt */
	UART_SendPromptA();
	UART_SendPromptC();

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
    	if(CMD_GetNewCommandFlagA() || CMD_GetNewCommandFlagC())
    	{
    		/* check for command over USB UART */
    		if(CMD_GetNewCommandFlagA())
    		{
        		/* process new command */
    			CMD_SetActiveUART('A');
        		if(!CMD_CheckMatch(CommandStringA, Commands, LARGEST_COMMAND))
        		{
        			UART_SendStringCRLNA(BAD_COMMAND);
        		}
        		else
        		{
        			UART_SendStringCRLNA("");
        		}
        		CMD_SetNewCommandFlagA(FALSE);
    			UART_SendPromptA();
    		}

    		/* check for command over BLUEOOTH UART */
    		if(CMD_GetNewCommandFlagC())
    		{
        		/* process new command */
    			CMD_SetActiveUART('C');
        		if(!CMD_CheckMatch(CommandStringC, Commands, LARGEST_COMMAND))
        		{
        			UART_SendStringCRLNC(BAD_COMMAND);
        		}
        		else
        		{
        			UART_SendStringCRLNC("");
        		}
        		CMD_SetNewCommandFlagC(FALSE);
    			UART_SendPromptC();
    		}
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
				UART_SendStringCRLNA(SPRINTBuffer);
				UART_SendStringCRLNC(SPRINTBuffer);

				if(IR_process)
				{
					/* check the Known codes */
					if(IR_CheckForNECMatch(NEC, Sanyo, &index))
					{
						/* Sanyo match */
						UART_SendStringA("Sanyo code : ");
						UART_SendStringC("Sanyo code : ");
						UART_SendStringCRLNA((unsigned char*)Sanyo[index].Description);
						UART_SendStringCRLNC((unsigned char*)Sanyo[index].Description);
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
						UART_SendStringA("Visio code : ");
						UART_SendStringC("Visio code : ");
						UART_SendStringCRLNA((unsigned char*)Visio[index].Description);
						UART_SendStringCRLNC((unsigned char*)Visio[index].Description);
					}
					else if(IR_CheckForNECMatch(NEC, Idylis, &index))
					{
						/* Idylis match */
						UART_SendStringA("Idylis code : ");
						UART_SendStringC("Idylis code : ");
						UART_SendStringCRLNA((unsigned char*)Idylis[index].Description);
						UART_SendStringCRLNC((unsigned char*)Idylis[index].Description);
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
				UART_SendStringA("Audio Skype code: ");
				UART_SendStringC("Audio Skype code: ");
				UART_SendStringCRLNA((unsigned char*)SKYPE_Codes[index].Description);
				UART_SendStringCRLNC((unsigned char*)SKYPE_Codes[index].Description);
				if(MSC_StringMatch((unsigned char*)SKYPE_Codes[index].Description, "Call Start")) // code1
				{
		    		/* a button was pressed */
		    		if(TV_GetMode() != SKYPE)
		    		{
		    			TV_GoToSkypeMode();
		    			TV_SetMode(SKYPE);
		    		}
				}
				if(MSC_StringMatch((unsigned char*)SKYPE_Codes[index].Description, "Call End")) // code2
				{
		    		/* a button was pressed */
		    		if(TV_GetMode() != ORIGINAL)
		    		{
		    			TV_GoToOriginalMode();
		    			TV_SetMode(ORIGINAL);
		    		}
				}
    		}
    		TV_SKYPE_Audio_Code_Started = FALSE;
    		TV_SKYPE_SetDecodeFlag(FALSE);
    	}

    	/* check for the TOGGLE switch moving */
    	if(TOG_GetToggleFlag())
    	{
    		if(SYS_ReadPin(TOGGLE_GPIO))
    		{
    			/* switch was toggled off */
    			TV_SKYPE_SearchingEnabled(FALSE);
    			LED_SetMode(RED);
    		}
    		else
    		{
    			/* switch was toggled on */
    			TV_SKYPE_Audio_Code_Started = FALSE;
    			TV_SKYPE_SearchingEnabled(TRUE);
    			LED_SetMode(GREEN);
    		}

    		TOG_SetToggleFlag(FALSE);
    		TOG_ToggleInterrupt(ON);
    	}

    	/* LED blinking without blocking */
    	if(LED_GetMode() == RED_BLINKING || LED_GetMode() == GREEN_BLINKING)
    	{
    		LED_BlinkingAction(LED_GetMode());
    	}
    }
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
