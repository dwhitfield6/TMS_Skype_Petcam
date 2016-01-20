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
/* Files to Include                                                           */
/******************************************************************************/
#ifndef RELAY_H
#define	RELAY_H

#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "USER.h"

/******************************************************************************/
/* SOLID_STATE_RELAY_WITH_ZEROCROSS_DETECTION
 *
 * This macro defines the type of solid state relay. When defined it means
 *  the solid state relay has built in zerocross detection so dimming is
 *  impossible.																  */
/******************************************************************************/
#define SOLID_STATE_RELAY_WITH_ZEROCROSS_DETECTION

/******************************************************************************/
/* AC_FREQUENCY
 *
 * This is the frequency of the wall AC.									  */
/******************************************************************************/
#define AC_FREQUENCY 60.0

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern unsigned char RLY_SSRelayDuty;

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitRelay(void);
void RLY_ZeroCrossInterrupt(unsigned char state);
void RLY_MechRelay(unsigned char state);
void RLY_SolidStateRelay(unsigned char state);


#endif	/* RELAY_H */
