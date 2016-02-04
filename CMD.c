/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 12/14/15     13.0_DW0a   Ported from
 * 							  "PIC_Catalyst_RPI_daughter_Speech_Recognition"
 *                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Contains functions for the UART commands.
 *																			  */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "AUDIO.h"
#include "BLUETOOTH.h"
#include "CMD.h"
#include "IR.h"
#include "MISC.h"
#include "TV.h"
#include "UART.h"
#include "USER.h"
    
/******************************************************************************/
/* Private Variable Declaration      	                                      */
/******************************************************************************/
static unsigned char CommandReadyA = FALSE;
static unsigned char CommandReadyC = FALSE;
static unsigned char ActiveUARTflag = 0;

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
const COMMANDTYPE Commands[] =
{
	{"?", CMD_Help,"Prints the Help menu"},
	{"Blue init", CMD_InitBluetooth, "Initializes the HC-06 Bluetooth module"},
	{"Help", CMD_PrintAllCommands,"Prints all of the commands"},
	{"IR Sanyo Send~", CMD_SendSanyo,"Sends an IR command to the Sanyo TV"},
	{"IR Visio Send~", CMD_SendVisio,"Sends an IR command to the Visio TV"},
	{"IR Idylis Send~", CMD_SendIdylis,"Sends an IR command to the Idylis Air conditioner"},
	{"Skype", CMD_GoToSKYPE, "Goes to SKYPE mode"},
	{"Original", CMD_GoToOriginal, "Goes to Original mode"},
	{"Signal inverted", CMD_SKYPE_SignalInverted, "Sets the audio signal inverted"},
	{"Signal notinverted", CMD_SKYPE_SignalNotInverted, "Sets the audio signal not-inverted"},
	{"Large Average++", CMD_IncreaseLargeAverageAlot,"Increases the large averager by 100 samples"},
	{"Large Average+", CMD_IncreaseLargeAverage,"Increases the large averager by 10 samples"},
	{"Large Average--", CMD_DecreaseLargeAverageAlot,"Decreases the large averager by 100 samples"},
	{"Large Average-", CMD_DecreaseLargeAverage,"Decreases the large averager by 10 samples"},
	{"Small Average++", CMD_IncreaseSmallAverageAlot,"Increases the small averager by 100 samples"},
	{"Small Average+", CMD_IncreaseSmallAverage,"Increases the small averager by 10 samples"},
	{"Small Average--", CMD_DecreaseSmallAverageAlot,"Decreases the small averager by 100 samples"},
	{"Small Average-", CMD_DecreaseSmallAverage,"Decreases the small averager by 10 samples"},
	{"VU Lowpass", CMD_VULowpass,"Sets the VU meter to use the Lowpass filter"},
	{"VU nofilter", CMD_VUAll,"Sets the VU meter to use the full audio spectrum filter"},
};

unsigned char CommandStringA[LARGEST_COMMAND_WITH_EXTRA];
unsigned char CommandStringC[LARGEST_COMMAND_WITH_EXTRA];
unsigned char NumCommands;
unsigned char MiscBuffer[MISC_BUFFER_SIZE];
unsigned char SPRINTBuffer[SPRINT_BUFFER_SIZE];

/******************************************************************************/
/* Inline Functions															  */
/******************************************************************************/

/******************************************************************************/
/* Functions																  */
/******************************************************************************/

/******************************************************************************/
/* InitCMD
 *
 * The function initializes the command and phrase searching.				  */
/******************************************************************************/
void InitCMD(void)
{
	NumCommands = sizeof(Commands) / sizeof(COMMANDTYPE);
}

/******************************************************************************/
/* CMD_Help
 *
 * This function prints the help menu.								  		  */
/******************************************	***********************************/
void CMD_Help(void)
{
	if(CMD_GetActiveUART() == 'A')
	{
		UART_SendStringCRLNA("");
		UART_SendStringCRLNA("Commands Help Menu:");
		UART_SendStringCRLNA("Hit 'Help' + enter to display all available commands");
		UART_SendStringCRLNA("");
	}
	else if(CMD_GetActiveUART() == 'C')
	{
		UART_SendStringCRLNC("");
		UART_SendStringCRLNC("Commands Help Menu:");
		UART_SendStringCRLNC("Hit 'Help' + enter to display all available commands");
		UART_SendStringCRLNC("");
	}
}

/******************************************************************************/
/* CMD_CheckMatch
 *
 * This function checks for a command match and executes the command.		  */
