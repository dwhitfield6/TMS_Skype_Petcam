/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 01/18/16     13.0_DW0a   Created.
 *                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Contains functions for the PWM module.
 *																			  */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "AUDIO.h"
#include "INTERRUPTS.h"
#include "MISC.h"
#include "PWM.h"
#include "SYSTEM.h"
#include "TIMERS.h"
#include "USER.h"

/******************************************************************************/
/* Private Variable Declaration		                                          */
/******************************************************************************/
static unsigned short PWM8_B_Compare = 0;
static unsigned short PWM11_A_Compare = 0;

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
unsigned short Period38kHz = 0;
unsigned short PeriodLowpass = 0;

/******************************************************************************/
/* Inline Functions															  */
/******************************************************************************/
 
/******************************************************************************/
/* Functions																  */
/******************************************************************************/

/******************************************************************************/
/* InitPWM
 *
 * The function initializes the PWM module.									  */
/******************************************************************************/
void InitPWM(void)
{
	InitPWM_IR();
	InitPWM_AudioLowpass();
}

/******************************************************************************/
/* InitPWM_IR
 *
 * The function initializes the PWM module for the IR LED.					  */
/******************************************************************************/
void InitPWM_IR(void)
{
	Period38kHz = PWM_SetFrequency(38000.0);

	/* Set PWM ISRs */
	SYS_Unlock();
	PieVectTable.EPWM8_INT = &ISR_EPWM_8_IRLED;
	SYS_Lock();

	SYS_EnableInterruptGroup(INTERRUPT_GROUP3);	// Group for PWM
	PWM_Interrupt8(OFF);

	/* Setup TBCLK */
	EPwm8Regs.TBCTL.bit.CTRMODE = 0b00;	// 00: Up-count mode
	EPwm8Regs.TBPRD = Period38kHz;   	// Set timer period
	EPwm8Regs.TBCTL.bit.PHSEN = 0; 		// Do not load the time-base counter (TBCTR) from the time-base	phase register (TBPHS)
	EPwm8Regs.TBPHS.bit.TBPHS = 0x0000; // Phase is 0
	PWM_ResetTBClock8();
	EPwm8Regs.TBCTL.bit.CLKDIV = 0b000;	// 000: /1 (default on reset)
	EPwm8Regs.TBCTL.bit.HSPCLKDIV = 0b001; // 001: /2 (default on reset)

	/* Setup shadow register load on period match */
	EPwm8Regs.CMPCTL.bit.SHDWBMODE = 0;		// Shadow mode. Operates as a double buffer. All writes via the CPU access the shadow register
	EPwm8Regs.CMPCTL.bit.LOADBMODE = 0b01;	//Load on CTR = PRD: Time-base counter equal to period (TBCTR = TBPRD)

	/* Set Compare values */
	PWM_SetDutyCycle8B(50);

	/* Set actions */
	EPwm8Regs.AQCTLB.bit.ZRO = 0b01;	// Clear PWM8BA on Zero
	EPwm8Regs.AQCTLB.bit.CBU = 0b10;    // Set PWM8BA on event A, up count

	/* Interrupt where we will change the Compare Values */
	EPwm8Regs.ETSEL.bit.INTSEL = 0b010;	// Enable event time-base counter equal to period (TBCTR = TBPRD)
	EPwm8Regs.ETPS.bit.INTPRD = 0b01;   // Generate an interrupt on the first event INTCNT = 01 (first event)
}

/******************************************************************************/
/* InitPWM_AudioLowpass
 *
 * The function initializes the PWM module for the Lowpass filter IC.		  */
/******************************************************************************/
void InitPWM_AudioLowpass(void)
{
	PeriodLowpass = PWM_SetFrequency(LOWPASS_CORNER_FREQUENCY * 100.0);

	/* Set PWM ISRs */
	SYS_Unlock();
	PieVectTable.EPWM11_INT = &ISR_EPWM_11_LOWPASS;
	SYS_Lock();

	SYS_EnableInterruptGroup(INTERRUPT_GROUP11);	// Group for PWM
	PWM_Interrupt11(OFF);

	/* Setup TBCLK */
	EPwm11Regs.TBCTL.bit.CTRMODE = 0b00;	// 00: Up-count mode
	EPwm11Regs.TBPRD = PeriodLowpass;   	// Set timer period
	EPwm11Regs.TBCTL.bit.PHSEN = 0; 		// Do not load the time-base counter (TBCTR) from the time-base	phase register (TBPHS)
	EPwm11Regs.TBPHS.bit.TBPHS = 0x0000; // Phase is 0
	PWM_ResetTBClock11();
	EPwm11Regs.TBCTL.bit.CLKDIV = 0b000;	// 000: /1 (default on reset)
	EPwm11Regs.TBCTL.bit.HSPCLKDIV = 0b001; // 001: /2 (default on reset)

	/* Setup shadow register load on period match */
	EPwm11Regs.CMPCTL.bit.SHDWAMODE = 0;		// Shadow mode. Operates as a double buffer. All writes via the CPU access the shadow register
	EPwm11Regs.CMPCTL.bit.LOADAMODE = 0b01;	//Load on CTR = PRD: Time-base counter equal to period (TBCTR = TBPRD)

	/* Set Compare values */
	PWM_SetDutyCycle11A(50);

	/* Set actions */
	EPwm11Regs.AQCTLA.bit.ZRO = 0b01;	// Clear PWM11A on Zero
	EPwm11Regs.AQCTLA.bit.CAU = 0b10;   // Set PWM11A on event A, up count

	/* Interrupt where we will change the Compare Values */
	EPwm11Regs.ETSEL.bit.INTSEL = 0b010;	// Enable event time-base counter equal to period (TBCTR = TBPRD)
	EPwm11Regs.ETPS.bit.INTPRD = 0b01;   // Generate an interrupt on the first event INTCNT = 01 (first event)
}

