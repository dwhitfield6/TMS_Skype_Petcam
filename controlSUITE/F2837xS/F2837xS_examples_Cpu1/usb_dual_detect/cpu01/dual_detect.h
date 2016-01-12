//###########################################################################
//
// dual_detect.h - The dual example application common definitions.
//
//###########################################################################
// $TI Release: F2837xS Support Library v180 $
// $Release Date: Fri Nov  6 16:27:58 CST 2015 $
// $Copyright: Copyright (C) 2014-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef __OTG_DETECT_H__
#define __OTG_DETECT_H__

void HostInit(void);
void HostMain(void);
void DeviceInit(void);
void DeviceMain(void);
void UpdateStatus(char *pcString, unsigned long ulButtons, _Bool bClrGBg);
void ClearMainWindow(void);

//*****************************************************************************
//
// Debug-related definitions and declarations.
//
// Debug output is available via UART0 if DEBUG is defined during build.
//
//*****************************************************************************
#ifdef DEBUG
//*****************************************************************************
//
// Map all debug print calls to UARTprintf in debug builds.
//
//*****************************************************************************
#define DEBUG_PRINT UARTprintf

#else

//*****************************************************************************
//
// Compile out all debug print calls in release builds.
//
//*****************************************************************************
#define DEBUG_PRINT while(0) ((int (*)(char *, ...))0)
#endif

#endif
