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

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
