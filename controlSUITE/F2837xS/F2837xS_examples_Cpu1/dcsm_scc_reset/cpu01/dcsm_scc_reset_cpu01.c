//###########################################################################
// FILE:   dcsm_scc_reset_cpu01.c
// TITLE:  SafeCopyCode Reset
//
//! \addtogroup cpu01_example_list
//! <h1> SafeCopyCode Reset (dcsm_scc_reset_cpu01) </h1>
//!
//! This example shows how to issue a reset using the SafeCopyCode (SCC)
//! function. In the case of a vector fetch while the PC points to the SCC
//! function, an SCCRESETn gets generated. In this example, a CPU Timer
//! interrupt is enabled to cause this vector fetch.
//
//###########################################################################
// $TI Release: F2837xS Support Library v180 $
// $Release Date: Fri Nov  6 16:27:58 CST 2015 $
// $Copyright: Copyright (C) 2014-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "F28x_Project.h"     // Device Headerfile and Examples Include File

void IssueSCCReset(void);
extern Uint16 SafeCopyCodeZ1(Uint32 size, Uint16 *dst, Uint16 *src);

void main(void)
{
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xS_SysCtrl.c file.
    InitSysCtrl();

// Step 2. Initialize GPIO:
// This example function is found in the F2837xS_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
    InitGpio();

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
    DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the F2837xS_PieCtrl.c file.
    InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xS_DefaultIsr.c.
// This function is found in F2837xS_PieVect.c.
    InitPieVectTable();

// Step 4. Call function to issue the SCC reset. If the SCC reset has
// already occured, the program will stop here.
    if(CpuSysRegs.RESC.bit.SCCRESETn != 1)
    {
        IssueSCCReset();
    }
    else
    {
        ESTOP0;
        for(;;);
    }
}

// This function will generate SCC Reset
void IssueSCCReset(void)
{
	// Initialize CPU timers. This will stop all timers.
	InitCpuTimers();

	// Configure CPU Timer 0 for a 500ns period @200MHz CPU Frq
	ConfigCpuTimer(&CpuTimer0, 200, 0.5);

	EALLOW;

	// Enable CPU interrupt 1
	IER |= M_INT1;
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

	// Start Timer
	CpuTimer0Regs.TCR.all = 0x4020;

	// Enable Global interrupt INTM
	EINT;
	EDIS;

	while(1)
	{
		SafeCopyCodeZ1(32, (Uint16 *)0xC000, (Uint16 *)0x80000);
	}
}
