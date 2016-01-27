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
#define ADCINA1 1
#define ADCINB0 0
#define ADCINB1 1

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
/* Connected to the MOSFET controlling the IR LED */
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
#define PUSHBUTTON_GPIO 21 // GPIO21

/************* Audio *************/
/* Connected to the output of the audio driver */
#define ADC_AUDIO_1_GPIO ADCINA0 // ADCINA0

/* Connected to the output of the audio driver */
#define ADC_AUDIO_2_GPIO ADCINB0 // ADCINB0

/************* UART over USB *************/
/* Connected to the input of the FTDI UART */
#define UART_TX_GPIO 84 // GPIO84 used as SCITXDA

/* Connected to the output of the FTDI UART */
#define UART_RX_GPIO 85 // GPIO85 used as SCITXDA

/************* UART over BLUETOOTH *************/
/* Connected to the input of the HC05 IC */
#define BLUETOOTH_TX_GPIO 89 // GPIO89 used as SCITXDC

/* Connected to the output of the HC05 IC */
#define BLUETOOTH_RX_GPIO 90 // GPIO90 used as SCITXDC

/************* LowPass filter IC *************/
/* Connected to the shutdown pin of the MAX740x IC */
#define LOWPASS_SHDN_GPIO 41 // GPI041

/* Connected to the clock pin of the MAX740x IC */
#define LOWPASS_CLK_GPIO 20 // GPIO20

/* Connected to the output of the lowpass filter */
#define ADC_AUDIO_3_GPIO ADCINA1 // ADCINA1

/* Connected to the output of the lowpass filter */
#define ADC_AUDIO_4_GPIO ADCINB1 // ADCINB1

/************* Toggle *************/
/* Connected to the toggle switch */
#define TOGGLE_GPIO 61 // GPIO61

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
