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

#include "ADC.h"
#include "INTERRUPTS.h"
#include "SYSTEM.h"
#include "USER.h"

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
/* InitADC
 *
 * The function initializes the analog to digital converter.				  */
/******************************************************************************/
void InitADC(void)
{
	/* Set ADC ISRs */
	SYS_Unlock();
	PieVectTable.ADCA2_INT = &ISR_ADC_AUDIO;
	SYS_Lock();

	SYS_EnableInterruptGroup(INTERRUPT_GROUP10);	// Group for ADC

	SYS_Unlock();
	/* Configure clock */
	AdcaRegs.ADCCTL2.bit.PRESCALE = 0b1110; // 1110 ADCCLK = Input Clock / 8.0
	/* set mode */
    ADC_SetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
	/* Set pulse positions to late */
	AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
	/* Setup the post-processing block to be associated with SOC0 */
	AdcaRegs.ADCPPB1CONFIG.bit.CONFIG = 0;
	ADC_ModuleA(ON);
	SYS_Lock();

	/* set up for continuous mode */
	ADC_SetupContinuousA();
}

/******************************************************************************/
/* ADC_ModuleA
 *
 * The function controls ADC module A analog circuitry.						  */
/******************************************************************************/
void ADC_ModuleA(unsigned char state)
{
	if(state)
	{
		AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1; 	// enable power the ADC module A
	}
	else
	{
		AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 0; 	// disable power the ADC module A
	}
}

/******************************************************************************/
/* ADC_SetMode
 *
 * The function sets the resolution and signal mode for a given ADC and loads
 *  the trim.																  */
/******************************************************************************/
void ADC_SetMode(ENUM_ADC_MODULE adc, ENUM_ADC_RESOLUTION resolution, ENUM_ADC_MODE signalmode)
{
	unsigned short adcOffsetTrimOTPIndex; 	// index into OTP table of ADC offset trims
	unsigned short adcOffsetTrim; 			// temporary ADC offset trim

	/* re-populate INL trim */
	ADC_LoadTrim(adc);

	if(*(unsigned short*)ADC_GetSetADCTrimPOINTER != 0xFFFF)
	{
		/*
		 * Offset trim function is programmed into OTP, so call it. Calculate the index
		 *  into OTP table of offset trims and call function to return the correct offset
		 *  trim.
		 */
		adcOffsetTrimOTPIndex = 4*adc + 2*resolution + 1*signalmode;
		adcOffsetTrim = (*ADC_GetSetADCTrimPOINTER)(adcOffsetTrimOTPIndex);
	}
	else
	{
		/* offset trim function is not populated, so set offset trim to 0 */
		adcOffsetTrim = 0;
	}

	/*
	 * Apply the resolution and signalmode to the specified ADC. Also apply the offset trim
	 *  and, if needed, linearity trim correction.
	 */
	switch(adc)
	{
		case ADC_ADCA:
			AdcaRegs.ADCCTL2.bit.RESOLUTION = resolution;
			AdcaRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
			AdcaRegs.ADCOFFTRIM.all = adcOffsetTrim;
			if(resolution == ADC_RESOLUTION_12BIT)
			{

				/* 12-bit linearity trim workaround */
				AdcaRegs.ADCINLTRIM1 &= 0xFFFF0000;
				AdcaRegs.ADCINLTRIM2 &= 0xFFFF0000;
				AdcaRegs.ADCINLTRIM4 &= 0xFFFF0000;
				AdcaRegs.ADCINLTRIM5 &= 0xFFFF0000;
			}
			break;
		case ADC_ADCB:
			AdcbRegs.ADCCTL2.bit.RESOLUTION = resolution;
			AdcbRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
			AdcbRegs.ADCOFFTRIM.all = adcOffsetTrim;
			if(resolution == ADC_RESOLUTION_12BIT)
			{
				/* 12-bit linearity trim workaround */
				AdcbRegs.ADCINLTRIM1 &= 0xFFFF0000;
				AdcbRegs.ADCINLTRIM2 &= 0xFFFF0000;
				AdcbRegs.ADCINLTRIM4 &= 0xFFFF0000;
				AdcbRegs.ADCINLTRIM5 &= 0xFFFF0000;
			}
			break;
		case ADC_ADCC:
			AdccRegs.ADCCTL2.bit.RESOLUTION = resolution;
			AdccRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
			AdccRegs.ADCOFFTRIM.all = adcOffsetTrim;
			if(resolution == ADC_RESOLUTION_12BIT)
			{
				/* 12-bit linearity trim workaround */
				AdccRegs.ADCINLTRIM1 &= 0xFFFF0000;
				AdccRegs.ADCINLTRIM2 &= 0xFFFF0000;
				AdccRegs.ADCINLTRIM4 &= 0xFFFF0000;
				AdccRegs.ADCINLTRIM5 &= 0xFFFF0000;
			}
			break;
		case ADC_ADCD:
			AdcdRegs.ADCCTL2.bit.RESOLUTION = resolution;
			AdcdRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
			AdcdRegs.ADCOFFTRIM.all = adcOffsetTrim;
			if(resolution == ADC_RESOLUTION_12BIT)
			{
				/* 12-bit linearity trim workaround */
				AdcdRegs.ADCINLTRIM1 &= 0xFFFF0000;
				AdcdRegs.ADCINLTRIM2 &= 0xFFFF0000;
				AdcdRegs.ADCINLTRIM4 &= 0xFFFF0000;
				AdcdRegs.ADCINLTRIM5 &= 0xFFFF0000;
			}
			break;
	}
}

