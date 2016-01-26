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
#ifndef AUDIO_H
#define	AUDIO_H

#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "USER.h"

/******************************************************************************/
/* Structures                                                                 */
/******************************************************************************/
typedef enum e_processing
{
	AVERAGE = 0,
}ENUM_AUDIO_PROCESSING;

typedef struct t_lowpass
{
	unsigned long ADC;			// Raw ADC counts
	unsigned long TimingCounts;	// Raw timer1 difference in counts
	double MicroSeconds;		// Timer 1 difference in Microseconds
}TYPE_LOWPASS;

/******************************************************************************/
/* AUDIO_ADC_BUFFER_SIZE
 *
 * This is the buffer size for storing raw ADC counts of audio samples.	  */
/******************************************************************************/
#define AUDIO_ADC_BUFFER_SIZE 1000

/******************************************************************************/
/* LOWPASS_BUFFER_SIZE
 *
 * This is the buffer size for storing raw Low pass ADC counts and timing
 *  data.																	  */
/******************************************************************************/
#define LOWPASS_BUFFER_SIZE 2

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern unsigned short Audio_ADC_Counts_Unfiltered_Buffer[AUDIO_ADC_BUFFER_SIZE];
extern unsigned short Audio_ADC_Counts_Unfiltered_place;
extern unsigned short AudioProcessingSampleLarge;
extern unsigned short AudioProcessingSampleSmall;
extern double AudioProcess1;
extern double AudioProcess2;
extern ENUM_AUDIO_PROCESSING AudioProcessing;
extern unsigned int SSRelayOnCount;
extern unsigned int SSRelayAntiTwitchCount;
extern TYPE_LOWPASS Audio_ADC_Counts_LowPass_Buffer[LOWPASS_BUFFER_SIZE];
extern unsigned short Audio_ADC_Counts_LowPass_place;

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitAudio(void);
void AUD_Sampling(unsigned char state);
void AUD_SetSampleReadyFlag(void);
void AUD_ClearSampleReadyFlag(void);
unsigned char AUD_GetSampleReadyFlag(void);
void AUD_Process(unsigned short* buffer, unsigned short AmountInBuffer, ENUM_AUDIO_PROCESSING processing, unsigned short AmountToSample, double* result);
void AUD_ShiftoutBuffer(unsigned short* buffer, unsigned short* amount, unsigned short shift);

#endif	/* AUDIO_H */
