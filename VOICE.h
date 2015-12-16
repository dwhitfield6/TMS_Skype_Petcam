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
/* These are WAV files used to play voice to tell the user what is happening.
 *  At startup, "Marley Pet cam initialized" plays. When a skype call is
 *  initiated, "Marley pet cam active" is played. When a skype call is ended,
 *   "Marley pet cam finished" playes.                                        */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#ifndef VOICE_H
#define	VOICE_H

#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "USER.h"

/******************************************************************************/
/* Start-up voice wave file "Marley Pet cam initialized"                      */
/******************************************************************************/
unsigned char VoiceInit_wav[] =
{

};

/******************************************************************************/
/* Call start voice wave file "Marley pet cam active"                 	      */
/******************************************************************************/
unsigned char VoiceStart_wav[] =
{

};

/******************************************************************************/
/* Call end voice wave file "Marley pet cam finished"                         */
/******************************************************************************/
unsigned char VoiceEnd_wav[] =
{

};

#endif	/* VOICE_H */