/******************************************************************************/
unsigned char CMD_CheckMatch(unsigned char* received, const COMMANDTYPE* commands, unsigned char size)
{
    unsigned char i,j;
    unsigned char* buffer;

    for(j=0;j<NumCommands;j++)
    {
        buffer = received;
        for(i=0;i<size;i++)
        {
        	if(MSC_LowercaseChar(commands[j].Command[i]) != ' ')
        	{
        		/* eat spaces in command */
        		while(MSC_LowercaseChar(*buffer) == ' ')
        		{
        			/* eat spaces in receive buffer */
        			buffer++;
        		}
        		if(MSC_LowercaseChar(*buffer) == MSC_LowercaseChar(commands[j].Command[i]) || commands[j].Command[i] == 0 || commands[j].Command[i] == '~')
				{
					if(commands[j].Command[i] == 0 || commands[j].Command[i] == '~')
					{
						/* Found a match, now check to make sure that a CR LN follows */
						if(*buffer == 0 || commands[j].Command[i] == '~')
						{
							/* we have a match */
							(*commands[j].Function) ();
							return PASS;
						}
						else
						{
							break;
						}
					}
					buffer++;
				}
				else
				{
					break;
				}
        	}
        }
    }
    return FAIL;
}

/******************************************************************************/
/* CMD_SetNewCommandFlagA
 *
 * This function sets the flag for a new command on UART A.					  */
/******************************************************************************/
void CMD_SetNewCommandFlagA(unsigned char status)
{
	CommandReadyA = status;
}

/******************************************************************************/
/* CMD_SetNewCommandFlagC
 *
 * This function sets the flag for a new command on UART C.					  */
/******************************************************************************/
void CMD_SetNewCommandFlagC(unsigned char status)
{
	CommandReadyC = status;
}

/******************************************************************************/
/* CMD_GetNewCommandFlagA
 *
 * This function gets the flag set for a new command on UART A.				  */
/******************************************************************************/
unsigned char CMD_GetNewCommandFlagA(void)
{
	return CommandReadyA;
}

/******************************************************************************/
/* CMD_GetNewCommandFlagC
 *
 * This function gets the flag set for a new command on UART C.				  */
/******************************************************************************/
unsigned char CMD_GetNewCommandFlagC(void)
{
	return CommandReadyC;
}

/******************************************************************************/
/* CMD_GetNewCommandFlag
 *
 * This function gets the flag set for a new command.						  */
/******************************************************************************/
unsigned char CMD_CommandSize(pFunction function)
{
	unsigned char i;
	unsigned char j;
	unsigned char numcharacters = 0;

	for(i=0;i<NumCommands;i++)
	{
		if(Commands[i].Function == function)
		{
			break;
		}
	}
	for(j=0;j<LARGEST_COMMAND_WITH_EXTRA;j++)
	{
		if(Commands[i].Command[j] == '~' || Commands[i].Command[j] == '0')
		{
			break;
		}
		numcharacters++;
	}
	return numcharacters;
}

/******************************************************************************/
/* CMD_PrintCommand
 *
 * This function prints a command. 											  */
/******************************************************************************/
void CMD_PrintCommand(const COMMANDTYPE* command)
{
    unsigned int count = 0;
    unsigned char i;

    for(i=0;i<LARGEST_COMMAND;i++)
	{
    	if(command->Command[i] == 0)
    	{
    		break;
    	}
    	if(command->Command[i] != '~')
		{
    		if(CMD_GetActiveUART() == 'A')
    		{
    			UART_SendCharA(command->Command[i]);
    		}
    		else if(CMD_GetActiveUART() == 'C')
    		{
    			UART_SendCharC(command->Command[i]);
    		}
    		count++;
		}
	}
    while(count < (LARGEST_COMMAND + 1))
    {
		if(CMD_GetActiveUART() == 'A')
		{
			UART_SendCharA(' ');
		}
		else if(CMD_GetActiveUART() == 'C')
		{
			UART_SendCharC(' ');
		}
        count++;
    }
	if(CMD_GetActiveUART() == 'A')
	{
		UART_SendStringCRLNA((unsigned char*) command->Help);
	}
	else if(CMD_GetActiveUART() == 'C')
	{
		UART_SendStringCRLNC((unsigned char*) command->Help);
	}
}

/******************************************************************************/
/* CMD_PrintCommands
 *
 * This function prints all commands (help).								  */
