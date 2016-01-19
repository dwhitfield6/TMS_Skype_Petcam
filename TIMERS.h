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
#ifndef TIMERS_H
#define	TIMERS_H

#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "USER.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitTimers(void);
void InitTimer0(void);
void InitTimer1(void);
void TMR_SetTimerWithPeriod0(void);
unsigned long TMR_GetTimer0(void);
void TMR_SetTimerPeriod0(unsigned long period);
unsigned long TMR_GetTimerPeriod0(void);
unsigned char TMR_Interrupt0(unsigned char state);
void TMR_StartTimer0(unsigned char state);
void TMR_SetTimerFlag0(void);
void TMR_ClearTimerFlag0(void);
unsigned char TMR_GetTimerFlag0(void);
#endif	/* TIMERS_H */