/******************************************************************************/
/* ADC_LoadTrim
 *
 * The function loads trim values from the OTP into trim registers of the ADC.*/
/******************************************************************************/
void ADC_LoadTrim(ENUM_ADC_MODULE adc)
{
	switch(adc)
	{
		case ADC_ADCA:
			if(*(unsigned short*)ADC_CalADC_A_INL_POINTER != 0xFFFF)
			{
				/* trim function is programmed into OTP, so call it */
				(*ADC_CalADC_A_INL_POINTER)();
			}
			else
			{
				/* do nothing, no INL trim function populated */
			}
			break;
		case ADC_ADCB:
			if(*(unsigned short*)ADC_CalADC_B_INL_POINTER != 0xFFFF)
			{
				/* trim function is programmed into OTP, so call it */
				(*ADC_CalADC_B_INL_POINTER)();
			}
			else
			{
				/* do nothing, no INL trim function populated */
			}
			break;
		case ADC_ADCC:
			if(*(unsigned short*)ADC_CalADC_C_INL_POINTER != 0xFFFF)
			{
				/* trim function is programmed into OTP, so call it */
				(*ADC_CalADC_C_INL_POINTER)();
			}
			else
			{
				/* do nothing, no INL trim function populated */
			}
			break;
		case ADC_ADCD:
			if(*(unsigned short*)ADC_CalADC_D_INL_POINTER != 0xFFFF)
			{
				/* trim function is programmed into OTP, so call it */
				(*ADC_CalADC_D_INL_POINTER)();
			}
			else
			{
				/* do nothing, no INL trim function populated */
			}
			break;
	}
}

/******************************************************************************/
/* ADC_SetupContinuousA
 *
 * The function sets the ADC module A to continuously convert on one channel. */
