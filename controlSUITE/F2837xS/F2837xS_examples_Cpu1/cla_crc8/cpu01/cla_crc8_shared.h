#ifndef _CLA_CRC8_SHARED_H_
#define _CLA_CRC8_SHARED_H_
//#############################################################################
// FILE:   cla_crc8_shared.h
// TITLE:  CLA 8-bit CRC example header file.
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
extern const uint16_t table[256];
extern uint16_t msg1[];
extern uint16_t msg2[];
extern uint16_t msg3[];
extern uint16_t msg4[];
extern uint16_t crc8_msg1;
extern uint16_t crc8_msg2;
extern uint16_t crc8_msg3;
extern uint16_t crc8_msg4;

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

#endif //end of _CLA_CRC8_SHARED_H_ definition
