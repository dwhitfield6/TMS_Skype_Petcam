//###########################################################################
// FILE:   emif1_16bit_sdram_dma.c
// TITLE:  EMIF1 module accessing 32bit SDRAM using the DMA.
//
//! \addtogroup cpu01_example_list
//! <h1> EMIF1 SDRAM Module (emif1_16bit_sdram_dma)</h1>
//!
//! This example configures EMIF1 in 16bit SDRAM mode and uses
//! CS0 (SDRAM) as chip enable. It will first write to an array
//! in the SDRAM and then read it back using the DMA for both
//! operations.
//! The buffer in SDRAM will be placed in the .farbss memory on
//! account of the fact that its assigned the attribute "far"
//! indicating it lies beyond the 22-bit program address space.
//! The compiler will take care to avoid using instructions such
//! as PREAD, which uses the Program Read Bus, or addressing
//! modes restricted to the lower 22-bit space when accessing
//! data with the attribute "far"
//! \note The memory space beyond 22-bits must be treated as data space
//! for load/store operations only. The user is cautioned against using
//! this space for either instructions or working memory.
//!
//! Example has been tested using Micron 48LC32M16A2 "P -75 C" part.
//!
//! \b Watch \b Variables: \n
//! - \b TEST_STATUS - Equivalent to \b TEST_PASS if test finished correctly,
//!                    else the value is set to \b TEST_FAIL
//! - \b ErrCount - Error counter
//!
//
//
//###########################################################################
// $TI Release: F2837xS Support Library v180 $
// $Release Date: Fri Nov  6 16:27:58 CST 2015 $
// $Copyright: Copyright (C) 2014-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "F28x_Project.h"     // Device Headerfile and Examples Include File

#define TEST_PASS 0xABCDABCD
#define TEST_FAIL 0xDEADDEAD

#define SDRAM_CS0_START_ADDR 0x80000000
#define SDRAM_CS0_SIZE 		 0x300000

#define MEM_BUFFER_SIZE         1024 // 32-Bit Word

Uint32 g_ulSrcBuf0[MEM_BUFFER_SIZE];
Uint32 g_ulDstBuf1[MEM_BUFFER_SIZE];
__attribute__((far)) volatile Uint32 g_ulSDRAMBuf[MEM_BUFFER_SIZE]; //Buffer in far memory

#pragma DATA_SECTION(g_ulSrcBuf0, "ramgs0");
#pragma DATA_SECTION(g_ulDstBuf1, "ramgs1");

//interrupt void local_DMA_CH1_ISR(void);

volatile Uint32 InitData = 0;
volatile Uint32 *DMADest;
volatile Uint32 *DMASource;

extern void setup_emif1_pinmux_sdram_16bit(Uint16);

//##########EMIF1-16bit SDRAM DMA test ######################

Uint16  ErrCount = 0;
Uint32  TEST_STATUS;

void DMA_DstDataClear() {
	int i;

    for(i = 0; i < MEM_BUFFER_SIZE; i++)
    {
    	__addr32_write_uint32(((Uint32)g_ulSDRAMBuf + (i*2)), 0x0);
    }

    for(i = 0; i < MEM_BUFFER_SIZE; i++)
    {
        g_ulDstBuf1[i] = 0x0;
    }
}

