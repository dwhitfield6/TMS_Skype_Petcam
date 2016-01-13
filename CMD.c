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
};

unsigned char CommandString[LARGEST_COMMAND];
unsigned char NumCommands;

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
	UART_SendStringCRLN("Hit Commands?+enter to display all available commands");
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
            if(MSC_LowercaseChar(*buffer) == commands[j].Command[i] || commands[j].Command[i] == 0 || commands[j].Command[i] == '~')
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

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
