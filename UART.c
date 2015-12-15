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
/* Contains functions for Universal asynchronous receiver/transmitter.
 *																			  */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "USER.h"
#include "UART.h"
#include "SYSTEM.h"
#include "MISC.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
unsigned short RX1_Buffer_Place = 0;
unsigned char RX1_Buffer[UART1_RECEIVE_SIZE];
unsigned char TX1_Buffer[UART1_TRANSMIT_SIZE];
volatile unsigned short TX1_Buffer_ADD_Place = 0;
unsigned short TX1_Buffer_REMOVE_Place = 0;

/******************************************************************************/
/* Inline Functions															  */
/******************************************************************************/

/******************************************************************************/
/* Functions																  */
/******************************************************************************/

/******************************************************************************/
/* InitUART
 *
 * The function initializes the UART module.								  */
/******************************************************************************/
void InitUART(void)
{

}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
