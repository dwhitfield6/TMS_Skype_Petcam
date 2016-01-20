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
/* NEC timing
 *
 * This is timing bounds of an NEC code in microseconds.					  */
/******************************************************************************/
/************* NEC header burst *************/
#define NEC_HEADER_HIGH	9200
#define NEC_HEADER_LOW	8800

/************* NEC header space for non-repeat code *************/
#define NEC_NONREPEAT_HIGH	4700
#define NEC_NONREPEAT_LOW	4300

/************* NEC header space for repeat code *************/
#define NEC_REPEAT_HIGH	2500
#define NEC_REPEAT_LOW	2000

/************* NEC pulse burst *************/
#define NEC_PULSE_BURST_HIGH	800
#define NEC_PULSE_BURST_LOW		300

/************* NEC space short for transmitting 0 *************/
#define NEC_SPACE_SHORT_HIGH	1300
#define NEC_SPACE_SHORT_LOW		1000

/************* NEC space long for transmitting 1 *************/
#define NEC_SPACE_LONG_HIGH	2500
#define NEC_SPACE_LONG_LOW	2000

/******************************************************************************/
/* NEC_CODE_EDGES_NONREPEAT
 *
 * This is the number of edges required for a valid NEC code (non-repeat).	  */
/******************************************************************************/
#define NEC_CODE_EDGES_NONREPEAT 128

/******************************************************************************/
/* NEC_CODE_EDGES_REPEAT
 *
 * This is the number of edges required for a valid NEC code (repeat).	  */
/******************************************************************************/
#define NEC_CODE_EDGES_REPEAT 20

/******************************************************************************/
/* IR_LED_50_50
 *
 * This is the duty cyce to twitch the LED when it is "ON".					  */
/******************************************************************************/
#define IR_LED_50_50 50

/******************************************************************************/
/* LARGEST_DESCRIPTION
 *
 * This is the largest button description									  */
/******************************************************************************/
#define LARGEST_DESCRIPTION 20L

/******************************************************************************/
/* MAX_IR_RECEIVE_EVENTS
 *
 * This is the number of IR edge timing events.								  */
/******************************************************************************/
#define MAX_IR_RECEIVE_EVENTS 200L

/******************************************************************************/
/* IR_RECEIVE_COUNTS_TIMEOUT
 *
 * This is the number counts we wait for a timeout							  */
/******************************************************************************/
#define IR_RECEIVE_COUNTS_TIMEOUT 0xFFFFFFFF

/******************************************************************************/
/* Structures                                                                 */
/******************************************************************************/
typedef struct Type_ir_nec
{
    unsigned char Description[LARGEST_DESCRIPTION];     // button description
    unsigned long NEC;           						// NEC code
}NECTYPE;

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern const NECTYPE Sanyo[];
extern const NECTYPE Visio[];
extern const NECTYPE Idylis[];
extern unsigned char NumSanyo;
extern unsigned char NumVisio;
extern unsigned char NumIdylis;
extern unsigned long IR_Receive_Timing_Counts[MAX_IR_RECEIVE_EVENTS];
extern unsigned long IR_Receive_Timing_MicroSeconds[MAX_IR_RECEIVE_EVENTS];
extern unsigned short IR_Receive_Timing_place;
extern unsigned char NEC_REPEAT;
extern unsigned char IR_NEC_Start;
extern unsigned long NEC;
extern unsigned long temp_NEC;

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitIR(void);
void InitIRSend(void);
void InitIRReceive(void);
void IR_ReceiverInterrupt(unsigned char state);
void IR_LEDModulePins(unsigned char state);
void IR_LEDTest(void);
void IR_LEDPWMTest(void);
void IR_LED(unsigned char state);
void IR_SendNECRepeat(void);
void IR_SendNEC(unsigned long code);
void IR_SendNECWithRepeat(unsigned long NEC);
unsigned char IR_CMDCheckMatch(unsigned char* received, const NECTYPE* codes, unsigned char* match);
void IR_SetReceiveFlag(void);
void IR_ClearReceiveFlag(void);
unsigned char IR_GetReceiveFlag(void);
unsigned char IR_ProcessReceiveNEC(unsigned long *NEC);
void IR_DisableReceive(void);
void IR_EnableReceive(void);

#endif	/* IR_H */
