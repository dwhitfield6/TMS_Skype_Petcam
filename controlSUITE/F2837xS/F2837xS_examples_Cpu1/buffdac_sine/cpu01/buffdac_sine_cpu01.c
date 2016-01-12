//###########################################################################
// FILE:   buffdac_sine_cpu01.c
// TITLE:  Buffered DAC Sine Wave Output Example for F2837xS.
//
//! \addtogroup cpu01_example_list
//! <h1> Buffered DAC Sine (buffdac_sine) </h1>
//!
//! This example generates a sine wave on the buffered DAC output,
//! DACOUTA/ADCINA0 (HSEC Pin 9) and uses the default DAC reference setting of VDAC.
//!
//! When the DAC reference is set to VDAC, an external reference voltage
//! must be applied to the VDAC pin. This can accomplished by connecting a
//! jumper wire from 3.3V to ADCINB0 (HSEC pin 12).
//!
//! Run the included .js file to add the watch variables.
//! This example uses the SGEN module. Documentation for the SGEN module can be
//! found in controlSUITE/libs/dsp/SGEN/101/doc
//!
//! The generated waveform can be adjusted with the following variables while running:
//! - \b waveformGain \b : Adjust the magnitude of the waveform.
//! Range is from 0.0 to 1.0. The default value of 0.8003 centers the waveform
//! within the linear range of the DAC
//! - \b waveformOffset \b : Adjust the offset of the waveform.
//!	Range is from -1.0 to 1.0. The default value of 0 centers the waveform
//! - \b outputFreq_hz \b : Adjust the output frequency of the waveform.
//! Range is from 0 to maxOutputFreq_hz
//! - \b maxOutputFreq_hz \b : Adjust the max output frequency of the waveform.
//! Range - See SGEN module documentation for how this affects other parameters
//!
//! The generated waveform can be adjusted with the following variables/macros but require recompile:
//! - \b samplingFreq_hz \b : Adjust the rate at which the DAC is updated.
//! Range - See SGEN module documentation for how this affects other parameters
//! - \b SINEWAVE_TYPE \b : The type of sine generated.
//! Range - LOW_THD_SINE, HIGH_PRECISION_SINE
//! - \b REFERENCE \b : The reference for the DAC.
//! Range - REFERENCE_VDAC, REFERENCE_VREF
//! - \b CPUFREQ_MHZ \b : The cpu frequency. This does not set the cpu frequency.
//! Range - See device data manual
//! - \b DAC_NUM \b : The DAC to use.
//! Range - DACA, DACB, DACC
//!
//! The following variables give additional information about the generated waveform:
//! See SGEN module documentation for details
//! - \b freqResolution_hz \b
//! - \b maxOutput_lsb \b : Maximum value written to the DAC.
//! - \b minOutput_lsb \b : Minimum value written to the DAC.
//! - \b pk_to_pk_lsb \b : Magnitude of generated waveform.
//! - \b cpuPeriod_us \b : Period of cpu.
//! - \b samplingPeriod_us \b : The rate at which the DAC is updated.
//! Note that samplingPeriod_us has to be greater than the DAC settling time.
//! - \b interruptCycles \b : Interrupt duration in cycles.
//! - \b interruptDuration_us \b : Interrupt duration in uS.
//! - \b sgen \b : The SGEN module instance.
//! - \b DataLog \b : Circular log of writes to the DAC.
//!
//
//###########################################################################
// $TI Release: F2837xS Support Library v180 $
// $Release Date: Fri Nov  6 16:27:58 CST 2015 $
// $Copyright: Copyright (C) 2014-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "sgen.h"			  // Signal Generation Headerfile

//datalog
#define DLOG_SIZE			1024
Uint16 DataLog[DLOG_SIZE];
#pragma DATA_SECTION(DataLog, "DLOG");

//initialize DAC pointer
volatile struct DAC_REGS* DAC_PTR[4] = {0x0,&DacaRegs,&DacbRegs,&DaccRegs};