/******************************************************************************/
/* PWM_SetFrequency
 *
 * The function sets the PWM frequency.										  */
/******************************************************************************/
unsigned short PWM_SetFrequency(double frequency)
{
	unsigned short period;

	period = (unsigned short) MSC_Round(((double)EPWMCLK / (frequency * 2.0) - 1.0));

	return period;
}

/******************************************************************************/
/* PWM_SetDutyCycle8B
 *
 * The function sets the PWM8 B duty cycle.									  */
/******************************************************************************/
void PWM_SetDutyCycle8B(unsigned char duty)
{
	double D_duty;
	unsigned short compare;

	if(duty > 100)
	{
		duty = 100;
	}
	D_duty = (double) duty;
	D_duty /= 100.0; 		// get percentage

	compare = (unsigned short) MSC_Round((double)Period38kHz * D_duty);
	if(compare > Period38kHz)
	{
		compare = Period38kHz;
	}
	compare = Period38kHz - compare;	// inverse
	if(compare == 0)
	{
		compare += 1; // dont allow compare on 0 since we clear on 0
	}

	PWM_SetCMP8B(compare);
	PWM_Interrupt8(ON);
}

/******************************************************************************/
/* PWM_SetDutyCycle11A
 *
 * The function sets the PWM11 A duty cycle.								  */
/******************************************************************************/
void PWM_SetDutyCycle11A(unsigned char duty)
{
	double D_duty;
	unsigned short compare;

	if(duty > 100)
	{
		duty = 100;
	}
	D_duty = (double) duty;
	D_duty /= 100.0; 		// get percentage

	compare = (unsigned short) MSC_Round((double)PeriodLowpass * D_duty);
	if(compare > PeriodLowpass)
	{
		compare = PeriodLowpass;
	}
	compare = PeriodLowpass - compare;	// inverse
	if(compare == 0)
	{
		compare += 1; // dont allow compare on 0 since we clear on 0
	}

	PWM_SetCMP11A(compare);
	PWM_Interrupt11(ON);
}

/******************************************************************************/
/* PWM_SetCMP8B
 *
 * The function sets the compare variable to set during the next interrupt.   */
/******************************************************************************/
void PWM_SetCMP8B(unsigned short compare)
{
	PWM8_B_Compare = compare;
}

/******************************************************************************/
/* PWM_SetCMP11A
 *
 * The function sets the compare variable to set during the next interrupt.   */
/******************************************************************************/
void PWM_SetCMP11A(unsigned short compare)
{
	PWM11_A_Compare = compare;
}

/******************************************************************************/
/* PWM_GetCMP8B
 *
 * The function gets the compare variable to set during the next interrupt.   */
/******************************************************************************/
unsigned short PWM_GetCMP8B(void)
{
	return PWM8_B_Compare;
}

/******************************************************************************/
/* PWM_GetCMP11A
 *
 * The function gets the compare variable to set during the next interrupt.   */
/******************************************************************************/
unsigned short PWM_GetCMP11A(void)
{
	return PWM11_A_Compare;
}

/******************************************************************************/
/* PWM_ResetTBClock8
 *
 * The function resets the PWM clock.										  */
/******************************************************************************/
void PWM_ResetTBClock8(void)
{
	EPwm8Regs.TBCTR = 0x0000;
}

/******************************************************************************/
/* PWM_ResetTBClock11
 *
 * The function resets the PWM clock.										  */
/******************************************************************************/
void PWM_ResetTBClock11(void)
{
	EPwm11Regs.TBCTR = 0x0000;
}

/******************************************************************************/
/* PWM_Interrupt8
 *
 * The function controls the PWM 8 module interrupt.						  */
/******************************************************************************/
void PWM_Interrupt8(unsigned char state)
{
	SYS_Unlock();
	if(state)
	{
		EPwm8Regs.ETSEL.bit.INTEN = 1;		// Enable EPWMx_INT generation
		PieCtrlRegs.PIEIER3.bit.INTx8 = 1; 	// EPWM8 interrupt enabled
	}
	else
	{
		EPwm8Regs.ETSEL.bit.INTEN = 0;		// Disable EPWMx_INT generation
		PieCtrlRegs.PIEIER3.bit.INTx8 = 0;	// EPWM8 interrupt disabled
	}
	SYS_Lock();
}

/******************************************************************************/
/* PWM_Interrupt11
 *
 * The function controls the PWM 11 module interrupt.						  */
/******************************************************************************/
void PWM_Interrupt11(unsigned char state)
{
	SYS_Unlock();
	if(state)
	{
		EPwm11Regs.ETSEL.bit.INTEN = 1;		// Enable EPWMx_INT generation
		PieCtrlRegs.PIEIER3.bit.INTx11 = 1;	// EPWM11 interrupt enabled
	}
	else
	{
		EPwm11Regs.ETSEL.bit.INTEN = 0;		// Disable EPWMx_INT generation
		PieCtrlRegs.PIEIER3.bit.INTx11 = 0;	// EPWM11 interrupt disabled
	}
	SYS_Lock();
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
