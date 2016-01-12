/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 12/14/15     13.0_DW0a   New project creation.
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
#include <stdint.h>
#include <stdbool.h>

#include "LED.h"
#include "MISC.h"
#include "SYSTEM.h"
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

	/* set up the interrupt vectors */
	SYS_PIEVectorTable();

	/* Enable global Interrupts and higher priority real-time debug events */
	SYS_Interrupts(ON);
	ERTM;  // Enable Global realtime interrupt DBGM

	/* initialize the GPIO pins */
	Init_Pins();

	/* initialize the hardware modules */
	Init_Modules();

    while(1)
    {

    }
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
