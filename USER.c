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

#include "CMD.h"
#include "LED.h"
#include "SYSTEM.h"
#include "UART.h"
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
    GPIO_SetupPinMux(RED_LED_GPIO, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(RED_LED_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);

    /* Green LED */
    GPIO_SetupPinMux(GREEN_LED_GPIO, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(GREEN_LED_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);

    /************* Zero_cross Optocoupler *************/
    /* optocoupler */
    GPIO_SetupPinMux(ZEROCROSS_GPIO, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(ZEROCROSS_GPIO, GPIO_INPUT, GPIO_NONE);

    /************* IR Communications *************/
    /* Connected to the MOSFET controllng the IR LED */
    /* optocoupler */
    GPIO_SetupPinMux(IR_LED_GPIO, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(IR_LED_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);

    /* Connected to the output of the IR receiver */
    GPIO_SetupPinMux(IR_RECEIVER_GPIO, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(IR_RECEIVER_GPIO, GPIO_INPUT, GPIO_NONE);

    /************* Relays *************/
    /* Connected to the Solid State Relay */
    GPIO_SetupPinMux(SS_RELAY_GPIO, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(SS_RELAY_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);

    /* Connected to the Mechanical Relay */
    GPIO_SetupPinMux(MECH_RELAY_GPIO, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(MECH_RELAY_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);

    /************* Pushbutton *************/
    /* Connected to the pushbutton switch */
    GPIO_SetupPinMux(PUSHBUTTON_GPIO, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(PUSHBUTTON_GPIO, GPIO_INPUT, GPIO_NONE);

    /************* Audio *************/
    /* Nothing to do for analog pins */

    /************* UART over USB *************/
    /* Connected to the input of the FTDI UART */
    GPIO_WritePin(UART_TX_GPIO, ON);
    GPIO_SetupPinMux(UART_TX_GPIO, GPIO_MUX_CPU1, 0);
	GPIO_SetupPinOptions(UART_TX_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);

    /* Connected to the output of the FTDI UART */
    GPIO_SetupPinMux(UART_RX_GPIO, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(UART_RX_GPIO, GPIO_INPUT, GPIO_ASYNC);
}

/******************************************************************************/
/* Init_Modules
 *
 * The function initializes the modules.									  */
/******************************************************************************/
void Init_Modules(void)
{
	IER |= INTERRUPT_GROUP9; // Enable CPU INT for group 9 (UART)
	InitCMD();
	InitLEDs();
	InitUART();
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
