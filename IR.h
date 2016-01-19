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
void IR_LEDModulePins(unsigned char state);
void IR_LEDTest(void);
void IR_LEDPWMTest(void);
void IR_LED(unsigned char state);
void IR_SendNECRepeat(void);
void IR_SendNEC(unsigned long code);
void IR_SendNECWithRepeat(unsigned long NEC);
unsigned char IR_CMDCheckMatch(unsigned char* received, const NECTYPE* codes, unsigned char* match);

#endif	/* IR_H */
