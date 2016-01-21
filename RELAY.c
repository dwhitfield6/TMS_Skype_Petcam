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
/* Contains functions for the Solid state, zero cross detector, and
 *  mechanical relay.
 *																			  */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "ADC.h"
#include "INTERRUPTS.h"
#include "RELAY.h"
#include "SYSTEM.h"
#include "TIMERS.h"
#include "USER.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
unsigned char RLY_SSRelayDuty = 0;

/******************************************************************************/
/* Inline Functions 														  */
/******************************************************************************/

/******************************************************************************/
/* Functions																  */
/******************************************************************************/

/******************************************************************************/
/* InitRelay
 *
 * The function initializes the relay.										  */
/******************************************************************************/
void InitRelay(void)
{
	/* Set INT2 ISRs */
	SYS_Unlock();
	PieVectTable.XINT2_INT = &ISR_INT2_ZEROCROSS;
	SYS_Lock();
	SYS_EnableInterruptGroup(INTERRUPT_GROUP1);		// Group for INT2
	RLY_ZeroCrossInterrupt(ON);
	SYS_Unlock();
    InputXbarRegs.INPUT5SELECT = ZEROCROSS_GPIO;	//Set XINT1 source to GPIO-pin
    SYS_Lock();
    XintRegs.XINT2CR.bit.POLARITY = 0;    			// Falling edge interrupt
}

/******************************************************************************/
/* BUT_ButtonInterrupt
 *
 * The function controls button interrupt.									  */
/******************************************************************************/
void RLY_ZeroCrossInterrupt(unsigned char state)
{
	SYS_Unlock();
	if (state)
	{
		PieCtrlRegs.PIEIER1.bit.INTx5 = 1;   	// Enable PIE Group 1 INT5
		XintRegs.XINT2CR.bit.ENABLE = 1;        // Enable XINT2
	}
	else
	{
		PieCtrlRegs.PIEIER1.bit.INTx5 = 0;    	// Enable PIE Group 1 INT5
		XintRegs.XINT2CR.bit.ENABLE = 0;        // Disable XINT2
	}
	SYS_Lock();
}

/******************************************************************************/
/* RLY_MechRelay
 *
 * The function controls the mechanical relay.								  */
/******************************************************************************/
void RLY_MechRelay(unsigned char state)
{
	if(state)
	{
		SYS_WritePin(MECH_RELAY_GPIO, ON);
	}
	else
	{
		SYS_WritePin(MECH_RELAY_GPIO, OFF);
	}
}

/******************************************************************************/
/* RLY_SolidStateRelay
 *
 * The function controls the solid state relay.								  */
/******************************************************************************/
void RLY_SolidStateRelay(unsigned char state)
{
	if(state)
	{
		SYS_WritePin(SS_RELAY_GPIO, ON);
	}
	else
	{
		SYS_WritePin(SS_RELAY_GPIO, OFF);
	}
}

/******************************************************************************/
/* RLY_SSRelayDutyCycle
 *
 * The function sets the solid state relay duty cycle.						  */
/******************************************************************************/
void RLY_SetSSRelayDutyCycle(unsigned char duty)
{
	unsigned long period;

	RLY_SSRelayDuty = duty;
	period = TMR_DutyToPeriod(duty);
	TMR_StartTimer2(FALSE);				// stop timer
	TMR_SetTimerPeriod2(period);
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
