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

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "SYSTEM.h"

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/
#define BIG     1
#define LITTLE  2
#define MIDDLE  3

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
inline void MSC_Relay(unsigned char state);
void MSC_DelayUS(long US);
void MSC_DelayNOP(unsigned long NOPs);
unsigned char IsLetter(unsigned char data);
unsigned char MSC_IsNumber(unsigned char data);
unsigned char MSC_IsCharacter(unsigned char data);
unsigned char MSC_IsAlphaNumeric(unsigned char data);
unsigned char MSC_IsAlphaNumericString(unsigned char* data);
void MSC_CleanBuffer(void* data, unsigned short bytes);
double MSC_Round(double input);
void MSC_BufferFill(void* buffer, unsigned long data, unsigned char bits, unsigned short bytes);
unsigned short MSC_SizeOfString(unsigned char* string);
void MSC_StringCopy(unsigned char* from,unsigned char* to);
unsigned char MSC_StringMatch(void* This, void* That);
unsigned char MSC_BufferMatch(void* buffer1, void* buffer2, unsigned short bytes);
void MSC_BufferCopy(void* From, void* To, unsigned short bytes);
void MSC_LowercaseString(unsigned char* Input);
void MSC_LowercaseChar(unsigned char* Input);
unsigned short MSC_HEXtoBCD(unsigned short input);
unsigned short MSC_BCDtoHEX(unsigned short input);
unsigned long MSC_Endian(unsigned long number, unsigned char bits, unsigned char style);
unsigned long MSC_ReverseLong(unsigned long This);

#endif	/* MISC_H */
