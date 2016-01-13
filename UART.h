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
#ifndef UART_H
#define	UART_H

#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "USER.h"

/******************************************************************************/
/* Structures                                                                 */
/******************************************************************************/
typedef enum e_parity
{
    PARITY_NONE,       // no parity bit
	PARITY_EVEN,       // even parity bit
	PARITY_ODD         // odd parity bit
}ENUM_PARITY;

/******************************************************************************/
/* UART_A buffer sizes
 *
 * This is the number of characters that fit in the UART A receive/transmit
 *  buffer.																	  */
/******************************************************************************/
#define UART_A_RECEIVE_SIZE 100
#define UART_A_TRANSMIT_SIZE 100

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern volatile unsigned int RX_A_Buffer_Place;
extern unsigned char RX_A_Buffer[UART_A_RECEIVE_SIZE];
extern unsigned char TX_A_Buffer[UART_A_TRANSMIT_SIZE];
extern volatile int TX_A_Buffer_ADD_Place;
extern volatile int TX_A_Buffer_REMOVE_Place;

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitUART(void);
void InitUART_A(void);
void UART_SetParametersA(unsigned long Baud, unsigned char stop, ENUM_PARITY parity);
unsigned char UART_GetFIFO(void);
void UART_SetFIFO(unsigned char state);
void UART_ModuleEnableA(unsigned char state);
void UART_ReceiveInterruptA(unsigned char state);
void UART_TransmitInterruptA(unsigned char state);
void UART_TransmitEnableA(unsigned char state);
void UART_ReceiveEnableA(unsigned char state);
void UART_ModulePinsA(unsigned char state);
void UART_PutCharA(unsigned char data);
unsigned char UART_GetCharA(unsigned char* FramingError, unsigned char* ParityError);
void UART_SendChar(unsigned char data);
void UART_SendString(unsigned char* data);

#endif	/* UART_H */