/******************************************************************************/
void CMD_PrintAllCommands(void)
{
    unsigned char i;

    if(CMD_GetActiveUART() == 'A')
	{
		UART_SendStringCRLNA("");
		UART_SendStringCRLNA("Available Commands:");
		UART_SendStringCRLNA("");
		for(i=0;i<NumCommands;i++)
		{
			CMD_PrintCommand(&Commands[i]);
		}
	}
    else if(CMD_GetActiveUART() == 'C')
	{
		UART_SendStringCRLNC("");
		UART_SendStringCRLNC("Available Commands:");
		UART_SendStringCRLNC("");
		for(i=0;i<NumCommands;i++)
		{
			CMD_PrintCommand(&Commands[i]);
		}
	}
}

/******************************************************************************/
/* CMD_SendSanyo
 *
 * This function sends a Sanyo TV command(IRSanyoSend).						  */
/******************************************************************************/
void CMD_SendSanyo(void)
{
	unsigned char index = 0;
	unsigned char i;
	unsigned char size = CMD_CommandSize(&CMD_SendSanyo);

	if(CMD_GetActiveUART() == 'A')
	{
		if(CommandStringA[size] == '?')
		{
			UART_SendStringCRLNA("Available Sanyo codes:");
			for(i=0;i<NumSanyo;i++)
			{
				UART_SendStringCRLNA((unsigned char*) Sanyo[i].Description);
			}
			UART_SendStringCRLNA("");
			UART_SendStringCRLNA("For example 'IR Sanyo Send Power'");
		}
		else
		{
			if(IR_CMDCheckMatch(&CommandStringA[size], Sanyo, &index))
			{
				IR_SendNECWithRepeat(Sanyo[index].NEC);
				UART_SendStringCRLNA("Sanyo Code sent");
			}
			else
			{
				UART_SendStringCRLNA("Sanyo Code not found");
				UART_SendStringCRLNA("Try IR Sanyo Send?");
			}
		}
	}
	else if(CMD_GetActiveUART() == 'C')
	{
		if(CommandStringC[size] == '?')
		{
			UART_SendStringCRLNC("Available Sanyo codes:");
			for(i=0;i<NumSanyo;i++)
			{
				UART_SendStringCRLNC((unsigned char*) Sanyo[i].Description);
			}
			UART_SendStringCRLNC("");
			UART_SendStringCRLNC("For example 'IR Sanyo Send Power'");
		}
		else
		{
			if(IR_CMDCheckMatch(&CommandStringC[size], Sanyo, &index))
			{
				IR_SendNECWithRepeat(Sanyo[index].NEC);
				UART_SendStringCRLNC("Sanyo Code sent");
			}
			else
			{
				UART_SendStringCRLNC("Sanyo Code not found");
				UART_SendStringCRLNC("Try IR Sanyo Send?");
			}
		}
	}
}

/******************************************************************************/
/* CMD_SendVisio
 *
 * This function sends a Visio TV command(IRVisioSend).						  */
/******************************************************************************/
void CMD_SendVisio(void)
{
	unsigned char index = 0;
	unsigned char i;
	unsigned char size = CMD_CommandSize(&CMD_SendVisio);

	if(CMD_GetActiveUART() == 'A')
	{
		if(CommandStringA[size] == '?')
		{
			UART_SendStringCRLNA("Available Visio codes:");
			for(i=0;i<NumVisio;i++)
			{
				UART_SendStringCRLNA((unsigned char*) Visio[i].Description);
			}
			UART_SendStringCRLNA("");
			UART_SendStringCRLNA("For example 'IR Visio Send Power'");
		}
		else
		{
			if(IR_CMDCheckMatch(&CommandStringA[size], Visio, &index))
			{
				IR_SendNECWithRepeat(Visio[index].NEC);
				UART_SendStringCRLNA("Visio Code sent");
			}
			else
			{
				UART_SendStringCRLNA("Visio Code not found");
				UART_SendStringCRLNA("Try IR Visio Send?");
			}
		}
	}
	else if(CMD_GetActiveUART() == 'C')
	{
		if(CommandStringC[size] == '?')
		{
			UART_SendStringCRLNC("Available Visio codes:");
			for(i=0;i<NumVisio;i++)
			{
				UART_SendStringCRLNC((unsigned char*) Visio[i].Description);
			}
			UART_SendStringCRLNC("");
			UART_SendStringCRLNC("For example 'IR Visio Send Power'");
		}
		else
		{
			if(IR_CMDCheckMatch(&CommandStringC[size], Visio, &index))
			{
				IR_SendNECWithRepeat(Visio[index].NEC);
				UART_SendStringCRLNC("Visio Code sent");
			}
			else
			{
				UART_SendStringCRLNC("Visio Code not found");
				UART_SendStringCRLNC("Try IR Visio Send?");
			}
		}
	}
}

