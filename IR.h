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
#ifndef IR_H
#define	IR_H

#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "USER.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern unsigned short IR_PWM50;
extern unsigned char IR_state;

/******************************************************************************/
/* IR codes                          
 *          
 * This is the NEC codes that we send.
 *                              											  */
/******************************************************************************/
extern unsigned long Sanyo_Power;
extern unsigned long Sanyo_Sleep;
extern unsigned long Sanyo_Menu;
extern unsigned long Sanyo_Volume_Up;
extern unsigned long Sanyo_Volume_Down;
extern unsigned long Sanyo_Channel_Up;
extern unsigned long Sanyo_Channel_Down;
extern unsigned long Sanyo_Mute;
extern unsigned long Sanyo_Back;
extern unsigned long Sanyo_1;
extern unsigned long Sanyo_2;
extern unsigned long Sanyo_3;
extern unsigned long Sanyo_4;
extern unsigned long Sanyo_5;
extern unsigned long Sanyo_6;
extern unsigned long Sanyo_7;
extern unsigned long Sanyo_8;
extern unsigned long Sanyo_9;
extern unsigned long Sanyo_0;
extern unsigned long Sanyo_Enter;
extern unsigned long Sanyo_Source;
extern unsigned long Sanyo_Rewind;
extern unsigned long Sanyo_Play;
extern unsigned long Sanyo_Forward;
extern unsigned long Sanyo_Record;
extern unsigned long Sanyo_Pause;
extern unsigned long Sanyo_Stop;

/*~~~~~~~~~~~~~~ Vizio TV ~~~~~~~~~~~~~~~~~~~~~~~~*/
extern unsigned long Vizio_Power;
extern unsigned long Vizio_Sleep;
extern unsigned long Vizio_Menu;
extern unsigned long Vizio_Volume_Up;
extern unsigned long Vizio_Volume_Down;

/*~~~~~~~~~~~~~~ Idylis AC unit ~~~~~~~~~~~~~~~~~~~~~~~~*/
extern unsigned long Idylis_Power;
extern unsigned long Idylis_FanSpeed;
extern unsigned long Idylis_Mode;
extern unsigned long Idylis_Plus;
extern unsigned long Idylis_Minus;
extern unsigned long Idylis_Timer;

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
inline unsigned char IR_LEDUse(unsigned char state);
inline void IR_LEDTest(void);
void IR_Module(unsigned char state);
void InitIR(void);
void IR_SendNECRepeat(void);
void IR_SendNEC(unsigned long* NEC);
void IR_SendNEC_Repeat(unsigned long* NEC);
void IR_SendNEC_Repeat_CMD(void);
void IR_SendNEC_Repeat_Multiple_CMD(void);

#endif	/* IR_H */
