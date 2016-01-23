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
#ifndef TV_H
#define	TV_H

#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "USER.h"

/******************************************************************************/
/* Structures                                                                 */
/******************************************************************************/
typedef enum e_tv_input
{
    HDMI1 	= 0,
	HDMI2 	= 1,
	HDMI3 	= 2,
	USB		= 3,
	CABLE	= 4,
	VIDEO	= 5,
}ENUM_TV_INPUT;

typedef enum e_skype_mode
{
    SKYPE 		= 0,
	ORIGINAL 	= 1,
}ENUM_SKYPE_MODE;

/******************************************************************************/
/* TV_REPEAT_NEC_TIMES
 *
 * This is the number of repeat characters we see until we act (the TV is
 *  slow to react).															  */
/******************************************************************************/
#define TV_REPEAT_NEC_TIMES 4

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern ENUM_TV_INPUT Original_TV_inputMode;
extern ENUM_TV_INPUT Current_TV_inputMode;
extern unsigned char Original_TV_Power;
extern unsigned char Current_TV_Power;

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitTV(void);
void TV_GoToSkypeMode(void);
void TV_GoToOriginalMode(void);
void TV_SetMode(ENUM_SKYPE_MODE mode);
ENUM_SKYPE_MODE TV_GetMode(void);

#endif	/* TV_H */