//definitions for selecting DAC reference
#define REFERENCE_VDAC		0
#define REFERENCE_VREF		1

//definitions for sine wave types
#define LOW_THD_SINE		0
#define HIGH_PRECISION_SINE	1

//definitions for DAC number
#define DACA				1
#define DACB				2
#define DACC				3

//specify configuration
#define SINEWAVE_TYPE		LOW_THD_SINE
#define REFERENCE			REFERENCE_VDAC
#define CPUFREQ_MHZ			200
#define DAC_NUM				DACA
Uint32 samplingFreq_hz = 200000;
Uint32 outputFreq_hz = 1000;
Uint32 maxOutputFreq_hz = 5000;
float waveformGain = 0.8003; // Range 0.0 -> 1.0
float waveformOffset = 0; // Range -1.0 -> 1.0

//initialize sine wave type
#if SINEWAVE_TYPE==LOW_THD_SINE
SGENTI_1 sgen = SGENTI_1_DEFAULTS;
#elif SINEWAVE_TYPE==HIGH_PRECISION_SINE
SGENHP_1 sgen = SGENHP_1_DEFAULTS;
#endif

//local functions
static inline void dlog(Uint16 value);
static inline void setFreq(void);
static inline void setGain(void);
static inline void setOffset(void);
static inline Uint16 getMax(void);
static inline Uint16 getMin(void);
void configureDAC(Uint16 dac_num);
void configureWaveform(void);
interrupt void cpu_timer0_isr(void);

//status variables
Uint16 sgen_out = 0;
Uint16 ndx = 0;
float freqResolution_hz = 0;
float cpuPeriod_us = 0;
Uint32 interruptCycles = 0;
float interruptDuration_us = 0;
float samplingPeriod_us = 0;
Uint16 maxOutput_lsb = 0;
Uint16 minOutput_lsb = 0;
Uint16 pk_to_pk_lsb = 0;

void main(void)
{
// Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xS_SysCtrl.c file.
    InitSysCtrl();

// Disable CPU interrupts
    DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags are cleared.
// This function is found in the F2837xS_PieCtrl.c file.
    InitPieCtrl();

// Clear all interrupts and initialize PIE vector table:
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

// Map Cpu Timer0 interrupt function to the PIE vector table
    EALLOW;
    PieVectTable.TIMER0_INT = &cpu_timer0_isr;
    EDIS;

// Initialize variables
    cpuPeriod_us = (1.0/CPUFREQ_MHZ);
    samplingPeriod_us = (1000000.0/samplingFreq_hz);

// Initialize datalog
    for(ndx=0; ndx<DLOG_SIZE; ndx++) DataLog[ndx] = 0;
    ndx = 0;

// Configure DAC
    configureDAC(DAC_NUM);

// Configure Waveform
    configureWaveform();

// Initialize Cpu Timers
    InitCpuTimers();

// Configure Cpu Timer0 to interrupt at specified sampling frequency
    ConfigCpuTimer(&CpuTimer0, CPUFREQ_MHZ, 1000000.0/samplingFreq_hz);

// Start Cpu Timer0
    CpuTimer0Regs.TCR.all = 0x4000;

// Enable interrupt
    IER |= M_INT1;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
    EINT;
    ERTM;

    while(1)
    {
    	setFreq(); // Set Output Frequency and Max Output Frequency
    	setGain(); // Set Magnitude of Waveform
    	setOffset(); // Set Offset of Waveform
    	maxOutput_lsb = getMax();
    	minOutput_lsb = getMin();
    	pk_to_pk_lsb = maxOutput_lsb - minOutput_lsb;
    }
}

// Circular DataLog. DataLog[0] contains the next index to be overwritten
static inline void dlog(Uint16 value)
{
	DataLog[ndx] = value;
	if(++ndx==DLOG_SIZE) ndx = 0;
	DataLog[0] = ndx;
}