/******************************************************************************/
/* CMD_SendIdylis
 *
 * This function sends a Idylis A/C command(IRIdylisSend).					  */
/******************************************************************************/
void CMD_SendIdylis(void)
{
	unsigned char index = 0;
	unsigned char i;
	unsigned char size = CMD_CommandSize(&CMD_SendIdylis);

	if(CMD_GetActiveUART() == 'A')
	{
		if(CommandStringA[size] == '?')
		{
			UART_SendStringCRLNA("Available Idylis codes:");
			for(i=0;i<NumIdylis;i++)
			{
				UART_SendStringCRLNA((unsigned char*) Idylis[i].Description);
			}
			UART_SendStringCRLNA("");
			UART_SendStringCRLNA("For example 'IR Idylis Send Power'");
		}
		else
		{
			if(IR_CMDCheckMatch(&CommandStringA[size], Idylis, &index))
			{
				IR_SendNECWithRepeat(Idylis[index].NEC);
				UART_SendStringCRLNA("Idylis Code sent");
			}
			else
			{
				UART_SendStringCRLNA("Idylis Code not found");
				UART_SendStringCRLNA("Try IR Idylis Send?");
			}
		}
	}
	else if(CMD_GetActiveUART() == 'C')
	{
		if(CommandStringC[size] == '?')
		{
			UART_SendStringCRLNC("Available Idylis codes:");
			for(i=0;i<NumIdylis;i++)
			{
				UART_SendStringCRLNC((unsigned char*) Idylis[i].Description);
			}
			UART_SendStringCRLNC("");
			UART_SendStringCRLNC("For example 'IR Idylis Send Power'");
		}
		else
		{
			if(IR_CMDCheckMatch(&CommandStringC[size], Idylis, &index))
			{
				IR_SendNECWithRepeat(Idylis[index].NEC);
				UART_SendStringCRLNC("Idylis Code sent");
			}
			else
			{
				UART_SendStringCRLNC("Idylis Code not found");
				UART_SendStringCRLNC("Try IR Idylis Send?");
			}
		}
	}

}

/******************************************************************************/
/* CMD_SetActiveUART
 *
 * This function sets the active UART (to print to).						  */
/******************************************************************************/
void CMD_SetActiveUART(unsigned char state)
{
	ActiveUARTflag = state;
}

/******************************************************************************/
/* CMD_GetActiveUART
 *
 * This function returns the active UART (to print to).						  */
/******************************************************************************/
unsigned char CMD_GetActiveUART(void)
{
	return ActiveUARTflag;
}

/******************************************************************************/
/* CMD_InitBluetooth
 *
 * The function initializes the HC-06 module.								  */
/******************************************************************************/
void CMD_InitBluetooth(void)
{
	while(!UART_IsDoneC());
	MSC_DelayUS(100);
	UART_SetParametersC(9600, 1, PARITY_NONE);   // set the Baud rate, stop bits, and parity bit
	MSC_DelayUS(100000);
	BLUE_ATCommand("AT");
	MSC_DelayUS(1000000);
	BLUE_ATCommand("AT+NAMEMARLEY");
	MSC_DelayUS(1000000);
	BLUE_ATCommand("AT+BAUD8");
	while(!UART_IsDoneC());
	UART_SetParametersC(115200, 1, PARITY_NONE);   // set the Baud rate, stop bits, and parity bit
	BLUE_ATCommand("AT");
	MSC_DelayUS(1000000);
	BLUE_ATCommand("AT+NAMEMARLEY");
	MSC_DelayUS(1000000);
	BLUE_ATCommand("AT+BAUD8");
	MSC_DelayUS(1000000);
	while(!UART_IsDoneC());
}

/******************************************************************************/
/* CMD_GoToSKYPE
 *
 * The function puts the system into SKYPE mode (Skype).					  */
/******************************************************************************/
void CMD_GoToSKYPE(void)
{
	TV_GoToSkypeMode();
}

