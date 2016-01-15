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
/* Contains functions for Analog to Digital converter.
 *																			  */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "BUTTON.h"
#include "INTERRUPTS.h"
#include "SYSTEM.h"
#include "USER.h"

/******************************************************************************/
/* Private Variable Declaration      	                                      */
/******************************************************************************/
static unsigned char ButtonFlag = FALSE;

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
void InitButtons(void)
{
	/* Set INT1 ISRs */
	SYS_Unlock();
	PieVectTable.XINT1_INT = &ISR_INT1_BUTTON;
	SYS_Lock();
	SYS_EnableInterruptGroup(INTERRUPT_GROUP1);	// Group for INT1
	BUT_ButtonInterrupt(ON);
	SYS_Unlock();
    InputXbarRegs.INPUT4SELECT = PUSHBUTTON_GPIO;	//Set XINT1 source to GPIO-pin
    SYS_Lock();
    XintRegs.XINT1CR.bit.POLARITY = 0;    			// Falling edge interrupt
}

/******************************************************************************/
/* BUT_ButtonInterrupt
 *
 * The function controls button interrupt.									  */
/******************************************************************************/
void BUT_ButtonInterrupt(unsigned char state)
{
	if (state)
	{
		PieCtrlRegs.PIEIER1.bit.INTx4 = 1;   	// Enable PIE Group 1 INT4
		XintRegs.XINT1CR.bit.ENABLE = 1;        // Enable XINT1
	}
	else
	{
		PieCtrlRegs.PIEIER1.bit.INTx4 = 0;    	// Enable PIE Group 1 INT4
		XintRegs.XINT1CR.bit.ENABLE = 0;        // Disable XINT1
	}
}

/******************************************************************************/
/* BUT_SetButtonFlag
 *
 * The function sets the button flag.										  */
/******************************************************************************/
void BUT_SetButtonFlag(unsigned char status)
{
	ButtonFlag = status;
}

/******************************************************************************/
/* BUT_GetButtonFlag
 *
 * The function gets the button flag.										  */
/******************************************************************************/
unsigned char BUT_GetButtonFlag(void)
{
	return ButtonFlag;
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
