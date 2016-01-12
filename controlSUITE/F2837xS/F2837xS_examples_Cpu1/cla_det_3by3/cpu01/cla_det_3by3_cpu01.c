//###########################################################################
// FILE:   cla_det_3by3_cpu01.c
// TITLE:  CLA Determinant of a 3X3 Matrix Example for F2837xS.
//
//! \addtogroup cpu01_example_list
//! <h1>CLA Determinant of 3X3 Matrix (cla_det_3by3_cpu01)</h1>
//!
//! In this example, Task 1 of the CLA will calculate the determinant of
//! a 3x3 matrix.
//!
//! \b Memory \b Allocation \n
//!  - CLA1 to CPU Message RAM
//!    - fDet - Determinant of the 3x3 matrix
//!  - CPU to CLA1 Message RAM
//!    - x - 3x3 input matrix
//!
//! \b Watch \b Variables \n
//! - fDet - Determinant of the 3x3 matrix
//
//###########################################################################
// $TI Release: F2837xS Support Library v180 $
// $Release Date: Fri Nov  6 16:27:58 CST 2015 $
// $Copyright: Copyright (C) 2014-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "cla_det_3by3_shared.h"

//*****************************************************************************
// defines
//*****************************************************************************

//CLA defines
#define WAITSTEP 	asm(" RPT #255 || NOP")

//*****************************************************************************
// globals
//*****************************************************************************
//Task 1 (C) Variables
// NOTE: Do not initialize the Message RAM variables globally, they will be reset
// during the message ram initialization phase in the CLA memory configuration routine
#ifdef __cplusplus
#pragma DATA_SECTION("CpuToCla1MsgRAM");
float x[M][N];
#pragma DATA_SECTION("Cla1ToCpuMsgRAM");
float fDet;

#else
#pragma DATA_SECTION(x,"CpuToCla1MsgRAM");
float x[M][N];
#pragma DATA_SECTION(fDet,"Cla1ToCpuMsgRAM");
float fDet;
#endif //__cplusplus
float z[BUFFER_SIZE];

//Task 2 (C) Variables

//Task 3 (C) Variables

//Task 4 (C) Variables

//Task 5 (C) Variables

//Task 6 (C) Variables

//Task 7 (C) Variables

//Task 8 (C) Variables

float z_expected[BUFFER_SIZE] = {
	0, 44, 88, 132, 176,
	220, 264, 308, 352,
	396, 440, 484, 528,
	572, 616, 660, 704,
	748, 792, 836, 880,
	924, 968, 1012, 1056,
	1100, 1144, 1188, 1232,
	1276, 1320, 1364
};


uint16_t pass=0;
uint16_t fail=0;

//*****************************************************************************
// function prototypes
//*****************************************************************************
void CLA_runTest(void);
void CLA_configClaMemory(void);
void CLA_initCpu1Cla1(void);

__interrupt void cla1Isr1();
__interrupt void cla1Isr2();
__interrupt void cla1Isr3();
__interrupt void cla1Isr4();
__interrupt void cla1Isr5();
__interrupt void cla1Isr6();
__interrupt void cla1Isr7();
__interrupt void cla1Isr8();

//*****************************************************************************
// Start of main
//*****************************************************************************
void main(void)
{
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xS_SysCtrl.c file.
    InitSysCtrl();

// Step 2. Clear all interrupts and initialize PIE vector table:
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

// Step 3. Configure the CLA memory spaces first followed by
// the CLA task vectors
    CLA_configClaMemory();
    CLA_initCpu1Cla1();

// Step 4. Enable global Interrupts and higher priority real-time debug events:
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

// Step 5. Run the test
    CLA_runTest();
}

//*****************************************************************************
// function definitions
//*****************************************************************************
void CLA_runTest(void)
{
	unsigned int  i, error;
	for(i=0;i<BUFFER_SIZE;i++){
		x[0][0] = (float)i+1;
		x[0][1] = (float)i+2;
		x[0][2] = (float)i+3;
		x[1][0] = (float)i-1;
		x[1][1] = (float)i-2;
		x[1][2] = (float)i-3;
		x[2][0] = (float)i-7;
		x[2][1] = (float)i+3;
		x[2][2] = (float)i-9;
	 Cla1ForceTask1andWait();
	 z[i] = fDet;
	 error = fabs(z_expected[i]-z[i]);
	 if (error < 0.0001)
	 {
		 pass++;
	 }
	 else
	 {
		 fail++;
	 }
	}

#if 0

    Cla1ForceTask2andWait();
    WAITSTEP;

    Cla1ForceTask3andWait();
    WAITSTEP;

    Cla1ForceTask4andWait();
    WAITSTEP;

    Cla1ForceTask5andWait();
    WAITSTEP;

    Cla1ForceTask6andWait();
    WAITSTEP;

    Cla1ForceTask7andWait();
    WAITSTEP;

    Cla1ForceTask8andWait();
    WAITSTEP;
#endif
}