/******************************************************************************/
/* CMD_GoToOriginal
 *
 * The function puts the system into original mode (Original).				  */
/******************************************************************************/
void CMD_GoToOriginal(void)
{
	TV_GoToOriginalMode();
}

/******************************************************************************/
/* CMD_IncreaseLargeAverageAlot
 *
 * The function increases the large averager by 100.						  */
/******************************************************************************/
void CMD_IncreaseLargeAverageAlot(void)
{
	if(AudioProcessingSampleLarge < (AUDIO_ADC_BUFFER_SIZE - 100))
	{
		AudioProcessingSampleLarge += 100;
	}
	sprintf((char*)SPRINTBuffer, "AudioProcessingSampleLarge = %d", AudioProcessingSampleLarge);

	if(CMD_GetActiveUART() == 'A')
	{
		UART_SendStringCRLNA(SPRINTBuffer);
	}
	else if(CMD_GetActiveUART() == 'C')
	{
		UART_SendStringCRLNC(SPRINTBuffer);
	}
}

/******************************************************************************/
/* CMD_IncreaseLargeAverage
 *
 * The function increases the large averager by 10.							  */
/******************************************************************************/
void CMD_IncreaseLargeAverage(void)
{
	if(AudioProcessingSampleLarge < (AUDIO_ADC_BUFFER_SIZE - 10))
	{
		AudioProcessingSampleLarge += 10;
	}
	sprintf((char*)SPRINTBuffer, "AudioProcessingSampleLarge = %d", AudioProcessingSampleLarge);

	if(CMD_GetActiveUART() == 'A')
	{
		UART_SendStringCRLNA(SPRINTBuffer);
	}
	else if(CMD_GetActiveUART() == 'C')
	{
		UART_SendStringCRLNC(SPRINTBuffer);
	}
}

/******************************************************************************/
/* CMD_DecreaseLargeAverageAlot
 *
 * The function decreases the large averager by 100.						  */
/******************************************************************************/
void CMD_DecreaseLargeAverageAlot(void)
{
	if(AudioProcessingSampleLarge > 100 && ((AudioProcessingSampleLarge - AudioProcessingSampleSmall) > 100))
	{
		AudioProcessingSampleLarge -= 100;
	}

	sprintf((char*)SPRINTBuffer, "AudioProcessingSampleLarge = %d", AudioProcessingSampleLarge);

	if(CMD_GetActiveUART() == 'A')
	{
		UART_SendStringCRLNA(SPRINTBuffer);
	}
	else if(CMD_GetActiveUART() == 'C')
	{
		UART_SendStringCRLNC(SPRINTBuffer);
	}
}

/******************************************************************************/
/* CMD_DecreaseLargeAverage
 *
 * The function decreases the large averager by 10.							  */
/******************************************************************************/
void CMD_DecreaseLargeAverage(void)
{
	if(AudioProcessingSampleLarge > 10 && ((AudioProcessingSampleLarge - AudioProcessingSampleSmall) > 10))
	{
		AudioProcessingSampleLarge -= 10;
	}

	sprintf((char*)SPRINTBuffer, "AudioProcessingSampleLarge = %d", AudioProcessingSampleLarge);

	if(CMD_GetActiveUART() == 'A')
	{
		UART_SendStringCRLNA(SPRINTBuffer);
	}
	else if(CMD_GetActiveUART() == 'C')
	{
		UART_SendStringCRLNC(SPRINTBuffer);
	}
}

/******************************************************************************/
/* CMD_IncreaseSmallAverageAlot
 *
 * The function increases the small averager by 100.							  */
/******************************************************************************/
void CMD_IncreaseSmallAverageAlot(void)
{
	if((AudioProcessingSampleSmall < (AUDIO_ADC_BUFFER_SIZE - 100)) && ((AudioProcessingSampleLarge - AudioProcessingSampleSmall) > 100))
	{
		AudioProcessingSampleSmall += 100;
	}

	sprintf((char*)SPRINTBuffer, "AudioProcessingSampleSmall = %d", AudioProcessingSampleSmall);

	if(CMD_GetActiveUART() == 'A')
	{
		UART_SendStringCRLNA(SPRINTBuffer);
	}
	else if(CMD_GetActiveUART() == 'C')
	{
		UART_SendStringCRLNC(SPRINTBuffer);
	}
}

/******************************************************************************/
/* CMD_IncreaseSmallAverage
 *
 * The function increases the small averager by 10.							  */
