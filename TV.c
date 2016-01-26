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
/* Contains functions for interacting with the Television.
 *																			  */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "IR.h"
#include "LED.h"
#include "MISC.h"
#include "RELAY.h"
#include "TV.h"
#include "USER.h"

/******************************************************************************/
/* Private Variable Declaration		                                          */
/******************************************************************************/
static ENUM_SKYPE_MODE TV_Skype_Mode = ORIGINAL;

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
ENUM_TV_INPUT Original_TV_inputMode;
ENUM_TV_INPUT Current_TV_inputMode;
unsigned char Original_TV_Power;
unsigned char Current_TV_Power;

/******************************************************************************/
/* Inline Functions                                                           */
/******************************************************************************/

/******************************************************************************/
/* Functions																  */
/******************************************************************************/

/******************************************************************************/
/* InitTV
 *
 * The function initializes the televison.									  */
/******************************************************************************/
void InitTV(void)
{
	Original_TV_inputMode = HDMI2;
	Current_TV_inputMode = Original_TV_inputMode;
	Original_TV_Power = ON;
	Current_TV_Power = Original_TV_Power;
}

/******************************************************************************/
/* TV_GoToSkypeMode
 *
 * The function puts the TV input to the mode for skype.					  */
/******************************************************************************/
void TV_GoToSkypeMode(void)
{
	LED_RedLED(OFF);
	LED_GreenLED(ON);
	RLY_MechRelay(ON);
	TV_SetMode(SKYPE);
	if(!Current_TV_Power)
	{
		IR_SendNECWithRepeatASCII("Power", Sanyo);
		MSC_DelayUS(1000000);
		Current_TV_Power = ON;
	}
	while(Current_TV_inputMode != HDMI1)
	{
		IR_SendNECWithRepeatASCII("Source", Sanyo);
		MSC_DelayUS(1000000);
		Current_TV_inputMode++;
		if(Current_TV_inputMode > VIDEO)
		{
			Current_TV_inputMode = HDMI1;
		}
	}
}

/******************************************************************************/
/* TV_GoToOriginalMode
 *
 * The function puts the TV input to the origian mode before switching to
 *  skype mode.																  */
/******************************************************************************/
void TV_GoToOriginalMode(void)
{
	LED_RedLED(ON);
	LED_GreenLED(OFF);
	RLY_MechRelay(OFF);
	TV_SetMode(ORIGINAL);
	if(Original_TV_Power != Current_TV_Power)
	{
		if(Original_TV_Power)
		{
			IR_SendNECWithRepeatASCII("Power", Sanyo);
			Current_TV_Power = OFF;
		}
		else
		{
			IR_SendNECWithRepeatASCII("Power", Sanyo);
			Current_TV_Power = ON;
		}
		MSC_DelayUS(2000000);
	}
	if(Original_TV_inputMode != Current_TV_inputMode)
	{
		while(Original_TV_inputMode != Current_TV_inputMode)
		{
			IR_SendNECWithRepeatASCII("Source", Sanyo);
			MSC_DelayUS(1000000);
			Current_TV_inputMode++;
			if(Current_TV_inputMode > VIDEO)
			{
				Current_TV_inputMode = HDMI1;
			}
		}
	}
}

/******************************************************************************/
/* TV_SetMode
 *
 * The function sets the TV skype mode.										  */
/******************************************************************************/
void TV_SetMode(ENUM_SKYPE_MODE mode)
{
	TV_Skype_Mode = mode;
}

/******************************************************************************/
/* TV_GetMode
 *
 * The function gets the TV skype mode.										  */
/******************************************************************************/
ENUM_SKYPE_MODE TV_GetMode(void)
{
	return TV_Skype_Mode;
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