static inline void setFreq(void)
{
#if SINEWAVE_TYPE==LOW_THD_SINE
    sgen.step_max = (maxOutputFreq_hz*0x10000)/samplingFreq_hz; // Range(Q0) = 0x0000 -> 0x7FFF, step_max(Q0) = (Max_Freq_hz*0x10000)/Sampling_Freq_hz

    sgen.freq = ((float)outputFreq_hz/maxOutputFreq_hz)*0x8000; // Range(Q15) = 0x0000 -> 0x7FFF, freq(Q15) = (Required_Freq_hz/Max_Freq_hz)*0x8000
#elif SINEWAVE_TYPE==HIGH_PRECISION_SINE
    sgen.step_max = (maxOutputFreq_hz*0x100000000)/samplingFreq_hz; // Range(Q0) = 0x00000000 -> 0x7FFFFFFF, step_max(Q0) = (Max_Freq_hz*0x100000000)/Sampling_Freq_hz

    sgen.freq = ((float)outputFreq_hz/maxOutputFreq_hz)*0x80000000; // Range(Q31) = 0x00000000 -> 0x7FFFFFFF, freq(Q31) = (Required_Freq_hz/Max_Freq_hz)*0x80000000
#endif

    freqResolution_hz = (float)maxOutputFreq_hz/sgen.step_max;
}

static inline void setGain(void)
{
	sgen.gain = waveformGain * 0x7FFF; // Range(Q15) = 0x0000 -> 0x7FFF
}

static inline void setOffset(void)
{
	sgen.offset = waveformOffset * 0x7FFF; // Range(Q15) = 0x8000 -> 0x7FFF
}

static inline Uint16 getMax(void)
{
	Uint16 index = 0;
	Uint16 tempMax = 0;
	for(index=1;index<DLOG_SIZE;index++)
	{
		if(tempMax<DataLog[index]) tempMax = DataLog[index];
	}
	return tempMax;
}

static inline Uint16 getMin(void)
{
	Uint16 index = 0;
	Uint16 tempMin = 0xFFFF;
	for(index=1;index<DLOG_SIZE;index++)
	{
		if(tempMin>DataLog[index]) tempMin = DataLog[index];
	}
	return tempMin;
}

void configureDAC(Uint16 dac_num)
{
	EALLOW;
	DAC_PTR[dac_num]->DACCTL.bit.DACREFSEL = REFERENCE;
	DAC_PTR[dac_num]->DACOUTEN.bit.DACOUTEN = 1;
	DAC_PTR[dac_num]->DACVALS.all = 0;
	DELAY_US(10); // Delay for buffered DAC to power up
	EDIS;
}

void configureWaveform(void)
{
    sgen.alpha = 0; // Range(16) = 0x0000 -> 0xFFFF
    setFreq();
    setGain();
    setOffset();
}

interrupt void cpu_timer0_isr(void)
{
    CpuTimer1Regs.TCR.all = 0x0000; // Start Cpu Timer1 to indicate begin of interrupt
	DAC_PTR[DAC_NUM]->DACVALS.all = sgen_out; // Write current sine value to buffered DAC
	dlog(sgen_out); // Log current sine value

	sgen.calc(&sgen); // Compute next sine value
	sgen_out = (sgen.out+32768)>>4; // Scale next sine value

    // Acknowledge this interrupt to receive more interrupts from group 1
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    CpuTimer1Regs.TCR.all = 0x0010; // Stop Cpu Timer1 to indicate end of interrupt
    interruptCycles = 0xFFFFFFFFUL - CpuTimer1Regs.TIM.all; // Calculate interrupt duration in cycles
    interruptDuration_us = cpuPeriod_us * interruptCycles; // Calculate interrupt duration in micro seconds
    CpuTimer1Regs.TCR.all = 0x0030; // Reload Cpu Timer1
}
