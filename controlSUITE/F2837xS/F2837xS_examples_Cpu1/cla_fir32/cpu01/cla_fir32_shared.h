#ifndef _CLA_FIR32_SHARED_H_
#define _CLA_FIR32_SHARED_H_
//#############################################################################
// FILE:   cla_fir32_shared.h
// TITLE:  CLA 5 Tap FIR filter
//
//  Group: 			C2000
//  Target Family:	F2837xS
//
//#############################################################################
// $TI Release: F2837xS Support Library v180 $
// $Release Date: Fri Nov  6 16:27:58 CST 2015 $
// $Copyright: Copyright (C) 2014-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "F2837xS_Cla_defines.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************

//*****************************************************************************
// typedefs
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************

//Task 1 (C) Variables
#define NUM_SAMPLES	128
#define FILTER_LEN    5
#define INPUT_LEN     128
#define OUTPUT_LEN    INPUT_LEN+FILTER_LEN

extern float fCoeffs[];
extern long xAdcInput;
extern long xResult;
extern float fDelayLine[];
extern unsigned long fir_output[];
extern unsigned long adc_input[];

//Task 2 (C) Variables

//Task 3 (C) Variables

//Task 4 (C) Variables

//Task 5 (C) Variables

//Task 6 (C) Variables

//Task 7 (C) Variables

//Task 8 (C) Variables

//Common (C) Variables

//*****************************************************************************
// function prototypes
//*****************************************************************************
// The following are symbols defined in the CLA assembly code
// Including them in the shared header file makes them
// .global and the main CPU can make use of them.

//CLA C Tasks
__interrupt void Cla1Task1();
__interrupt void Cla1Task2();
__interrupt void Cla1Task3();
__interrupt void Cla1Task4();
__interrupt void Cla1Task5();
__interrupt void Cla1Task6();
__interrupt void Cla1Task7();
__interrupt void Cla1Task8();

#ifdef __cplusplus
}
#endif // extern "C"

#endif //end of _CLA_FIR32_SHARED_H_ definition
