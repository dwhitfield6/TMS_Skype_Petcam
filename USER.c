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
/* Contains Functions for TMS320 initialization.
 *																			  */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "USER.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/* Inline Functions															  */
/******************************************************************************/

/******************************************************************************/
/* Functions																  */
/******************************************************************************/

/******************************************************************************/
/* Init_Pins
 *
 * The function initializes the gpio pins. Sets all pins to be muxed to GPIO
 *  in input mode with pull-ups enabled. Also disables open drain and polarity
 *  inversion and sets the qualification to synchronous. Also unlocks all
 *  GPIOs.																	  */
/******************************************************************************/
void Init_Pins(void)
{
    volatile Uint32 *gpioBaseAddr;

    /*~~~~~~~~~~~~~~~~~ initialization ~~~~~~~~~~~~~~~~~*/
    Uint16 regOffset;

    //Disable pin locks
    EALLOW;
    GpioCtrlRegs.GPALOCK.all = 0x00000000;
    GpioCtrlRegs.GPBLOCK.all = 0x00000000;
    GpioCtrlRegs.GPCLOCK.all = 0x00000000;
    GpioCtrlRegs.GPDLOCK.all = 0x00000000;
    GpioCtrlRegs.GPELOCK.all = 0x00000000;
    GpioCtrlRegs.GPFLOCK.all = 0x00000000;

    //Fill all registers with zeros. Writing to each register separately
    //for six GPIO modules would make this function *very* long. Fortunately,
    //we'd be writing them all with zeros anyway, so this saves a lot of space.
    gpioBaseAddr = (Uint32 *)&GpioCtrlRegs;
    for (regOffset = 0; regOffset < sizeof(GpioCtrlRegs)/2; regOffset++)
    {
        //Hack to avoid enabling pull-ups on all pins. GPyPUD is offset
        //0x0C in each register group of 0x40 words. Since this is a
        //32-bit pointer, the addresses must be divided by 2.
        if (regOffset % (0x40/2) != (0x0C/2))
            gpioBaseAddr[regOffset] = 0x00000000;
    }

    gpioBaseAddr = (Uint32 *)&GpioDataRegs;
    for (regOffset = 0; regOffset < sizeof(GpioDataRegs)/2; regOffset++)
    {
        gpioBaseAddr[regOffset] = 0x00000000;
    }

    EDIS;

    /*~~~~~~~~~~~~~~~~~~~ Pin setup ~~~~~~~~~~~~~~~~~~~*/

    /************* LEDs *************/
    /* Red LED */
    GPIO_SetupPinMux(REDLED_GPIO, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(REDLED_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);

    /* Blue LED */
    GPIO_SetupPinMux(BLUELED_GPIO, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(BLUELED_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);

}

/******************************************************************************/
/* Init_Modules
 *
 * The function initializes the modules.									  */
/******************************************************************************/
void Init_Modules(void)
{

}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
