/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 12/14/15     13.0_DW0a   Ported from
 * 							  "PIC_Catalyst_RPI_daughter_Speech_Recognition"
 *                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#ifndef USER_H
#define	USER_H

#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

/******************************************************************************/
/* Project Name                                                               */
/******************************************************************************/
#define PROJECT_NAME "Marley PetCam"

/******************************************************************************/
/* Firmware Version                                                           */
/******************************************************************************/
#define FIRMWARE_VERSION "13.0_DW0a"

/******************************************************************************/
/* Copywrite message                                                          */
/******************************************************************************/
#define COPYWRITE_MESSAGE "Copywrite Marley Circuits 2016. All rights reserved."

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/
#define ON 1
#define OFF 0
#define TRUE 1
#define FALSE 0
#define INPUT 1
#define OUTPUT 0
#define PASS 1
#define YES 1
#define NO 0
#define NONE NO

#define MAX_UCHAR 	255
#define MAX_CHAR 	128
#define MAX_UINT 	65535L
#define MAX_INT 	32767L
#define MAX_ULONG 	4294967295L
#define MAX_LONG 	2147483647L

/******************************************************************************/
/* Analog pins                                                                */
/******************************************************************************/
#define ADCINA0 0
#define ADCINB0 0

/******************************************************************************/
/* Macro functions                                                            */
/******************************************************************************/
#define NOP() __asm(" nop");
#define Nop()	NOP()

/******************************************************************************/
/* Pin Defines                                                                */
/******************************************************************************/

/************* LEDs *************/
/* Connected to the Red LED portion of the RED/GREEN LED */
#define RED_LED_GPIO 13 // GPIO13

/* Connected to the Green LED portion of the RED/GREEN LED */
#define GREEN_LED_GPIO 14 // GPIO14

/************* Zero_cross Optocoupler *************/
/* Connected to the optocoupler output from AC line */
#define ZEROCROSS_GPIO 12 // GPIO12

/************* IR Communications *************/
/* Connected to the MOSFET controllng the IR LED */
#define IR_LED_GPIO 15 // GPIO15

/* Connected to the output of the IR receiver */
#define IR_RECEIVER_GPIO 16 // GPIO16

/************* Relays *************/
/* Connected to the Solid State Relay */
#define SS_RELAY_GPIO 17 // GPIO17

/* Connected to the Mechanical Relay */
#define MECH_RELAY_GPIO 71 // GPIO71

/************* Pushbutton *************/
/* Connected to the pushbutton switch */
#define PUSHBUTTON_GPIO 20 // GPIO20

/************* Audio *************/
/* Connected to the output of the audio driver */
#define ADC_AUDIO_1_GPIO ADCINB0 // ADCINB0

/* Connected to the output of the audio driver */
#define ADC_AUDIO_2_GPIO ADCINA0 // ADCINA0

/************* UART over USB *************/
/* Connected to the input of the FTDI UART */
#define UART_TX_GPIO 84 // GPIO84 used as SCITXDA

/* Connected to the output of the FTDI UART */
#define UART_RX_GPIO 85 // GPIO85 used as SCITXDA

/******************************************************************************/
/* Version variables                                                          */
/******************************************************************************/

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void Init_Pins(void);
void Init_Modules(void);

#endif	/* USER_H */
