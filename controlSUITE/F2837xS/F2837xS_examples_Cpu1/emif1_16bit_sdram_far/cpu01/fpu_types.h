//###########################################################################
//
// FILE:   fpu_types.h
//
// TITLE:  Prototypes and Definitions for the C28x FPU Library
//
//###########################################################################
// $TI Release: F2837xS Support Library v180 $
// $Release Date: Fri Nov  6 16:27:58 CST 2015 $
// $Copyright: Copyright (C) 2014-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef _FPU_TYPES_H_
#define _FPU_TYPES_H_

#include <stdint.h>
#include "float.h"

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Type Definitions
//-----------------------------------------------------------------------------
#ifndef FPU_TYPES
#define FPU_TYPES

// Complex Float Data Type
typedef struct {
    float dat[2];
} complex_float;

#endif //FPU_TYPES

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of _FPU_TYPES_H_

//===========================================================================
// End of file.
//===========================================================================

