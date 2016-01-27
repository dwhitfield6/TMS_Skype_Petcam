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
#ifndef ADC_H
#define	ADC_H

#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "USER.h"

/******************************************************************************/
/* Structures                                                                 */
/******************************************************************************/
typedef enum e_adc_module
{
	ADC_ADCA = 0,
	ADC_ADCB = 1,
	ADC_ADCC = 2,
	ADC_ADCD = 3,
}ENUM_ADC_MODULE;

typedef enum e_adc_resolution
{
	ADC_RESOLUTION_12BIT = 0,
	ADC_RESOLUTION_16BIT = 1,
}ENUM_ADC_RESOLUTION;

typedef enum e_adc_mode
{
	ADC_SIGNALMODE_SINGLE = 0,
	ADC_SIGNALMODE_DIFFERENTIAL = 1,
}ENUM_ADC_MODE;

/******************************************************************************/
/* MACRO Functions and Pointer Functions                                      */
/******************************************************************************/

/******************************************************************************/
/* ADC_GetSetADCTrimPOINTER
 *
 * The Pointer to a function call looks up the ADC offset trim for a given
 *  condition.  															  */
/******************************************************************************/
#define ADC_GetSetADCTrimPOINTER (unsigned short (*)(unsigned short OTPoffset))0x0703AC

/******************************************************************************/
/* ADC_CalADC_A_INL_POINTER
 *
 * The Pointer to functions calibrate the ADC A linearity. 															  */
/******************************************************************************/
#define ADC_CalADC_A_INL_POINTER (void   (*)(void))0x0703B4

/******************************************************************************/
/* ADC_CalADC_B_INL_POINTER
 *
 * The Pointer to functions calibrate the ADC A linearity. 															  */
/******************************************************************************/
#define ADC_CalADC_B_INL_POINTER (void   (*)(void))0x0703B2

/******************************************************************************/
/* ADC_CalADC_C_INL_POINTER
 *
 * The Pointer to functions calibrate the ADC A linearity. 															  */
/******************************************************************************/
#define ADC_CalADC_C_INL_POINTER (void   (*)(void))0x0703B0

/******************************************************************************/
/* ADC_CalADC_D_INL_POINTER
 *
 * The Pointer to functions calibrate the ADC A linearity. 															  */
/******************************************************************************/
#define ADC_CalADC_D_INL_POINTER (void   (*)(void))0x0703AE

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitADC(void);
void ADC_ModuleA(unsigned char state);
void ADC_SetMode(ENUM_ADC_MODULE adc, ENUM_ADC_RESOLUTION resolution, ENUM_ADC_MODE signalmode);
void ADC_LoadTrim(ENUM_ADC_MODULE adc);
void ADC_SetupContinuousA(void);
unsigned char ADC_BusyA(void);
void ADC_InterruptA(unsigned char state);
void ADC_ForceSampleA(void);
unsigned char ADC_GetStatusA(void);

#endif	/* ADC_H */
