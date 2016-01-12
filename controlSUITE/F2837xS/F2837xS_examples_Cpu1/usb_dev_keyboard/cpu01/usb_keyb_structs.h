//###########################################################################
//
// usb_keyb_structs.h - Data structures defining the keyboard USB device.
//
//###########################################################################
// $TI Release: F2837xS Support Library v180 $
// $Release Date: Fri Nov  6 16:27:58 CST 2015 $
// $Copyright: Copyright (C) 2014-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef _USB_KEYB_STRUCTS_H_
#define _USB_KEYB_STRUCTS_H_

extern uint32_t KeyboardHandler(void *pvCBData,
                                     uint32_t ui32Event,
                                     uint32_t ui32MsgData,
                                     void *pvMsgData);

extern tUSBDHIDKeyboardDevice g_sKeyboardDevice;

#endif
