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
#define UART_A_RECEIVE_SIZE 200
#define UART_A_TRANSMIT_SIZE 200

/******************************************************************************/
/* UART_C buffer sizes
 *
 * This is the number of characters that fit in the UART C receive/transmit
 *  buffer.																	  */
/******************************************************************************/
#define UART_C_RECEIVE_SIZE 200
#define UART_C_TRANSMIT_SIZE 200

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/
#define CR 			'\r'
#define LN 			'\n'
#define CRLN 		"\r\n"
#define SPACE		' '
#define BACKSPACE	0x08
#define DELETE		0x7F

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern volatile unsigned int RX_A_Buffer_Place;
extern volatile unsigned int RX_C_Buffer_Place;
extern unsigned char RX_A_Buffer[UART_A_RECEIVE_SIZE];
extern unsigned char RX_C_Buffer[UART_C_RECEIVE_SIZE];
extern unsigned char TX_A_Buffer[UART_A_TRANSMIT_SIZE];
extern unsigned char TX_C_Buffer[UART_C_TRANSMIT_SIZE];
extern volatile int TX_A_Buffer_ADD_Place;
extern volatile int TX_C_Buffer_ADD_Place;
extern volatile int TX_A_Buffer_REMOVE_Place;
extern volatile int TX_C_Buffer_REMOVE_Place;

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitUART(void);
void InitUART_A(void);
void InitUART_C(void);
void UART_SetParametersA(unsigned long Baud, unsigned char stop, ENUM_PARITY parity);
void UART_SetParametersC(unsigned long Baud, unsigned char stop, ENUM_PARITY parity);
unsigned char UART_GetFIFOA(void);
unsigned char UART_GetFIFOC(void);
void UART_SetFIFOA(unsigned char state);
void UART_SetFIFOC(unsigned char state);
void UART_ModuleEnableA(unsigned char state);
void UART_ModuleEnableC(unsigned char state);
void UART_ReceiveInterruptA(unsigned char state);
void UART_ReceiveInterruptC(unsigned char state);
void UART_TransmitInterruptA(unsigned char state);
void UART_TransmitInterruptC(unsigned char state);
void UART_TransmitEnableA(unsigned char state);
void UART_TransmitEnableC(unsigned char state);
void UART_ReceiveEnableA(unsigned char state);
void UART_ReceiveEnableC(unsigned char state);
void UART_ModulePinsA(unsigned char state);
void UART_ModulePinsC(unsigned char state);
void UART_PutCharA(unsigned char data);
void UART_PutCharC(unsigned char data);
unsigned char UART_GetCharA(unsigned char* FramingError, unsigned char* ParityError);
unsigned char UART_GetCharC(unsigned char* FramingError, unsigned char* ParityError);
void UART_SendCharA(unsigned char data);
void UART_SendCharC(unsigned char data);
void UART_SendStringA(unsigned char* data);
void UART_SendStringC(unsigned char* data);
void UART_SendStringCRLNA(unsigned char* data);
void UART_SendStringCRLNC(unsigned char* data);
void UART_SendBannerA(void);
void UART_SendBannerC(void);
void UART_SendPromptA(void);
void UART_SendPromptC(void);
void UART_ProcessCharacterA(unsigned char data);
void UART_ProcessCharacterC(unsigned char data);

#endif	/* UART_H */
