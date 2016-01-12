#ifndef _CLA_ADC_FIR32_SHARED_H_
#define _CLA_ADC_FIR32_SHARED_H_
//#############################################################################
// FILE:   cla_adc_fir32_shared.h
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
#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "F2837xS_Cla_defines.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define FILTER_LEN    5

//*****************************************************************************
// typedefs
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************

//Task 1 (ASM) Variables
extern uint16_t voltFilt;
extern float  X[FILTER_LEN];
extern float  A[FILTER_LEN];

//Task 2 (ASM) Variables

//Task 3 (ASM) Variables

//Task 4 (ASM) Variables

//Task 5 (ASM) Variables

//Task 6 (ASM) Variables

//Task 7 (ASM) Variables

//Task 8 (ASM) Variables

//Common (ASM) Variables

//*****************************************************************************
// function prototypes
//*****************************************************************************
// The following are symbols defined in the CLA assembly code
// Including them in the shared header file makes them
// .global and the main CPU can make use of them.

//CLA ASM Tasks
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

#endif //end of _CLA_ADC_FIR32_SHARED_H_ definition
