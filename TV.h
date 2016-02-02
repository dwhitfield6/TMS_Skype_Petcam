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

#include "AUDIO.h"
#include "USER.h"

/******************************************************************************/
/* LARGEST_SKYPE_DESCRIPTION
 *
 * This is the largest size of the skype code description.					  */
/******************************************************************************/
#define LARGEST_SKYPE_DESCRIPTION 30

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

typedef struct t_skype_codes
{
    unsigned char Description[LARGEST_SKYPE_DESCRIPTION]; 	// skype code description
    unsigned char AudioCode;           						// Audio code
}TYPE_SKYPE_CODE;

/******************************************************************************/
/* TV_REPEAT_NEC_TIMES
 *
 * This is the number of repeat characters we see until we act (the TV is
 *  slow to react).															  */
/******************************************************************************/
#define TV_REPEAT_NEC_TIMES 4

/******************************************************************************/
/* TV_SKYPE_AUDIO_CODE_LENGTH_MICROSECONDS
 *
 * This is the number of microseconds that a SKYPE audio protocol code takes. */
/******************************************************************************/
#define TV_SKYPE_AUDIO_CODE_LENGTH_MICROSECONDS 600000.0

/******************************************************************************/
/* TV_SKYPE_AUDIO_ADC_HIGH
 *
 * This is the number of ADC counts that signifiy a code burst is happening.  */
/******************************************************************************/
#define TV_SKYPE_AUDIO_ADC_HIGH 3800

/******************************************************************************/
/* TV_SKYPE_AUDIO_ADC_LOW
 *
 * This is the number of ADC counts that signify a code burst is happening.  */
/******************************************************************************/
#define TV_SKYPE_AUDIO_ADC_LOW 300

/******************************************************************************/
/* FIND_LOCAL_WRONG_WAY_COUNT
 *
 * This is the multiplier for the Audio protocol timing for a valid larger
 *  than expected.															  */
/******************************************************************************/
#define FIND_LOCAL_WRONG_WAY_COUNT 200

/******************************************************************************/
/* AUDIO_ADC_TIMING_HIGH_LIMIT
 *
 * This is the multiplier for the Audio protocol timing for a valid larger
 *  than expected.															  */
/******************************************************************************/
#define AUDIO_ADC_TIMING_HIGH_LIMIT 1.2

/******************************************************************************/
/* AUDIO_ADC_TIMING_LOW_LIMIT
 *
 * This is the multiplier for the Audio protocol timing for a valid smaller
 *  than expected.															  */
/******************************************************************************/
#define AUDIO_ADC_TIMING_LOW_LIMIT 0.8

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern ENUM_TV_INPUT Original_TV_inputMode;
extern ENUM_TV_INPUT Current_TV_inputMode;
extern unsigned char Original_TV_Power;
extern unsigned char Current_TV_Power;
extern unsigned char TV_SKYPE_Audio_Code_Started;
extern double TV_SKYPE_Audio_ProtocolTotalMicroseconds;
extern const TYPE_SKYPE_CODE SKYPE_Codes[];
extern unsigned char NumSKYPE;

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitTV(void);
void TV_GoToSkypeMode(void);
void TV_GoToOriginalMode(void);
void TV_SetMode(ENUM_SKYPE_MODE mode);
ENUM_SKYPE_MODE TV_GetMode(void);
void TV_SKYPE_SetDecodeFlag(unsigned char state);
unsigned char TV_SKYPE_GetDecodeFlag(void);
unsigned char TV_SKYPE_Decode(TYPE_LOWPASS* buffer, unsigned short amount, const TYPE_SKYPE_CODE* codes, unsigned char* index);
unsigned char TV_SKYPE_FindFirstLocalMaximumIncreasing(TYPE_LOWPASS* buffer, unsigned short start, unsigned short finish, unsigned short* index);
unsigned char TV_SKYPE_FindFirstLocalMaximumDecreasing(TYPE_LOWPASS* buffer, unsigned short start, unsigned short finish, unsigned short* index);
unsigned char TV_SKYPE_FindFirstLocalMinimumIncreasing(TYPE_LOWPASS* buffer, unsigned short start, unsigned short finish, unsigned short* index);
unsigned char TV_SKYPE_FindFirstLocalMinimumDecreasing(TYPE_LOWPASS* buffer, unsigned short start, unsigned short finish, unsigned short* index);
void TV_SKYPE_SearchingEnabled(unsigned char mode);
unsigned char TV_SKYPE_GetSearchingStatus(void);
double TV_SKYPE_AccumulatedTime(TYPE_LOWPASS* buffer, unsigned short start, unsigned short finish);

#endif	/* TV_H */