/******************************************************************************/
void CMD_IncreaseSmallAverage(void)
{
	if((AudioProcessingSampleSmall < (AUDIO_ADC_BUFFER_SIZE - 10)) && ((AudioProcessingSampleLarge - AudioProcessingSampleSmall) > 10))
	{
		AudioProcessingSampleSmall += 10;
	}

	sprintf((char*)SPRINTBuffer, "AudioProcessingSampleSmall = %d", AudioProcessingSampleSmall);

	if(CMD_GetActiveUART() == 'A')
	{
		UART_SendStringCRLNA(SPRINTBuffer);
	}
	else if(CMD_GetActiveUART() == 'C')
	{
		UART_SendStringCRLNC(SPRINTBuffer);
	}
}

/******************************************************************************/
/* CMD_DecreaseSmallAverageAlot
 *
 * The function decreases the small averager by 100.						  */
/******************************************************************************/
void CMD_DecreaseSmallAverageAlot(void)
{
	if(AudioProcessingSampleSmall > 100)
	{
		AudioProcessingSampleSmall -= 100;
	}

	sprintf((char*)SPRINTBuffer, "AudioProcessingSampleSmall = %d", AudioProcessingSampleSmall);

	if(CMD_GetActiveUART() == 'A')
	{
		UART_SendStringCRLNA(SPRINTBuffer);
	}
	else if(CMD_GetActiveUART() == 'C')
	{
		UART_SendStringCRLNC(SPRINTBuffer);
	}
}

/******************************************************************************/
/* CMD_DecreaseSmallAverage
 *
 * The function decreases the small averager by 10.							  */
/******************************************************************************/
void CMD_DecreaseSmallAverage(void)
{
	if(AudioProcessingSampleSmall > 10)
	{
		AudioProcessingSampleSmall -= 10;
	}

	sprintf((char*)SPRINTBuffer, "AudioProcessingSampleSmall = %d", AudioProcessingSampleSmall);

	if(CMD_GetActiveUART() == 'A')
	{
		UART_SendStringCRLNA(SPRINTBuffer);
	}
	else if(CMD_GetActiveUART() == 'C')
	{
		UART_SendStringCRLNC(SPRINTBuffer);
	}
}

/******************************************************************************/
/* CMD_VULowpass
 *
 * The function sets the Vu meter to use the lowpass filtered audio.		  */
/******************************************************************************/
void CMD_VULowpass(void)
{
	AudioVU = LOWPASS;

	if(CMD_GetActiveUART() == 'A')
	{
		UART_SendStringCRLNA("Audio Vu mode = Lowpass");
	}
	else if(CMD_GetActiveUART() == 'C')
	{
		UART_SendStringCRLNC("Audio Vu mode = Lowpass");
	}
}

/******************************************************************************/
/* CMD_VUAll
 *
 * The function sets the Vu meter to use the unfiltered audio.				  */
/******************************************************************************/
void CMD_VUAll(void)
{
	AudioVU = ALL;

	if(CMD_GetActiveUART() == 'A')
	{
		UART_SendStringCRLNA("Audio Vu mode = Allpass");
	}
	else if(CMD_GetActiveUART() == 'C')
	{
		UART_SendStringCRLNC("Audio Vu mode = Allpass");
	}
}

/******************************************************************************/
/* CMD_SKYPE_SignalInverted
 *
 * The function sets the audio signal inverted.								  */
/******************************************************************************/
void CMD_SKYPE_SignalInverted(void)
{
	SKYPE_Signal_Inverted = TRUE;

	if(CMD_GetActiveUART() == 'A')
	{
		UART_SendStringCRLNA("Audio signal source = Inverted");
	}
	else if(CMD_GetActiveUART() == 'C')
	{
		UART_SendStringCRLNC("Audio signal source = Inverted");
	}
}

/******************************************************************************/
/* CMD_SKYPE_SignalNotInverted
 *
 * The function sets the audio signal not inverted.							  */
/******************************************************************************/
void CMD_SKYPE_SignalNotInverted(void)
{
	SKYPE_Signal_Inverted = FALSE;

	if(CMD_GetActiveUART() == 'A')
	{
		UART_SendStringCRLNA("Audio signal source = Not Inverted");
	}
	else if(CMD_GetActiveUART() == 'C')
	{
		UART_SendStringCRLNC("Audio signal source = Not Inverted");
	}
}
/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
