/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 01/12/15     13.0_DW0a   First coding.
 *                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

/******************************************************************************/
/* ISR prototypes                                                        	  */
/******************************************************************************/
interrupt void ISR_UART_A_RX(void);
interrupt void ISR_UART_A_TX(void);
interrupt void ISR_INT1_BUTTON(void);
interrupt void ISR_INT2_ZEROCROSS(void);

#endif	/* INTERRUPTS_H */