/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 01/18/16     13.0_DW0a   Created.
 *                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#ifndef PWM_H
#define	PWM_H

#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "INTERRUPTS.h"
#include "USER.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern unsigned short Period38kHz;
extern unsigned short PeriodLowpass;

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitPWM(void);
void InitPWM_IR(void);
void InitPWM_AudioLowpass(void);
unsigned short PWM_SetFrequency(double frequency);
void PWM_SetDutyCycle8B(unsigned char duty);
void PWM_SetDutyCycle11A(unsigned char duty);
void PWM_SetCMP8B(unsigned short compare);
void PWM_SetCMP11A(unsigned short compare);
unsigned short PWM_GetCMP8B(void);
unsigned short PWM_GetCMP11A(void);
void PWM_ResetTBClock8(void);
void PWM_ResetTBClock11(void);
void PWM_Interrupt8(unsigned char state);
void PWM_Interrupt11(unsigned char state);


#endif	/* PWM_H */