void main(void)
{
	int i;
	TEST_STATUS = TEST_FAIL;

	InitSysCtrl();

	DINT;

	//  Initialize the PIE control registers to their default state.
	//  The default state is all PIE interrupts disabled and flags
	//  are cleared.
	//  This function is found in the F2837xS_PieCtrl.c file.
	InitPieCtrl();

	// Disable CPU interrupts and clear all CPU interrupt flags:
	EALLOW;
	IER = 0x0000;
	IFR = 0x0000;
	EDIS;
	
	// Initialize the PIE vector table with pointers to the shell Interrupt
	// GService Routines (ISR).
	// This will populate the entire table, even if the interrupt
	// is not used in this example.  This is useful for debug purposes.
	// The shell ISR routines are found in F2837xS_DefaultIsr.c.
	// This function is found in F2837xS_PieVect.c.
	InitPieVectTable();

	EALLOW;
	EINT;
	EDIS;

	//Configure to run EMIF1 on half Rate (EMIF1CLK = CPU1SYSCLK/2)
	EALLOW;
	ClkCfgRegs.PERCLKDIVSEL.bit.EMIF1CLKDIV = 0x1;
	EDIS;

	EALLOW;

	//Disable Access Protection (CPU_FETCH/CPU_WR/DMA_WR)
	Emif1ConfigRegs.EMIF1ACCPROT0.all = 0x0;
	if (Emif1ConfigRegs.EMIF1ACCPROT0.all != 0x0)
	{
	  ErrCount++;
	}

	// Commit the configuration related to protection. Till this bit remains set
	// content of EMIF1ACCPROT0 register can't be changed.
	Emif1ConfigRegs.EMIF1COMMIT.all = 0x1;
	if(Emif1ConfigRegs.EMIF1COMMIT.all != 0x1)
	{
	 ErrCount++;
	}

	// Lock the configuration so that EMIF1COMMIT register can't be changed any more.
	Emif1ConfigRegs.EMIF1LOCK.all = 0x1;
	if (Emif1ConfigRegs.EMIF1LOCK.all != 1)
	{
	  ErrCount++;
	}

	EDIS;

	// Initialize source buffer for DMA transfer.
	InitData = 0x12103456;
	for(i = 0; i < MEM_BUFFER_SIZE; i++)
	{
		InitData = InitData + 0x11111111;
		g_ulSrcBuf0[i] = InitData;
	}

	// Initialize DMA
	DMAInitialize();

	// Configure DMA Channel 1 (16-bit datasize)
	DMADest   = g_ulSDRAMBuf;
	DMASource = (volatile Uint32 *)g_ulSrcBuf0;
	DMACH1AddrConfig32bit(DMADest,DMASource);
	DMACH1BurstConfig(31,1,1);         //Will set up to use 16-bit datasize, pointers are based on 16-bit words
	DMACH1TransferConfig(((MEM_BUFFER_SIZE*2/32) -1),1,1);      //so need to increment by 2 to grab the correct location
	DMACH1WrapConfig(0xFFFF,0,0xFFFF,0);
	//Since this is a static copy use one shot mode, so only one trigger is needed
	//Also using 16-bit mode
	DMACH1ModeConfig(0x0,PERINT_ENABLE,ONESHOT_ENABLE,CONT_DISABLE,SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,SIXTEEN_BIT,CHINT_END,CHINT_ENABLE);

	// Configure DMA Channel 2 (32-bit datasize)
	DMADest   = (volatile Uint32 *)g_ulDstBuf1;
	DMASource = g_ulSDRAMBuf;
	DMACH2AddrConfig32bit(DMADest,DMASource);
	DMACH2BurstConfig(31,2,2);         //Will set up to use 32-bit datasize, pointers are based on 32-bit words
	DMACH2TransferConfig(((MEM_BUFFER_SIZE*2/32) -1),2,2);      //so need to increment by 1 to grab the correct location
	DMACH2WrapConfig(0xFFFF,0,0xFFFF,0);
	//Since this is a static copy use one shot mode, so only one trigger is needed
	//Also using 32-bit mode
	DMACH2ModeConfig(0x0,PERINT_ENABLE,ONESHOT_ENABLE,CONT_DISABLE,SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,THIRTYTWO_BIT,CHINT_END,CHINT_ENABLE);

	StartDMACH1();
	StartDMACH2();

	//Configure GPIO pins for EMIF1
	setup_emif1_pinmux_sdram_16bit(0);

	/////////////////////////////////////
	//Configure SDRAM control registers//
	/////////////////////////////////////

	// Need to be programmed based on SDRAM Data-Sheet.
	//T_RFC = 60ns = 0x6
	//T_RP  = 18ns = 0x1
	//T_RCD = 18ns = 0x1
	//T_WR  = 1CLK + 6 ns = 0x1
	//T_RAS = 42ns = 0x4
	//T_RC  = 60ns = 0x6
	//T_RRD = 12ns = 0x1
	Emif1Regs.SDRAM_TR.all = 0x31114610;

	//Txsr = 70ns = 0x7
	Emif1Regs.SDR_EXT_TMNG.all = 0x7;

	//Tref = 64ms for 8192 ROW, RR = 64000*100(Tfrq)/8192 = 781.25 (0x30E)
	Emif1Regs.SDRAM_RCR.all = 0x30E;
    
	//PAGESIZE=2 (1024 elements per ROW), IBANK = 2 (4 BANK), CL = 3, NM = 1 (16bit)
	Emif1Regs.SDRAM_CR.all = 0x00015622;

	//Add some delay
	for(i=0;i<123;i++) { }

	// Clear the Data from DMA Destination Address
	DMA_DstDataClear();

	//WRITE TO EXT MEM (16-bit)
	EALLOW;
	DmaRegs.CH1.CONTROL.bit.PERINTFRC = 1;
	while (DmaRegs.CH1.CONTROL.bit.TRANSFERSTS != 1){};
	while (DmaRegs.CH1.CONTROL.bit.TRANSFERSTS != 0){};
	EDIS;

	// READ FROM EXT MEM (32-bit)
	EALLOW;
	DmaRegs.CH2.CONTROL.bit.PERINTFRC = 1;
	while (DmaRegs.CH2.CONTROL.bit.TRANSFERSTS != 1){};
	while (DmaRegs.CH2.CONTROL.bit.TRANSFERSTS != 0){};
	EDIS;

	//Compare the Data
    for (i = 0 ; i< MEM_BUFFER_SIZE ; i++)
    {
    	if (g_ulSrcBuf0[i] != g_ulDstBuf1[i])
    	{
    		ErrCount++;
    	}
    }

	if (ErrCount == 0x0)
	{
		TEST_STATUS = TEST_PASS;
	}

	while (1);
}

