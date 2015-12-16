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
/* Contains system functions.
 *																			  */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "SYSTEM.h"

/******************************************************************************/
/* Functions																  */
/******************************************************************************/

/******************************************************************************/
/* SYS_ConfigureOscillator
 *
 * The function waits for the high frequency oscillator to be working and
 *  stable.																	  */
/******************************************************************************/
void SYS_ConfigureOscillator(void)
{    
	SYS_DisableWatchdog();

#ifdef _FLASH
	/* Copy time critical code and Flash setup code to RAM. This includes the
	 *  following functions:  InitFlash(); The  RamfuncsLoadStart, RamfuncsLoadSize, and RamfuncsRunStart
	 *  symbols are created by the linker. Refer to the device .cmd file.
	 */
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);

    /* Call Flash Initialization to setup flash waitstates. This function must reside in RAM */
    InitFlash_Bank0();
#endif

    EALLOW;

    /* enable pull-ups on unbonded IOs as soon as possible to reduce power consumption */
    GPIO_EnableUnbondedIOPullups();

   	CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
   	CpuSysRegs.PCLKCR13.bit.ADC_B = 1;
   	CpuSysRegs.PCLKCR13.bit.ADC_C = 1;
   	CpuSysRegs.PCLKCR13.bit.ADC_D = 1;

	//check if device is trimmed
	if(*((Uint16 *)0x5D1B6) == 0x0000){
	   //device is not trimmed, apply static calibration values
	   AnalogSubsysRegs.ANAREFTRIMA.all = 31709;
	   AnalogSubsysRegs.ANAREFTRIMB.all = 31709;
	   AnalogSubsysRegs.ANAREFTRIMC.all = 31709;
	   AnalogSubsysRegs.ANAREFTRIMD.all = 31709;
	}

   	CpuSysRegs.PCLKCR13.bit.ADC_A = 0;
   	CpuSysRegs.PCLKCR13.bit.ADC_B = 0;
   	CpuSysRegs.PCLKCR13.bit.ADC_C = 0;
   	CpuSysRegs.PCLKCR13.bit.ADC_D = 0;
   	EDIS;

   	/* configure the PLL */
   	InitSysPll(XTAL_OSC,IMULT_40,FMULT_0,PLLCLK_BY_2); 		//PLLSYSCLK = (XTAL_OSC) * (IMULT + FMULT) / (PLLSYSCLKDIV)

	//Turn on all peripherals
	InitPeripheralClocks();
}

/******************************************************************************/
/* SYS_DisableWatchdog
 *
 * The function disables the watch dog.										  */
/******************************************************************************/
void SYS_DisableWatchdog(void)
{
	volatile Uint16 temp;
    EALLOW;

    /* Save the watchdog clock configuration */
    temp = WdRegs.WDCR.all & 0x0007;
    WdRegs.WDCR.all = 0x0068 | temp;
    EDIS;
}

/******************************************************************************/
/* SYS_Interrupts
 *
 * The function controls the interrupts.									  */
/******************************************************************************/
void SYS_Interrupts(unsigned char state)
{
    if(state)
    {
    	EINT;
    }
    else
    {
    	DINT;
    }
}

/******************************************************************************/
/* SYS_ClearPIE
 *
 * The function clears all registers associated with the PIE
 *  (Peripheral interrupts Enable).											  */
/******************************************************************************/
void SYS_ClearPIE(void)
{
    /* Disable the PIE */
    PieCtrlRegs.PIECTRL.bit.ENPIE = 0;

    /* Clear all PIEIER registers */
	PieCtrlRegs.PIEIER1.all = 0;
	PieCtrlRegs.PIEIER2.all = 0;
	PieCtrlRegs.PIEIER3.all = 0;
	PieCtrlRegs.PIEIER4.all = 0;
	PieCtrlRegs.PIEIER5.all = 0;
	PieCtrlRegs.PIEIER6.all = 0;
	PieCtrlRegs.PIEIER7.all = 0;
	PieCtrlRegs.PIEIER8.all = 0;
	PieCtrlRegs.PIEIER9.all = 0;
	PieCtrlRegs.PIEIER10.all = 0;
	PieCtrlRegs.PIEIER11.all = 0;
	PieCtrlRegs.PIEIER12.all = 0;

	/* Clear all PIEIFR registers */
	PieCtrlRegs.PIEIFR1.all = 0;
	PieCtrlRegs.PIEIFR2.all = 0;
	PieCtrlRegs.PIEIFR3.all = 0;
	PieCtrlRegs.PIEIFR4.all = 0;
	PieCtrlRegs.PIEIFR5.all = 0;
	PieCtrlRegs.PIEIFR6.all = 0;
	PieCtrlRegs.PIEIFR7.all = 0;
	PieCtrlRegs.PIEIFR8.all = 0;
	PieCtrlRegs.PIEIFR9.all = 0;
	PieCtrlRegs.PIEIFR10.all = 0;
	PieCtrlRegs.PIEIFR11.all = 0;
	PieCtrlRegs.PIEIFR12.all = 0;
}

/******************************************************************************/
/* SYS_PIEVectorTable
 *
 * Wrapper function that sets up the interrupt vectors.  					  */
/******************************************************************************/
void SYS_PIEVectorTable(void)
{
	InitPieVectTable();
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
