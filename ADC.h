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

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "USER.h"

/******************************************************************************/
/* ADC_BITS
 *
 * This is the resolution in bits of the internal ADC						  */
/******************************************************************************/
#define ADC_BITS 16

/******************************************************************************/
/* VREF
 *
 * This is the reference voltage for the a measurements.					  */
/******************************************************************************/
#define VREF 3.3

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
inline unsigned char ADC_Interrupt(unsigned char state);
inline unsigned char ADC_Module(unsigned char state);
void InitADC(void);
void ADC_SetSample(unsigned char channel);
void ADC_StopSample(void);
void ADC_ReadRails(void);

#endif	/* ADC_H */
