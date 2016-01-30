/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 01/27/16     13.0_DW0a   First coding.
 *                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Contains functions for the toggle switch.
 *																			  */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "INTERRUPTS.h"
#include "SYSTEM.h"
#include "TOGGLE.h"
#include "USER.h"

/******************************************************************************/
/* Private Variable Declaration      	                                      */
/******************************************************************************/
static ENUM_TOGGLE ToggleFlag = NO_TOGGLE;

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/* Inline Functions 														  */
/******************************************************************************/

/******************************************************************************/
/* Functions																  */
/******************************************************************************/

/******************************************************************************/
/* InitButtons
 *
 * The function initializes the push buttons.								  */
/******************************************************************************/
void InitToggle(void)
{
	/* Set INT4 ISRs */
	SYS_Unlock();
	PieVectTable.XINT4_INT = &ISR_INT4_TOGGLE;
	SYS_Lock();
	SYS_EnableInterruptGroup(INTERRUPT_GROUP12);	// Group for INT12
	SYS_Unlock();
    InputXbarRegs.INPUT13SELECT = TOGGLE_GPIO;		//Set XINT4 source to GPIO-pin
    SYS_Lock();
    XintRegs.XINT4CR.bit.POLARITY = 0b11;   		// Falling and rising edge interrupt

	if(SYS_ReadPin(TOGGLE_GPIO))
	{
		TOG_SetToggleFlag(TOGGLE_OFF);
	}
	else
	{
		TOG_SetToggleFlag(TOGGLE_ON);
	}
	TOG_ToggleInterrupt(ON);
}

/******************************************************************************/
/* TOG_ToggleInterrupt
 *
 * The function controls toggle switch interrupt.							  */
/******************************************************************************/
void TOG_ToggleInterrupt(unsigned char state)
{
	SYS_Unlock();
	if (state)
	{
		PieCtrlRegs.PIEIER12.bit.INTx2 = 1;   	// Enable PIE Group 12 INT2
		XintRegs.XINT4CR.bit.ENABLE = 1;        // Enable XINT4
	}
	else
	{
		PieCtrlRegs.PIEIER12.bit.INTx2 = 0;   	// Disable PIE Group 12 INT2
		XintRegs.XINT4CR.bit.ENABLE = 0;        // Disable XINT4
	}
	SYS_Lock();
}

/******************************************************************************/
/* TOG_SetToggleFlag
 *
 * The function sets the toggle flag.										  */
/******************************************************************************/
void TOG_SetToggleFlag(ENUM_TOGGLE status)
{
	ToggleFlag = status;
}

/******************************************************************************/
/* TOG_GetToggleFlag
 *
 * The function gets the toggle flag.										  */
/******************************************************************************/
ENUM_TOGGLE TOG_GetToggleFlag(void)
{
	return ToggleFlag;
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
