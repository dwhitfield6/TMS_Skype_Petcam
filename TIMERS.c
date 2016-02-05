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
/* Contains functions for timers.
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
#include "IR.h"
#include "MISC.h"
#include "RELAY.h"
#include "SYSTEM.h"
#include "TIMERS.h"
#include "USER.h"

/******************************************************************************/
/* Private Variable Declaration		                                          */
/******************************************************************************/
static unsigned char Timer0_Timeout = FALSE;

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/* Inline Functions                                                           */
/******************************************************************************/

/******************************************************************************/
/* Functions																  */
/******************************************************************************/

/******************************************************************************/
/* InitTimers
 *
 * The function initializes the timers.										  */
/******************************************************************************/
void InitTimers(void)
{
	InitTimer0();
	InitTimer1();
	InitTimer2();
}

/******************************************************************************/
/* InitTimer0
 *
 * The function initializes timer 0 for the MISC delay function.			  */
/******************************************************************************/
void InitTimer0(void)
{
	/* Set Timer 0 ISR */
	SYS_Unlock();
	PieVectTable.TIMER0_INT = &ISR_TIMER0_DELAY;
	SYS_Lock();

	TMR_Interrupt0(OFF);
	SYS_EnableInterruptGroup(INTERRUPT_GROUP1);	// Group for Timer 0
	TMR_StartTimer0(FALSE);						// Stop the timer
	CpuTimer0Regs.TPR.bit.TDDR = 15;			// presceler is 16
}

/******************************************************************************/
/* InitTimer1
 *
 * The function initializes timer 1 for the IR recevier timing.				  */
/******************************************************************************/
void InitTimer1(void)
{
	/* Set Timer 1 ISR */
	SYS_Unlock();
	PieVectTable.TIMER1_INT = &ISR_TIMER1_IR_RECEIVE;
	SYS_Lock();

	TMR_SetTimerPeriod1(IR_RECEIVE_COUNTS_TIMEOUT);
	TMR_Interrupt1(ON);
	TMR_StartTimer1(FALSE);						// Stop the timer
	CpuTimer1Regs.TPR.bit.TDDR = 15;			// presceler is 16
}

/******************************************************************************/
/* InitTimer2
 *
 * The function initializes timer 2 audio protocol timing.					  */
/******************************************************************************/
void InitTimer2(void)
{
	/* Set Timer 2 ISR */
	SYS_Unlock();
	PieVectTable.TIMER2_INT = &ISR_TIMER2_AUDIO_PROTOCOL;
	SYS_Lock();

	TMR_SetTimerPeriod2(TIMER_2_PERIOD_COUNTS);
	TMR_Interrupt2(OFF);
	TMR_StartTimer2(FALSE);						// Stop the timer
	CpuTimer2Regs.TPR.bit.TDDR = 15;			// presceler is 16
}


/******************************************************************************/
/* TMR_SetTimerWithPeriod0
 *
 * The function loads the period cont to the timer TIM register.			  */
/******************************************************************************/
void TMR_SetTimerWithPeriod0(void)
{
	CpuTimer0Regs.TCR.bit.TRB = 1;
}

/******************************************************************************/
/* TMR_SetTimerWithPeriod1
 *
 * The function loads the period cont to the timer TIM register.			  */
/******************************************************************************/
void TMR_SetTimerWithPeriod1(void)
{
	CpuTimer1Regs.TCR.bit.TRB = 1;
}

/******************************************************************************/
/* TMR_SetTimerWithPeriod2
 *
 * The function loads the period cont to the timer TIM register.			  */
/******************************************************************************/
void TMR_SetTimerWithPeriod2(void)
{
	CpuTimer2Regs.TCR.bit.TRB = 1;
}

/******************************************************************************/
/* TMR_GetTimer0
 *
 * The function gets the TIM register for the current timer count.			  */
/******************************************************************************/
unsigned long TMR_GetTimer0(void)
{
	unsigned long timer;

	timer = (unsigned long)CpuTimer0Regs.TIM.bit.MSW << 16;
	timer += CpuTimer0Regs.TIM.bit.LSW;

	return timer;
}

/******************************************************************************/
/* TMR_GetTimer1
 *
 * The function gets the TIM register for the current timer count.			  */
