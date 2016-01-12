//###########################################################################
// FILE:   lpm_haltwake.c
// TITLE:  Halt entry and Exit Example for F2837xS.
//
//! \addtogroup cpu01_example_list
//!  <h1>Low Power Modes: Halt Mode and Wakeup (lpm_haltwake)</h1>
//!
//!  This example puts the device into HALT mode. If the lowest
//!  possible current consumption in HALT mode is desired, the
//!  JTAG connector must be removed from the device board while
//!  the device is in HALT mode.
//!
//!  The example then wakes up the device from HALT using GPIO10.
//!  GPIO10 wakes the device from HALT mode when a high-to-low
//!  signal is detected on the pin. This pin must be pulsed by
//!  an external agent for wakeup.
//!
//!  The wakeup process begins as soon as GPIO10 is held low for the
//!  time indicated in the device datasheet. After the
//!  device wakes up, GPIO11 can be observed to go low.
//!
//!  GPIO10 is configured as the LPM wakeup pin to trigger a
//!  WAKEINT interrupt upon detection of a low pulse.
//!  Initially, pull GPIO10 high externally.
//!
//!  To observe when device wakes from HALT mode, monitor
//!  GPIO11 with an oscilloscope (Cleared to 0 in WAKEINT ISR)
//
//###########################################################################
// $TI Release: F2837xS Support Library v180 $
// $Release Date: Fri Nov  6 16:27:58 CST 2015 $
// $Copyright: Copyright (C) 2014-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "F28x_Project.h"     // Device Headerfile and Examples Include File

#ifdef _FLASH
// These are defined by the linker (see device linker command file)
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadSize;
extern Uint16 RamfuncsRunStart;
#endif

// Prototype statements for functions found within this file.
__interrupt void local_WAKE_ISR(void);  	// ISR for WAKEINT

// Define if the INTOSC0/1 will be enabled during HALT
//#define HALT_OSCON 	1			// OSC ON
#define HALT_OSCON	0		// OSC OFF

void main(void)
{
	Uint16 afterWdReset = 0;

	//When the example is used with the WatchDog Timer, the WatchDog
	//timer will reset the device when it is LPM. If the example is run
	//from flash and the device is in a boot to flash configuration,
	//then it will restart the application and will enter the condition
	//below and ESTOP0 if the debugger is connected.
	//
	//Check whether this was a normal startup or a watchdog reset.
	//
	afterWdReset = CpuSysRegs.RESC.bit.WDRSn;
	// clear the reset cause bit.
	CpuSysRegs.RESC.bit.WDRSn = 1;
	if (afterWdReset)
	{
		ESTOP0;
	}

	// Step 1. Initialize System Control:
	// PLL, WatchDog, enable Peripheral Clocks
	// This example function is found in the F2837xS_SysCtrl.c file.
	InitSysCtrl();

	// Step 2. Initialize GPIO:
	// This example function is found in the F2837xS_Gpio.c file and
	// illustrates how to set the GPIO to it's default state.
	InitGpio();

	// configure Gpios for this example

	// GPIO10 is the external wake-up source
	GPIO_SetupPinMux(10,GPIO_MUX_CPU1,0);
	GPIO_SetupPinOptions(10,GPIO_INPUT,GPIO_PULLUP|GPIO_ASYNC);

	// GPIO11 is an output
	GPIO_SetupPinMux(11,GPIO_MUX_CPU1,0);
	GPIO_SetupPinOptions(11,GPIO_OUTPUT,0);


	EALLOW;
	// Use GPIO10 to wake the CPU from Halt
	CpuSysRegs.GPIOLPMSEL0.bit.GPIO10 = 1;
	EDIS;
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

	// Interrupts that are used in this example are re-mapped to
	// ISR functions found within this file.
	EALLOW;  // This is needed to write to EALLOW protected registers
	PieVectTable.WAKE_INT = &local_WAKE_ISR;
	EDIS;

	// Step 4. Initialize all the Device Peripherals:
	// Not applicable for this example.

	// Step 5. User specific code, enable interrupts:

	// Enable CPU INT1 which is connected to WakeInt:
	IER |= M_INT1;

	// Enable WAKEINT in the PIE: Group 1 interrupt 8
	PieCtrlRegs.PIEIER1.bit.INTx8 = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

	// Enable global Interrupts:
	EINT;   // Enable Global interrupt INTM

	// Set if the Oscillators will be on or off
	if(HALT_OSCON)
	{
		// WD is functional in HALT
		EALLOW;
		CpuSysRegs.LPMCR.bit.WDINTE = 1; //watchdog interrupt will wake the device
		WdRegs.SCSR.bit.WDENINT = 1; //enable the WD interrupt
		ClkCfgRegs.CLKSRCCTL1.bit.WDHALTI = 1; //WD is functional in the HALT mode
		EDIS;

		// Reset WD. Uncomment this section
		// if WD wakeup is desired.
//		ServiceDog();
//		// Enable the watchdog to wake the device from HALT
//		EALLOW;
//		WdRegs.WDCR.all = 0x0028;
//		EDIS;
	}
	else
	{
		// WD is not functional in HALT
		EALLOW;
		CpuSysRegs.LPMCR.bit.WDINTE = 0;
		ClkCfgRegs.CLKSRCCTL1.bit.WDHALTI = 0;
		EDIS;
	}

	// Ensure there are no subsequent flash accesses to wake up the pump and bank
	// Power down the flash bank and pump
	SeizeFlashPump_Bank0();
	FlashOff_Bank0();
	ReleaseFlashPump();
	SeizeFlashPump_Bank1();
	FlashOff_Bank1();
	ReleaseFlashPump();

    GpioDataRegs.GPASET.bit.GPIO11 = 1;		// GPIO11 is Set high before entering HALT
    HALT();		//enter enter HALT mode

	// Reconfigure PLL after waking from HALT
	InitSysPll(XTAL_OSC,IMULT_20,FMULT_0,PLLCLK_BY_2); 	//PLLSYSCLK = (XTAL_OSC) * (IMULT + FMULT) / (PLLSYSCLKDIV)
	ESTOP0;

	// loop forever
	while(1);

}	// end of Main

interrupt void local_WAKE_ISR(void)
{
   GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;	// GPIO11 is cleared upon exiting HALT.
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

