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
#ifndef MISC_H
#define	MISC_H

#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "SYSTEM.h"

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Bit Defines                                                                */
/******************************************************************************/
#define b0 			0x00
#define b00 		0x00
#define b000 		0x00
#define b0000 		0x00
#define b00000 		0x00
#define b000000 	0x00
#define b0000000 	0x00
#define b00000000 	0x00

#define b1 			0x01
#define b01 		0x01
#define b001 		0x01
#define b0001 		0x01
#define b00001 		0x01
#define b000001 	0x01
#define b0000001 	0x01
#define b00000001 	0x01

#define b10 		0x02
#define b010 		0x02
#define b0010 		0x02
#define b00010 		0x02
#define b000010 	0x02
#define b0000010 	0x02
#define b00000010 	0x02

#define b11 		0x03
#define b011 		0x03
#define b0011 		0x03
#define b00011 		0x03
#define b000011 	0x03
#define b0000011 	0x03
#define b00000011 	0x03

#define b100 		0x04
#define b0100 		0x04
#define b00100 		0x04
#define b000100 	0x04
#define b0000100 	0x04
#define b00000100 	0x04

#define b101 		0x05
#define b0101 		0x05
#define b00101 		0x05
#define b000101 	0x05
#define b0000101 	0x05
#define b00000101 	0x05

#define b110 		0x06
#define b0110 		0x06
#define b00110 		0x06
#define b000110 	0x06
#define b0000110 	0x06
#define b00000110 	0x06

#define b111 		0x07
#define b0111 		0x07
#define b00111 		0x07
#define b000111 	0x07
#define b0000111 	0x07
#define b00000111 	0x07

#define b1000 		0x08
#define b01000 		0x08
#define b001000 	0x08
#define b0001000 	0x08
#define b00001000 	0x08

#define b1001 		0x09
#define b01001 		0x09
#define b001001 	0x09
#define b0001001 	0x09
#define b00001001 	0x09

#define b1010 		0x0A
#define b01010 		0x0A
#define b001010 	0x0A
#define b0001010 	0x0A
#define b00001010 	0x0A

#define b1011 		0x0B
#define b01011 		0x0B
#define b001011 	0x0B
#define b0001011 	0x0B
#define b00001011 	0x0B

#define b1100 		0x0C
#define b01100 		0x0C
#define b001100 	0x0C
#define b0001100 	0x0C
#define b00001100 	0x0C

#define b1101 		0x0D
#define b01101 		0x0D
#define b001101 	0x0D
#define b00011101 	0x0D
#define b00001101 	0x0D

#define b1110 		0x0E
#define b01110 		0x0E
#define b001110 	0x0E
#define b0001110 	0x0E
#define b00001110 	0x0E

#define b1111 		0x0F
#define b01111 		0x0F
#define b001111 	0x0F
#define b0001111 	0x0F
#define b00001111 	0x0F

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void MSC_DelayUS(unsigned long US);
void MSC_DelayNOP(unsigned long NOPs);
unsigned char MSC_IsPrintable(unsigned char data);
void MSC_StringCopy(unsigned char* from,unsigned char* to);
unsigned char MSC_LowercaseChar(unsigned char Input);
double MSC_Round(double input);
unsigned long MSC_ReverseLong(unsigned long This);
unsigned char MSC_StringMatch(unsigned char* This, unsigned char* That);

#endif	/* MISC_H */