/******************************************************************************/
unsigned long TMR_GetTimer1(void)
{
	unsigned long timer;

	timer = (unsigned long)CpuTimer1Regs.TIM.bit.MSW << 16;
	timer += CpuTimer1Regs.TIM.bit.LSW;

	return timer;
}

/******************************************************************************/
/* TMR_GetTimer2
 *
 * The function gets the TIM register for the current timer count.			  */
/******************************************************************************/
unsigned long TMR_GetTimer2(void)
{
	unsigned long timer;

	timer = (unsigned long)CpuTimer2Regs.TIM.bit.MSW << 16;
	timer += CpuTimer2Regs.TIM.bit.LSW;

	return timer;
}

/******************************************************************************/
/* TMR_SetTimerPeriod0
 *
 * The function sets the PRD register for the period count.					  */
/******************************************************************************/
void TMR_SetTimerPeriod0(unsigned long period)
{
	CpuTimer0Regs.PRD.bit.MSW = (period >> 16);
	CpuTimer0Regs.PRD.bit.LSW = period;
}

/******************************************************************************/
/* TMR_SetTimerPeriod1
 *
 * The function sets the PRD register for the period count.					  */
/******************************************************************************/
void TMR_SetTimerPeriod1(unsigned long period)
{
	CpuTimer1Regs.PRD.bit.MSW = (period >> 16);
	CpuTimer1Regs.PRD.bit.LSW = period;
}

/******************************************************************************/
/* TMR_SetTimerPeriod2
 *
 * The function sets the PRD register for the period count.					  */
/******************************************************************************/
void TMR_SetTimerPeriod2(unsigned long period)
{
	CpuTimer2Regs.PRD.bit.MSW = (period >> 16);
	CpuTimer2Regs.PRD.bit.LSW = period;
}

/******************************************************************************/
/* TMR_GetTimerPeriod0
 *
 * The function gets the PRD register for the period count.					  */
/******************************************************************************/
unsigned long TMR_GetTimerPeriod0(void)
{
	unsigned long period;

	period = (unsigned long)CpuTimer0Regs.PRD.bit.MSW << 16;
	period += CpuTimer0Regs.PRD.bit.LSW;

	return period;
}

/******************************************************************************/
/* TMR_GetTimerPeriod1
 *
 * The function gets the PRD register for the period count.					  */
/******************************************************************************/
unsigned long TMR_GetTimerPeriod1(void)
{
	unsigned long period;

	period = (unsigned long)CpuTimer1Regs.PRD.bit.MSW << 16;
	period += CpuTimer1Regs.PRD.bit.LSW;

	return period;
}

/******************************************************************************/
/* TMR_GetTimerPeriod2
 *
 * The function gets the PRD register for the period count.					  */
/******************************************************************************/
unsigned long TMR_GetTimerPeriod2(void)
{
	unsigned long period;

	period = (unsigned long)CpuTimer2Regs.PRD.bit.MSW << 16;
	period += CpuTimer2Regs.PRD.bit.LSW;

	return period;
}

/******************************************************************************/
/* TMR_Interrupt0
 *
 * The function controls the Timer 0 interrupt.								  */
/******************************************************************************/
unsigned char TMR_Interrupt0(unsigned char state)
{
    unsigned char status = CpuTimer0Regs.TCR.bit.TIE;

    SYS_Unlock();
    if(state)
    {
    	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;  	// PIE Group 1, INT7
    	CpuTimer0Regs.TCR.bit.TIE = 1; 			// Enable the Timer interrupt
    }
    else
    {
    	PieCtrlRegs.PIEIER1.bit.INTx7 = 0;  	// PIE Group 1, INT7
    	CpuTimer0Regs.TCR.bit.TIE = 0; 			// Disable the Timer interrupt
    }
    SYS_Lock();
    return status;
}

/******************************************************************************/
/* TMR_Interrupt1
 *
 * The function controls the Timer 1 interrupt.								  */
/******************************************************************************/
unsigned char TMR_Interrupt1(unsigned char state)
{
    unsigned char status = CpuTimer1Regs.TCR.bit.TIE;

    SYS_Unlock();
    if(state)
    {
    	CpuTimer1Regs.TCR.bit.TIE = 1; 			// Enable the Timer interrupt
    }
    else
    {
    	CpuTimer1Regs.TCR.bit.TIE = 0; 			// Disable the Timer interrupt
    }
    SYS_Lock();
    return status;
}

