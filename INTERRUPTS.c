/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 12/15/15     13.0_DW0a   First coding.
 *                                                                            */
/******************************************************************************/


/******************************************************************************/
/* Interrupt Vector Options
 *
 * VECTOR NAMES:
 *
 * AES256_VECTOR
 * RTC_VECTOR
 * PORT4_VECTOR
 * PORT3_VECTOR
 * TIMER3_A1_VECTOR
 * TIMER3_A0_VECTOR
 * PORT2_VECTOR
 * TIMER2_A1_VECTOR
 * TIMER2_A0_VECTOR
 * PORT1_VECTOR
 * TIMER1_A1_VECTOR
 * TIMER1_A0_VECTOR
 * DMA_VECTOR
 * USCI_A1_VECTOR
 * TIMER0_A1_VECTOR
 * TIMER0_A0_VECTOR
 * ADC12_VECTOR
 * USCI_B0_VECTOR
 * USCI_A0_VECTOR
 * WDT_VECTOR
 * TIMER0_B1_VECTOR
 * TIMER0_B0_VECTOR
 * COMP_E_VECTOR
 * UNMI_VECTOR
 * SYSNMI_VECTOR
 * RESET_VECTOR
 *
 * Vector information found here:
 * C:\ti\ccsv6\ccs_base\msp430\include
 *                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "BUTTON.h"
#include "TIMERS.h"
#include "LED.h"
#include "USER.h"
#include "SYSTEM.h"

/******************************************************************************/
/* Global Variables                                                           */
/******************************************************************************/

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/******************************************************************************/
/* Port 1 interrupt (used for button 2)
 *                                                                            */
/******************************************************************************/
/*#pragma vector=PORT1_VECTOR
__interrupt void Port1_ISR(void)
{
	if(P1IFG & Pin_Button2)
	{
		LED_GreenToggle();
		TMR_ResetTimerA0();
		TMR_ModeTimerA0(UP);
		BUT_Button2Interrupt(OFF);
		P1IFG &= ~Pin_Button2;
	}
}
*/
/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
