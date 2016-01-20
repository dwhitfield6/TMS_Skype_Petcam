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
/* Contains functions to transmit and receive IR codes.
 *																			  */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "CMD.h"
#include "IR.h"
#include "MISC.h"
#include "PWM.h"
#include "SYSTEM.h"
#include "TIMERS.h"
#include "USER.h"

/******************************************************************************/
/* IR codes                          
 *          
 * This is the NEC codes that we send.
 *                              											  */
/******************************************************************************/
/*~~~~~~~~~~~~~~ Sanyo TV ~~~~~~~~~~~~~~~~~~~~~~~~*/
const NECTYPE Sanyo[] =
{
	{"Power",  			0x1CE348B7},
	{"Sleep",  			0x1CE3B04F},
	{"Menu",  			0x1CE3E817},
	{"Volume Up",  		0x1CE3708F},
	{"Volume Down", 	0x1CE3F00F},
	{"Channel Up", 		0x1CE350AF},
	{"Channel Down",	0x1CE3D02F},
	{"Mute",  			0x1CE318E7},
	{"Back",  			0x1CE39867},
	{"1",  				0x1CE3807F},
	{"2",  				0x1CE340BF},
	{"3",  				0x1CE3C03F},
	{"4",  				0x1CE320DF},
	{"5",  				0x1CE3A05F},
	{"6",  				0x1CE3609F},
	{"7",  				0x1CE3E01F},
	{"8",  				0x1CE310EF},
	{"9",  				0x1CE3906F},
	{"0",  				0x1CE300FF},
	{"Enter",  			0x1CE32AD5},
	{"Source",  		0x1CE3C837},
	{"Rewind",  		0x1CE3946B},
	{"Play",  			0x1CE324DB},
	{"Forward",  		0x1CE314EB},
	{"Record",  		0xFFFFFFFF},
	{"Pause",  			0x1CE3649B},
	{"Stop",  			0x1CE3A45B},
};

/*~~~~~~~~~~~~~~ Vizio TV ~~~~~~~~~~~~~~~~~~~~~~~~*/
const NECTYPE Visio[] =
{
	{"Power",  			0x20DF10EF},
	{"Sleep",  			0x20DF708F},
	{"Menu",  			0x20DFF20D},
	{"Volume Up",  		0x20DF40BF},
	{"Volume Down", 	0x20DFC03F},
};

/*~~~~~~~~~~~~~~ Idylis AC unit ~~~~~~~~~~~~~~~~~~~~~~~~*/
const NECTYPE Idylis[] =
{
	{"Power",  			0x4FB40BF},
	{"Fan Speed",  		0x4FB58A7},
	{"Mode",  			0x4FB906F},
	{"Plus",  			0x4FB50AF},
	{"Minus", 			0x4FB8877},
	{"Timer", 			0x4FB9867},
};

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
unsigned char NumSanyo = 0;
unsigned char NumVisio = 0;
unsigned char NumIdylis = 0;

/******************************************************************************/
/* Functions																  */
/******************************************************************************/

/******************************************************************************/
/* InitIR
 *
 * The function initializes the IR LED transmitter and receiver.			  */
/******************************************************************************/
void InitIR(void)
{
	NumSanyo = sizeof(Sanyo) / sizeof(NECTYPE);
	NumVisio = sizeof(Visio) / sizeof(NECTYPE);
	NumIdylis = sizeof(Idylis) / sizeof(NECTYPE);
	InitIRSend();
	InitIRReceive();
}

/******************************************************************************/
/* InitIRSend
 *
 * The function initializes the IR LED transmitter.							  */
/******************************************************************************/
void InitIRSend(void)
{
	IR_LEDModulePins(FALSE);
	IR_LED(OFF);
	PWM_SetDutyCycle(IR_LED_50_50);
}

/******************************************************************************/
/* InitIRReceive
 *
 * The function initializes the IR receiver.								  */
/******************************************************************************/
void InitIRReceive(void)
{
	/* Set INT1 ISRs */
	SYS_Unlock();
	PieVectTable.XINT3_INT = &ISR_INT3_IR_RECEIVE;
	SYS_Lock();
	SYS_EnableInterruptGroup(INTERRUPT_GROUP12);	// Group for INT12
	IR_ReceiverInterrupt(ON);
	SYS_Unlock();
    InputXbarRegs.INPUT6SELECT = IR_RECEIVER_GPIO;	//Set XINT3 source to GPIO-pin
    SYS_Lock();
    XintRegs.XINT3CR.bit.POLARITY = 0b11;    		// 11: Interrupt is selected as positive or negative edge triggered
}

/******************************************************************************/
/* IR_ReceiverInterrupt
 *
 * The function controls the IR receiver interrupt.							  */
/******************************************************************************/
void IR_ReceiverInterrupt(unsigned char state)
{
	if (state)
	{
		PieCtrlRegs.PIEIER12.bit.INTx1 = 1;   	// Enable PIE Group 12 INT1
		XintRegs.XINT3CR.bit.ENABLE = 1;        // Enable XINT3
	}
	else
	{
		PieCtrlRegs.PIEIER12.bit.INTx1 = 0;   	// Disable PIE Group 12 INT1
		XintRegs.XINT3CR.bit.ENABLE = 0;        // Disable XINT3
	}
}

