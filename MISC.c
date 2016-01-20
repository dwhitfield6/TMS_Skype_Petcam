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
/* Contains Miscellaneous Functions
 *																			  */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>
#include <math.h>        /* For true/false definition */

#include "MISC.h"
#include "TIMERS.h"
#include "USER.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/* Inline Functions                                                           */
/******************************************************************************/

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

/******************************************************************************/
/* MSC_DelayUS
 *
 * The function delays the given numebr of microseconds						  */
/******************************************************************************/
void MSC_DelayUS(unsigned long US)
{
    double prescalerD;
    long prescalerL;

    if(US == 0)
    {
    	return;
    }

    prescalerD = MSC_Round(((double)SYSCLK * (double) US) / (16.0 * 1000000.0));
    prescalerL = (long) prescalerD;

    while(prescalerL > MAX_ULONG)
    {
    	TMR_ClearTimerFlag0();	// reset timer flag
        TMR_StartTimer0(FALSE);	// stop timer
        TMR_SetTimerPeriod0(MAX_ULONG);
        TMR_SetTimerWithPeriod0();
        TMR_Interrupt0(ON);
        TMR_StartTimer0(TRUE);	// start timer
        while(!TMR_GetTimerFlag0());
        prescalerL -= MAX_ULONG;
    }

	TMR_ClearTimerFlag0();	// reset timer flag
    TMR_StartTimer0(FALSE);	// stop timer
    TMR_SetTimerPeriod0(prescalerL);
    TMR_SetTimerWithPeriod0();
    TMR_Interrupt0(ON);
    TMR_StartTimer0(TRUE);	// start timer
    while(!TMR_GetTimerFlag0());
}

/******************************************************************************/
/* MSC_DelayNOP
 *
 * The function waists the number of cycles passed into the function.		  */
/******************************************************************************/
void MSC_DelayNOP(unsigned long NOPs)
{
    unsigned long i;
    for(i=0; i<NOPs; i++)
    {
        NOP();
    }
}

/******************************************************************************/
/* MSC_IsPrintable
 *
 * The function returns true if the data is printable.						  */
/******************************************************************************/
unsigned char MSC_IsPrintable(unsigned char data)
{
    if(data >= 0x20 && data <0x7F)
    {
        return TRUE;
    }
    return FALSE;
}

/******************************************************************************/
/* MSC_StringCopy
 *
 * This function copies a string from over to.								  */
/******************************************************************************/
void MSC_StringCopy(unsigned char* from,unsigned char* to)
{
    while(*from != 0)
    {
        *to = *from;
        from++;
        to++;
    }
    *to = *from;
}

/******************************************************************************/
/* MSC_LowercaseChar
 *
 * This function turns the character to lowercase.							  */
/******************************************************************************/
unsigned char MSC_LowercaseChar(unsigned char Input)
{
    if((Input >= 65) && (Input <= 90 ))
    {
        return Input + 32;
    }
    else
    {
        return Input;
    }
}

/******************************************************************************/
/* MSC_Round
 *
 * This function rounds to the nearest whole number.						  */
/******************************************************************************/
double MSC_Round(double input)
{
    long temp = (long)(input + 0.5);

    return (double) temp;
}

/******************************************************************************/
/* MSC_ReverseLong
 *
 * The function reads the value of 'This' and returns the reverse of the
 *  data.																	  */
/******************************************************************************/
unsigned long MSC_ReverseLong(unsigned long This)
{
    unsigned long temp=0;

    temp += (This & 0x00000001) << 31;
    temp += (This & 0x00000002) << 29;
    temp += (This & 0x00000004) << 27;
    temp += (This & 0x00000008) << 25;
    temp += (This & 0x00000010) << 23;
    temp += (This & 0x00000020) << 21;
    temp += (This & 0x00000040) << 19;
    temp += (This & 0x00000080) << 17;
    temp += (This & 0x00000100) << 15;
    temp += (This & 0x00000200) << 13;
    temp += (This & 0x00000400) << 11;
    temp += (This & 0x00000800) << 9;
    temp += (This & 0x00001000) << 7;
    temp += (This & 0x00002000) << 5;
    temp += (This & 0x00004000) << 3;
    temp += (This & 0x00008000) << 1;
    temp += (This & 0x00010000) >> 1;
    temp += (This & 0x00020000) >> 3;
    temp += (This & 0x00040000) >> 5;
    temp += (This & 0x00080000) >> 7;
    temp += (This & 0x00100000) >> 9;
    temp += (This & 0x00200000) >> 11;
    temp += (This & 0x00400000) >> 13;
    temp += (This & 0x00800000) >> 15;
    temp += (This & 0x01000000) >> 17;
    temp += (This & 0x02000000) >> 19;
    temp += (This & 0x04000000) >> 21;
    temp += (This & 0x08000000) >> 23;
    temp += (This & 0x10000000) >> 25;
    temp += (This & 0x20000000) >> 27;
    temp += (This & 0x40000000) >> 29;
    temp += (This & 0x80000000) >> 31;

    return temp;
}
/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
