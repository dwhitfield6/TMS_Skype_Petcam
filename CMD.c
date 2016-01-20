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
#include <stdbool.h>
#include <string.h>

#include "CMD.h"
#include "IR.h"
#include "MISC.h"
#include "UART.h"
#include "USER.h"
    
/******************************************************************************/
/* Private Variable Declaration      	                                      */
/******************************************************************************/
static unsigned char CommandReady = FALSE;

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
const COMMANDTYPE Commands[] =
{
	{"?", CMD_Help,"Prints the Help menu"},
	{"Help", CMD_PrintAllCommands,"Prints all of the commands"},
	{"IR Sanyo Send~", CMD_SendSanyo,"Sends an IR command to the Sanyo TV"},
	{"IR Visio Send~", CMD_SendVisio,"Sends an IR command to the Visio TV"},
	{"IR Idylis Send~", CMD_SendIdylis,"Sends an IR command to the Idylis Air conditioner"},
};

unsigned char CommandString[LARGEST_COMMAND_WITH_EXTRA];
unsigned char NumCommands;
unsigned char MiscBuffer[MISC_BUFFER_SIZE];

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
	UART_SendStringCRLN("");
	UART_SendStringCRLN("Commands Help Menu:");
	UART_SendStringCRLN("Hit 'Help' + enter to display all available commands");
	UART_SendStringCRLN("");
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
/* CMD_SetNewCommandFlag
 *
 * This function sets the flag for a new command.							  */
/******************************************************************************/
void CMD_SetNewCommandFlag(unsigned char status)
{
	CommandReady = status;
}

/******************************************************************************/
/* CMD_GetNewCommandFlag
 *
 * This function gets the flag set for a new command.						  */
/******************************************************************************/
unsigned char CMD_GetNewCommandFlag(void)
{
	return CommandReady;
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
    		UART_SendChar(command->Command[i]);
    		count++;
		}
	}
    while(count < (LARGEST_COMMAND + 1))
    {
    	UART_SendChar(' ');
        count++;
    }
    UART_SendStringCRLN(command->Help);
}

/******************************************************************************/
/* CMD_PrintCommands
 *
 * This function prints all commands (help).								  */
/******************************************************************************/
void CMD_PrintAllCommands(void)
{
    unsigned char i;

    UART_SendStringCRLN("");
    UART_SendStringCRLN("Available Commands:");
    UART_SendStringCRLN("");
    for(i=0;i<NumCommands;i++)
    {
        CMD_PrintCommand(&Commands[i]);
    }
    UART_SendStringCRLN("");
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

	if(CommandString[size] == '?')
	{
		UART_SendStringCRLN("Available Sanyo codes:");
		for(i=0;i<NumSanyo;i++)
		{
			UART_SendStringCRLN(Sanyo[i].Description);
		}
		UART_SendStringCRLN("");
		UART_SendStringCRLN("For example 'IR Sanyo Send Power'");
	}
	else
	{
		if(IR_CMDCheckMatch(&CommandString[size], Sanyo, &index))
		{
			IR_SendNECWithRepeat(Sanyo[index].NEC);
			UART_SendStringCRLN("Sanyo Code sent");
		}
		else
		{
			UART_SendStringCRLN("Sanyo Code not found");
			UART_SendStringCRLN("Try IR Sanyo Send?");
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

	if(CommandString[size] == '?')
	{
		UART_SendStringCRLN("Available Visio codes:");
		for(i=0;i<NumVisio;i++)
		{
			UART_SendStringCRLN(Visio[i].Description);
		}
		UART_SendStringCRLN("");
		UART_SendStringCRLN("For example 'IR Visio Send Power'");
	}
	else
	{
		if(IR_CMDCheckMatch(&CommandString[size], Visio, &index))
		{
			IR_SendNECWithRepeat(Visio[index].NEC);
			UART_SendStringCRLN("Visio Code sent");
		}
		else
		{
			UART_SendStringCRLN("Visio Code not found");
			UART_SendStringCRLN("Try IR Visio Send?");
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

	if(CommandString[size] == '?')
	{
		UART_SendStringCRLN("Available Idylis codes:");
		for(i=0;i<NumIdylis;i++)
		{
			UART_SendStringCRLN(Idylis[i].Description);
		}
		UART_SendStringCRLN("");
		UART_SendStringCRLN("For example 'IR Idylis Send Power'");
	}
	else
	{
		if(IR_CMDCheckMatch(&CommandString[size], Idylis, &index))
		{
			IR_SendNECWithRepeat(Idylis[index].NEC);
			UART_SendStringCRLN("Idylis Code sent");
		}
		else
		{
			UART_SendStringCRLN("Idylis Code not found");
			UART_SendStringCRLN("Try IR Idylis Send?");
		}
	}
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