/******************************************************************************/
/* IR_LEDModulePins
 *
 * The function sets the IR LED to PWM mode.								  */
/******************************************************************************/
void IR_LEDModulePins(unsigned char state)
{
	SYS_Unlock();
    if(state)
    {
        /* Map the remappable pin */ 
    	GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0b01;	// Configure GPIO15 as EPWM8B
    }
    else
    {
    	GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0b00;	// Configure GPIO15 as gpio
    }
	SYS_Lock();
}

/******************************************************************************/
/* IR_LEDTest
 *
 * The function tests the IR LED.											  */
/******************************************************************************/
void IR_LEDTest(void)
{
	IR_LEDModulePins(FALSE);
    while(1)
    {
		IR_LED(ON);
		MSC_DelayUS(1000);
		IR_LED(OFF);
		MSC_DelayUS(1000);
    }
}

/******************************************************************************/
/* IR_LEDPWMTest
 *
 * The function tests the IR LED in PWM mode.								  */
/******************************************************************************/
void IR_LEDPWMTest(void)
{
	IR_LEDModulePins(TRUE);
}

/******************************************************************************/
/* IR_LED
 *
 * The function controls the IR LED when not in PWM mode.					  */
/******************************************************************************/
void IR_LED(unsigned char state)
{
	if(state)
	{
		SYS_WritePin(IR_LED_GPIO, ON);
	}
	else
	{
		SYS_WritePin(IR_LED_GPIO, OFF);
	}
}

/******************************************************************************/
/* IR_SendNECRepeat
 *
 * The function sends the NEC repeat code.									  */
/******************************************************************************/
void IR_SendNECRepeat(void)
{
	/* make sure that the first cycle is fresh */
	PWM_ResetTBClock();

    /* send repeat */
	IR_LEDModulePins(TRUE);
    MSC_DelayUS(9000);
    IR_LEDModulePins(FALSE);
    MSC_DelayUS(2250);
    
    IR_LEDModulePins(TRUE);
    MSC_DelayUS(563);
    IR_LEDModulePins(FALSE);
    MSC_DelayUS(96875);
}

/******************************************************************************/
/* IR_SendNEC
 *
 * The function sends the NEC code.											  */
/******************************************************************************/
void IR_SendNEC(unsigned long code)
{
    unsigned char i;

    /* reverse code for LSB */
    code = MSC_ReverseLong(code);

	/* make sure that the first cycle is fresh */
	PWM_ResetTBClock();

    /* send header sync pulse */
    IR_LEDModulePins(TRUE);
    MSC_DelayUS(9000);
    IR_LEDModulePins(FALSE);
    MSC_DelayUS(4500);
    for(i=0; i<32;i++)
    {
        if(code & 0x00000001)
        {
            /* send logical 1 */
        	IR_LEDModulePins(TRUE);
            MSC_DelayUS(563);
            IR_LEDModulePins(FALSE);
            MSC_DelayUS(1686);
        }
        else
        {
            /* send logical 0 */
        	IR_LEDModulePins(TRUE);
            MSC_DelayUS(563);
            IR_LEDModulePins(FALSE);
            MSC_DelayUS(563);
        }
        code >>= 1;
    }

    /* final burst */
    IR_LEDModulePins(TRUE);
    MSC_DelayUS(563);
    IR_LEDModulePins(FALSE);
    MSC_DelayUS(40500);
}

/******************************************************************************/
/* IR_SendNEC
 *
 * The function sends the NEC code and a repeat.							  */
/******************************************************************************/
void IR_SendNECWithRepeat(unsigned long NEC)
{
    IR_SendNEC(NEC);
    IR_SendNECRepeat();
}

/******************************************************************************/
/* IR_CMDCheckMatch
 *
 * This function checks for a description match and returns the index of the
 *  IR coded.																  */
/******************************************************************************/
unsigned char IR_CMDCheckMatch(unsigned char* received, const NECTYPE* codes, unsigned char* match)
{
    unsigned char i,j;
    unsigned char* buffer;
    unsigned char numbercodes;

    if(codes == Sanyo)
    {
    	numbercodes = NumSanyo;
    }
    else if(codes == Visio)
    {
    	numbercodes = NumVisio;
    }
    else if(codes == Idylis)
    {
    	numbercodes = NumIdylis;
    }

    for(j=0;j<numbercodes;j++)
    {
        buffer = received;
        for(i=0;i<LARGEST_DESCRIPTION;i++)
        {
        	if(MSC_LowercaseChar(codes[j].Description[i]) != ' ')
        	{
        		/* eat spaces in command */
        		while(MSC_LowercaseChar(*buffer) == ' ')
        		{
        			/* eat spaces in receive buffer */
        			buffer++;
        		}
        		if((MSC_LowercaseChar(*buffer) == MSC_LowercaseChar(codes[j].Description[i])) || (codes[j].Description[i] == 0))
				{
					if(codes[j].Description[i] == 0)
					{
						/* Found a match, now check to make sure that a CR LN follows */
						if(*buffer == 0)
						{
							/* we have a match */
							*match = j;
							return PASS;
						}
						else
						{
							break;
						}
					}
					buffer++;
				}
				else
				{
					break;
				}
        	}
        }
    }
    return FAIL;
}
/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
