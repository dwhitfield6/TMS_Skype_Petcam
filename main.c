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

#include "CMD.h"
#include "IR.h"
#include "LED.h"
#include "MISC.h"
#include "SYSTEM.h"
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

    while(1)
    {
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
    	if(IR_GetReceiveFlag())
    	{
    		if(IR_ProcessReceiveNEC(&temp_NEC))
    		{
    			NEC = temp_NEC;
    			sprintf((char*)SPRINTBuffer, "Received IR NEC code: %ld", NEC);
    			UART_SendStringCRLN(SPRINTBuffer);
    		}
    		IR_ReceiverInterrupt(ON);
    		IR_ClearReceiveFlag();
    	}
    }
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