/******************************************************************************/
/* TMR_Interrupt2
 *
 * The function controls the Timer 2 interrupt.								  */
/******************************************************************************/
unsigned char TMR_Interrupt2(unsigned char state)
{
    unsigned char status = CpuTimer2Regs.TCR.bit.TIE;

    SYS_Unlock();
    if(state)
    {
    	CpuTimer2Regs.TCR.bit.TIE = 1; 			// Enable the Timer interrupt
    }
    else
    {
    	CpuTimer2Regs.TCR.bit.TIE = 0; 			// Disable the Timer interrupt
    }
    SYS_Lock();
    return status;
}

/******************************************************************************/
/* TMR_StartTimer0
 *
 * The function either starts or stops the timer.							  */
/******************************************************************************/
void TMR_StartTimer0(unsigned char state)
{
	if(state)
	{
		CpuTimer0Regs.TCR.bit.TSS = 0; // start or restart the CPU-timer
	}
	else
	{
		CpuTimer0Regs.TCR.bit.TSS = 1; // stop the CPU-timer
	}
}


/******************************************************************************/
/* TMR_StartTimer1
 *
 * The function either starts or stops the timer.							  */
/******************************************************************************/
void TMR_StartTimer1(unsigned char state)
{
	if(state)
	{
		CpuTimer1Regs.TCR.bit.TSS = 0; // start or restart the CPU-timer
	}
	else
	{
		CpuTimer1Regs.TCR.bit.TSS = 1; // stop the CPU-timer
	}
}

/******************************************************************************/
/* TMR_StartTimer2
 *
 * The function either starts or stops the timer.							  */
/******************************************************************************/
void TMR_StartTimer2(unsigned char state)
{
	if(state)
	{
		CpuTimer2Regs.TCR.bit.TSS = 0; // start or restart the CPU-timer
	}
	else
	{
		CpuTimer2Regs.TCR.bit.TSS = 1; // stop the CPU-timer
	}
}

/******************************************************************************/
/* TMR_GetStartTimerStatus0
 *
 * The function returns TRUE if the timer is running.						  */
/******************************************************************************/
unsigned char TMR_GetStartTimerStatus0(void)
{
	if(CpuTimer0Regs.TCR.bit.TSS)
	{
		return FALSE;
	}
	return TRUE;
}

/******************************************************************************/
/* TMR_GetStartTimerStatus1
 *
 * The function returns TRUE if the timer is running.						  */
/******************************************************************************/
unsigned char TMR_GetStartTimerStatus1(void)
{
	if(CpuTimer1Regs.TCR.bit.TSS)
	{
		return FALSE;
	}
	return TRUE;
}

/******************************************************************************/
/* TMR_GetStartTimerStatus2
 *
 * The function returns TRUE if the timer is running.						  */
/******************************************************************************/
unsigned char TMR_GetStartTimerStatus2(void)
{
	if(CpuTimer2Regs.TCR.bit.TSS)
	{
		return FALSE;
	}
	return TRUE;
}

/******************************************************************************/
/* TMR_SetTimerFlag0
 *
 * The function sets the timer 0 flag.										  */
/******************************************************************************/
void TMR_SetTimerFlag0(void)
{
	Timer0_Timeout = TRUE;
}

/******************************************************************************/
/* TMR_ClearTimerFlag0
 *
 * The function clears the timer 0 flag.									  */
/******************************************************************************/
void TMR_ClearTimerFlag0(void)
{
	Timer0_Timeout = FALSE;
}

/******************************************************************************/
/* TMR_GetTimerFlag0
 *
 * The function gets the timer 0 flag.										  */
/******************************************************************************/
unsigned char TMR_GetTimerFlag0(void)
{
	return Timer0_Timeout;
}

/******************************************************************************/
/* TMR_CountsToMicroseconds
 *
 * The function calculates microseconds from counts.						  */
/******************************************************************************/
unsigned long TMR_CountsToMicroseconds(unsigned long counts)
{
	unsigned long microseconds;

	microseconds = (unsigned long) MSC_Round((16.0 / (double)SYSCLK) * (double) counts * 1000000.0);
	return microseconds;
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
