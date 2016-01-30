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
/* Contains functions for the indicator LEDs.
 *																			  */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "LED.h"
#include "MISC.h"
#include "USER.h"

/******************************************************************************/
/* Private Variable Declaration		                                          */
/******************************************************************************/
static ENUM_LED_MODE LED_mode = LED_OFF;
static unsigned long LED_Blinkingcount = 0;

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/* Inline Functions 														  */
/******************************************************************************/

/******************************************************************************/
/* Functions																  */
/******************************************************************************/

/******************************************************************************/
/* InitLEDs
 *
 * The function initializes the LEDs.										  */
/******************************************************************************/
void InitLEDs(void)
{
	unsigned char i;

	/* flash LEDs for user */
	for(i=0;i<5;i++)
	{
		LED_RedLED(ON);
		LED_GreenLED(OFF);
		MSC_DelayUS(100000);
		LED_RedLED(OFF);
		LED_GreenLED(ON);
		MSC_DelayUS(100000);
	}
	LED_RedLED(ON);
	LED_GreenLED(OFF);
}

/******************************************************************************/
/* LED_RedLED
 *
 * The function controls the Red LED.										  */
/******************************************************************************/
void LED_RedLED(unsigned char state)
{
	if(state)
	{
		SYS_WritePin(RED_LED_GPIO, ON);
	}
	else
	{
		SYS_WritePin(RED_LED_GPIO, OFF);
	}
}

/******************************************************************************/
/* LED_GreenLED
 *
 * The function controls the Green LED.										  */
/******************************************************************************/
void LED_GreenLED(unsigned char state)
{
	if(state)
	{
		SYS_WritePin(GREEN_LED_GPIO, ON);
	}
	else
	{
		SYS_WritePin(GREEN_LED_GPIO, OFF);
	}
}

/******************************************************************************/
/* LED_GetMode
 *
 * The function gets the LED mode.											  */
/******************************************************************************/
ENUM_LED_MODE LED_GetMode(void)
{
	return LED_mode;
}

/******************************************************************************/
/* LED_SetMode
 *
 * The function sets the LED mode.											  */
/******************************************************************************/
void LED_SetMode(ENUM_LED_MODE mode)
{
	LED_mode = mode;

	LED_GreenLED(OFF);
	LED_RedLED(OFF);
	LED_Blinkingcount = 0;
	if(mode == RED || mode == RED_BLINKING)
	{
		LED_RedLED(ON);
	}
	else if(mode == GREEN || mode == GREEN_BLINKING)
	{
		LED_GreenLED(ON);
	}
}

/******************************************************************************/
/* LED_SetMode
 *
 * The function sets the LED mode.											  */
/******************************************************************************/
void LED_BlinkingAction(ENUM_LED_MODE mode)
{
	if(mode == RED_BLINKING || mode == GREEN_BLINKING)
	{
		if(LED_Blinkingcount < LED_BLINKING_COUNT_SPEED)
		{
			LED_Blinkingcount++;
		}
		else
		{
			LED_Blinkingcount = 0;
			if(mode == GREEN_BLINKING)
			{
				if(SYS_ReadPin(GREEN_LED_GPIO))
				{
					LED_GreenLED(OFF);
				}
				else
				{
					LED_GreenLED(ON);
				}
			}
			else if(mode == RED_BLINKING)
			{
				if(SYS_ReadPin(RED_LED_GPIO))
				{
					LED_RedLED(OFF);
				}
				else
				{
					LED_RedLED(ON);
				}
			}
		}
	}
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
