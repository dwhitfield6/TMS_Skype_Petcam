//###########################################################################
//
// FILE:    Shared_Erase.h
//
// TITLE:   Erase shared functions
//
// Functions:
//
//     void SCI_Erase(Uint16 command, Uint32 sectors)
//
//###########################################################################
// $TI Release: F2837xS Support Library v180 $
// $Release Date: Fri Nov  6 16:27:58 CST 2015 $
// $Copyright: Copyright (C) 2014-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef __SHARED_ERASE_H__
#define __SHARED_ERASE_H__

#include "c1_bootrom.h"
#include "F021_F2837xD_C28x.h"
//Include Flash API example header file
#include "flash_programming_c28.h"

void SCI_Erase(Uint32 sectors);

#endif
