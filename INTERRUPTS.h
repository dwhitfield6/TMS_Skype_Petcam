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
interrupt void ISR_UART_C_RX(void);
interrupt void ISR_UART_A_TX(void);
interrupt void ISR_UART_C_TX(void);
interrupt void ISR_INT1_BUTTON(void);
interrupt void ISR_INT2_ZEROCROSS(void);
interrupt void ISR_INT3_IR_RECEIVE(void);
interrupt void ISR_INT4_TOGGLE(void);
interrupt void ISR_TIMER0_DELAY(void);
interrupt void ISR_TIMER1_IR_RECEIVE(void);
interrupt void ISR_TIMER2_SS_Relay(void);
interrupt void ISR_EPWM_8_IRLED(void);
interrupt void ISR_EPWM_11_LOWPASS(void);
interrupt void ISR_ADC_AUDIO(void);

#endif	/* INTERRUPTS_H */