/******************************************************************************/
void ADC_SetupContinuousA(void)
{
	unsigned short acqps;

	/* determine minimum acquisition window (in SYSCLKS) based on resolution */
	if(AdcaRegs.ADCCTL2.bit.RESOLUTION == ADC_RESOLUTION_12BIT)
	{
		acqps = 14;	// 75ns
	}
	else
	{
		acqps = 63;	// 320ns
	}

	SYS_Unlock();
	AdcaRegs.ADCSOC0CTL.bit.CHSEL  = ADC_AUDIO_1_GPIO;  	// SOC0 will convert on cahnnel A0
	AdcaRegs.ADCSOC1CTL.bit.CHSEL  = ADC_AUDIO_3_GPIO;  	// SOC1 will convert on channel A1

	AdcaRegs.ADCSOC0CTL.bit.ACQPS  = acqps;    	// sample window is acqps + 1 SYSCLK cycles
	AdcaRegs.ADCSOC1CTL.bit.ACQPS  = acqps;    	// sample window is acqps + 1 SYSCLK cycles

	AdcaRegs.ADCINTSEL1N2.bit.INT1E = 0;		// 0 ADCINT1 is disabled
	AdcaRegs.ADCINTSEL1N2.bit.INT2E = 0; 		// 0 ADCINT2 is disabled
	AdcaRegs.ADCINTSEL3N4.bit.INT3E = 0; 		// 0 ADCINT3 is disabled
	AdcaRegs.ADCINTSEL3N4.bit.INT4E = 0; 		// 0 ADCINT4 is disabled

	/*
	 * 1 ADCINT1 pulses are generated whenever an EOC pulse is generated irrespective of whether
	 *  the flag bit is cleared or not.
	 */
	AdcaRegs.ADCINTSEL1N2.bit.INT1CONT = 1;
	AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0x0;  	// 0h EOC0 is trigger for ADCINT1

	/* No trigger for SOC0 */
   	AdcaRegs.ADCINTSOCSEL1.bit.SOC0 = 0b00;

	/*
	 * 0 No further ADCINT2 pulses are generated until ADCINT2 flag (in ADCINTFLG register) is
	 *  cleared by user.
	 */
	AdcaRegs.ADCINTSEL1N2.bit.INT2CONT = 1;
	AdcaRegs.ADCINTSEL1N2.bit.INT2SEL = 0x1;  	// 1h EOC1 is trigger for ADCINT2

	/* No trigger for SOC1 */
   	AdcaRegs.ADCINTSOCSEL1.bit.SOC1 = 0b01;		// ADCINT1 will trigger SOC1. TRIGSEL field is ignored.

   	SYS_Lock();
}

/******************************************************************************/
/* ADC_BusyA
 *
 * The function returns the status of the ADC module.						  */
/******************************************************************************/
unsigned char ADC_BusyA(void)
{
	if(AdcaRegs.ADCCTL1.bit.ADCBSY)
	{
		return TRUE;
	}
	return FALSE;
}

/******************************************************************************/
/* ADC_InterruptA
 *
 * The function controls the ADC module A interrupt.						  */
/******************************************************************************/
void ADC_InterruptA(unsigned char state)
{
	SYS_Unlock();
	if(state)
	{
		PieCtrlRegs.PIEIER10.bit.INTx2  = 1;	// PIE Group 10, INT2
		AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;	// enable INT1 interrupt
		AdcaRegs.ADCINTSEL1N2.bit.INT2E = 1;	// enable INT2 interrupt
	}
	else
	{
		PieCtrlRegs.PIEIER10.bit.INTx2  = 0;	// PIE Group 10, INT2
		AdcaRegs.ADCINTSEL1N2.bit.INT1E = 0;	// disable INT1 interrupt
		AdcaRegs.ADCINTSEL1N2.bit.INT2E = 0; 	// disable INT2 interrupt
	}
	SYS_Lock();
}

/******************************************************************************/
/* ADC_ForceSampleA
 *
 * The function forces a conversion. 										  */
/******************************************************************************/
void ADC_ForceSampleA(void)
{
	AdcaRegs.ADCSOCFRC1.bit.SOC0 = 1; 	// Force SOC0 flag bit to 1. This will cause a conversion to start once	priority is given to SOC0.
}

/******************************************************************************/
/* ADC_GetStatusA
 *
 * The function returns the conversion status of the ADC.					  */
/******************************************************************************/
unsigned char ADC_GetStatusA(void)
{
	if(AdcaRegs.ADCSOCFLG1.bit.SOC0 || AdcaRegs.ADCSOCFLG1.bit.SOC1)
	{
		/*  Trigger has been received and sample is pending for SOC0 or SOC1 */
		return TRUE;
	}
	/* No sample pending for SOC0 or SOC1 */
	return FALSE;
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
