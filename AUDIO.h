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

/******************************************************************************/
/* AUDIO_ADC_BUFFER_SIZE
 *
 * This is the buffer size for storing raw AADC counts of audio samples.	  */
/******************************************************************************/
#define AUDIO_ADC_BUFFER_SIZE 1000

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern unsigned short Audio_ADC_Counts_Buffer[AUDIO_ADC_BUFFER_SIZE];
extern unsigned short Audio_ADC_Counts_place;
extern unsigned short AudioProcessingSample;
extern double AudioProcess1;
extern double AudioProcess2;
extern ENUM_AUDIO_PROCESSING AudioProcessing;

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
void AUD_SetSamplingEnabledFlag(unsigned char state);
unsigned char AUD_GetSamplingEnabledFlag(void);
void AUD_Process(unsigned short* buffer, unsigned short AmountInBuffer, ENUM_AUDIO_PROCESSING processing, unsigned short AmountToSample, double* result);
void AUD_ShiftoutBuffer(unsigned short* buffer, unsigned short* amount, unsigned short shift);

#endif	/* AUDIO_H */
