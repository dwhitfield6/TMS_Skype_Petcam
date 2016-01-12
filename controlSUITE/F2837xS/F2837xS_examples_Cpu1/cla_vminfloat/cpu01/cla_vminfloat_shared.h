#ifndef _CLA_VMINFLOAT_SHARED_H_
#define _CLA_VMINFLOAT_SHARED_H_
//#############################################################################
// FILE:   cla_vminfloat_shared.h
// TITLE:  Vector Minimum
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
#include "F2837xS_Cla_typedefs.h"
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
extern int32 index1;
extern int32 length1;
extern float32 min1;
extern float32 vector1[];

//Task 2 (C) Variables
extern int32 index2;
extern int32 length2;
extern float32 min2;
extern float32 vector2[];

//Task 3 (C) Variables
extern int32 index3;
extern int32 length3;
extern float32 min3;
extern float32 vector3[];

//Task 4 (C) Variables

//Task 5 (C) Variables

//Task 6 (C) Variables

//Task 7 (C) Variables

//Task 8 (C) Variables

//Common (C) Variables
extern int32 i;

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

#endif //end of _CLA_VMINFLOAT_SHARED_H_ definition
