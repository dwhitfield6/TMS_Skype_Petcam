//###########################################################################
// FILE:   tmu_sinegen_cpu01.c
// TITLE:  TMU Sine Generation Example for F2837xS.
//
//! \addtogroup cpu01_example_list
//! <h1> Profiling \f$sine(x)\f$ using the TMU (tmu_sinegen)</h1>
//!
//! In this example, we will use TMU intrinsics to calculate
//! the sine for a series of per-unit arguments (the argument is not represented
//! in radians, it is normalized to the range -1.0 to 1.0). We will profile
//! the execution time of the TMU versus the conventional implementation
//! in the run-time support library
//!
//! \f$ \forall x \in [-2\pi, 2\pi], x_{pu} = \frac{x}{2\pi}\f$
//! \f$ y = sin(x_{pu} * 2\pi) \f$
//!
//! Instead of using intrinsics, the compiler can implement most of the
//! RTS trigonometric functions through TMU instructions if the option
//! \e fp_mode is set to \e relaxed. In this example, this option is left
//! untouched; it defaults to the \e strict mode.
//!
//! \b Watch \b Variables \n
//!    - timeRTS - time to run RTS routine
//!    - timeTMU - time to run TMU routine
//
//
//###########################################################################
// $TI Release: F2837xS Support Library v180 $
// $Release Date: Fri Nov  6 16:27:58 CST 2015 $
// $Copyright: Copyright (C) 2014-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include <math.h>
#include <stdio.h>
#include "F28x_Project.h"     // Device Headerfile and Examples Include File

//*****************************************************************************
// defines
//*****************************************************************************
#define 	VECTOR_SIZE		1024
#define 	MAX_ARG			1.0
#define		MIN_ARG			-1.0
#define	 	PROFILE_FREQ	200		//Specified in MHz
#define		PROFILE_PER		1000	//Specified in microseconds
#define		TWO_PI			6.283185307179586476925286766559
#define		TOLERANCE		1.0e-6
//*****************************************************************************
// macros
//*****************************************************************************
#define		START_TIMER(x) {							     \
							  x = CpuTimer1Regs.TIM.all;     \
							  CpuTimer1Regs.TCR.bit.TSS = 0; \
                            }

#define		STOP_TIMER(x)	{                                \
							  CpuTimer1Regs.TCR.bit.TSS = 1; \
							  x = CpuTimer1Regs.TIM.all;     \
  							  CpuTimer1Regs.TCR.bit.TRB = 1; \
                            }
//*****************************************************************************
// globals
//*****************************************************************************
uint16_t pass=0;
uint16_t fail=0;
float inputVector[VECTOR_SIZE];
float rtsOutput[VECTOR_SIZE];
float tmuOutput[VECTOR_SIZE];
float errorVector[VECTOR_SIZE];

float ticksRTS, ticksTMU, timeRTS, timeTMU;
float maxError;
//*****************************************************************************
// function prototypes
//*****************************************************************************
void genInputVector(float *inputVector, int16_t size);
float genErrorVector(float *rtsOutput, float *tmuOutput,
		float *errorVector, int16_t size);
float RTS_runTest(float *inputVector,float *rtsOutput,
		int16_t size);
float TMU_runTest(float *inputVector,float *tmuOutput,
		int16_t size);

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

// Step 3. Configure the timer used to profile the TMU and RTS routines
    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer1, PROFILE_FREQ, PROFILE_PER);

// Step 4. Enable global Interrupts and higher priority real-time debug events:
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

// Step 5. Run the test, generate the input vector, call the RTS/TMU
//    routines, get the error vector and, finally, print the execution time.
    genInputVector(inputVector, VECTOR_SIZE);
    ticksRTS = RTS_runTest(inputVector, rtsOutput, VECTOR_SIZE);
    ticksTMU = TMU_runTest(inputVector, tmuOutput, VECTOR_SIZE);
    maxError = genErrorVector(rtsOutput, tmuOutput, errorVector, VECTOR_SIZE);
    timeRTS = ticksRTS * (1.0/PROFILE_FREQ);
    timeTMU = ticksTMU * (1.0/PROFILE_FREQ);
// To use the printf statement, allocate space for the .cio, .sysmem section,
// increase allotment for the .text, stack and heap sections in the properties
// and linker command file.
    printf("Execution Results \n");
    printf("RTS Time : %10.6f us\n", timeRTS);
    printf("TMU Time : %10.6f us\n", timeTMU);
}

//*****************************************************************************
// function definitions
//*****************************************************************************
void genInputVector(float *inputVector, int16_t size)
{
	int16_t i;
	float step = (MAX_ARG - MIN_ARG)/size;

	inputVector[0] = MIN_ARG;
	for(i = 1; i < size ; i++){
		inputVector[i] = inputVector[i-1] + step;
	}
}

float genErrorVector(float *rtsOutput, float *tmuOutput,
		float *errorVector, int16_t size)
{
	int16_t i;
	float maxError = -1.0;
	for(i = 0; i < size ; i++){
		errorVector[i] = fabs(rtsOutput[i] - tmuOutput[i]);
		if(errorVector[i] > maxError){
			maxError = errorVector[i];
		}
		if(errorVector[i] < TOLERANCE){
			pass++;
		}else{
			fail++;
		}
	}

	return(maxError);
}

float RTS_runTest(float *inputVector,float *rtsOutput,
		int16_t size)
{
	int16_t i;
	float start_time = 0.0;
	float stop_time = 0.0;

	START_TIMER(start_time);
	for(i = 0; i < size ; i++){
		rtsOutput[i] = sin(inputVector[i] * TWO_PI);
	}
	STOP_TIMER(stop_time);

	return(start_time - stop_time);
}

float TMU_runTest(float *inputVector,float *tmuOutput,
		int16_t size)
{
	int16_t i;
	float start_time = 0.0;
	float stop_time = 0.0;

	START_TIMER(start_time);
	for(i = 0; i < size ; i++){
		tmuOutput[i] = __sinpuf32(inputVector[i]);
	}
	STOP_TIMER(stop_time);

	return(start_time - stop_time);
}

//*****************************************************************************
// ISR
//*****************************************************************************


// End of File