void CLA_configClaMemory(void)
{
	extern uint32_t Cla1funcsRunStart, Cla1funcsLoadStart, Cla1funcsLoadSize;
	EALLOW;

#ifdef _FLASH
	// Copy over code from FLASH to RAM
	memcpy((uint32_t *)&Cla1funcsRunStart, (uint32_t *)&Cla1funcsLoadStart,
			(uint32_t)&Cla1funcsLoadSize);
#endif //_FLASH

	// Initialize and wait for CLA1ToCPUMsgRAM
	MemCfgRegs.MSGxINIT.bit.INIT_CLA1TOCPU = 1;
	while(MemCfgRegs.MSGxINITDONE.bit.INITDONE_CLA1TOCPU != 1){};

	// Initialize and wait for CPUToCLA1MsgRAM
	MemCfgRegs.MSGxINIT.bit.INIT_CPUTOCLA1 = 1;
	while(MemCfgRegs.MSGxINITDONE.bit.INITDONE_CPUTOCLA1 != 1){};

	// Select LS5RAM to be the programming space for the CLA
	// First configure the CLA to be the master for LS5 and then
	// set the space to be a program block
	MemCfgRegs.LSxMSEL.bit.MSEL_LS5 = 1;
	MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS5 = 1;

	//Next configure LS0RAM and LS1RAM as data spaces for the CLA
	// First configure the CLA to be the master for LS0(1) and then
    // set the spaces to be code blocks
	MemCfgRegs.LSxMSEL.bit.MSEL_LS0 = 1;
	MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS0 = 0;

	MemCfgRegs.LSxMSEL.bit.MSEL_LS1 = 1;
	MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS1 = 0;

	EDIS;
}

void CLA_initCpu1Cla1(void)
{
	// Compute all CLA task vectors
	// On Type-1 CLAs the MVECT registers accept full 16-bit task addresses as
	// opposed to offsets used on older Type-0 CLAs
	EALLOW;
	Cla1Regs.MVECT1 = (uint16_t)(&Cla1Task1);
	Cla1Regs.MVECT2 = (uint16_t)(&Cla1Task2);
	Cla1Regs.MVECT3 = (uint16_t)(&Cla1Task3);
	Cla1Regs.MVECT4 = (uint16_t)(&Cla1Task4);
	Cla1Regs.MVECT5 = (uint16_t)(&Cla1Task5);
	Cla1Regs.MVECT6 = (uint16_t)(&Cla1Task6);
	Cla1Regs.MVECT7 = (uint16_t)(&Cla1Task7);
	Cla1Regs.MVECT8 = (uint16_t)(&Cla1Task8);

	// Enable the IACK instruction to start a task on CLA in software
	// for all  8 CLA tasks. Also, globally enable all 8 tasks (or a
	// subset of tasks) by writing to their respective bits in the
	// MIER register
    Cla1Regs.MCTL.bit.IACKE = 1;
    Cla1Regs.MIER.all 	= 0x00FF;

    // Configure the vectors for the end-of-task interrupt for all
    // 8 tasks
	PieVectTable.CLA1_1_INT   = &cla1Isr1;
	PieVectTable.CLA1_2_INT   = &cla1Isr2;
	PieVectTable.CLA1_3_INT   = &cla1Isr3;
	PieVectTable.CLA1_4_INT   = &cla1Isr4;
	PieVectTable.CLA1_5_INT   = &cla1Isr5;
	PieVectTable.CLA1_6_INT   = &cla1Isr6;
	PieVectTable.CLA1_7_INT   = &cla1Isr7;
	PieVectTable.CLA1_8_INT   = &cla1Isr8;

	// Enable CLA interrupts at the group and subgroup levels
	PieCtrlRegs.PIEIER11.all  = 0xFFFF;
	IER |= (M_INT11 );
}

//*****************************************************************************
// ISR
//*****************************************************************************
__interrupt void cla1Isr1 ()
{
	// Acknowledge the end-of-task interrupt for task 1
	PieCtrlRegs.PIEACK.all = M_INT11;
//	asm(" ESTOP0");
}

__interrupt void cla1Isr2 ()
{
	asm(" ESTOP0");
}

__interrupt void cla1Isr3 ()
{
	asm(" ESTOP0");
}

__interrupt void cla1Isr4 ()
{
	asm(" ESTOP0");
}

__interrupt void cla1Isr5 ()
{
	asm(" ESTOP0");
}

__interrupt void cla1Isr6 ()
{
	asm(" ESTOP0");
}

__interrupt void cla1Isr7 ()
{
	asm(" ESTOP0");
}

__interrupt void cla1Isr8 ()
{
	// Acknowledge the end-of-task interrupt for task 8
	PieCtrlRegs.PIEACK.all = M_INT11;
//	asm(" ESTOP0");
}

// End of File
