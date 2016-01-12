#ifndef _CLA_SHELLSORT_SHARED_H_
#define _CLA_SHELLSORT_SHARED_H_
//#############################################################################
// FILE:   cla_shellsort_shared.h
// TITLE:  Shell Sort Test
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
#include "F2837xS_Cla_typedefs.h"
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
#define LENGTH1 (int32)((sizeof(vector1)/sizeof(vector1[0])))
extern float32 vector1[5];
extern float32 vector1_sorted[];

//Task 2 (C) Variables
#define LENGTH2 (int32)((sizeof(vector2)/sizeof(vector2[0])))
extern float32 vector2[10];
extern float32 vector2_sorted[];

//Task 3 (C) Variables
#define LENGTH3 (int32)((sizeof(vector3)/sizeof(vector2[0])))
extern int32   vector3[9];
extern int32   vector3_sorted[];

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

#endif //end of _CLA_SHELLSORT_SHARED_H_ definition
