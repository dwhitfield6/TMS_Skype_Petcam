//###########################################################################
//
// usbdescriptors.h - The usb descriptor information for this project.
//
//###########################################################################
// $TI Release: F2837xS Support Library v180 $
// $Release Date: Fri Nov  6 16:27:58 CST 2015 $
// $Copyright: Copyright (C) 2014-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef __USBDESCRIPTORS_H__
#define __USBDESCRIPTORS_H__

//*****************************************************************************
//
// Pre-declarations of the handlers.
//
//*****************************************************************************
extern void HandleHIDDescriptor(unsigned long ulIndex,
                                tUSBRequest *pUSBRequest);
extern void HandleRequests(unsigned long ulIndex, tUSBRequest *pUSBRequest);
extern void ConfigurationChange(unsigned long ulIndex, unsigned long ulInfo);
extern void EP1Handler(unsigned long ulIndex, unsigned long ulStatus);
extern void HandleReset(unsigned long ulIndex);
extern void HandleDisconnect(unsigned long ulIndex);

extern unsigned long const g_ulReportDescriptorSize;
extern unsigned char const g_pucReportDescriptor[];
extern tDeviceInfo g_sMouseDeviceInfo;

#endif // __USBDESCRIPTORS_H__
