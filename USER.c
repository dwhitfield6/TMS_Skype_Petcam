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

#include "ADC.h"
#include "AUDIO.h"
#include "BUTTON.h"
#include "CMD.h"
#include "IR.h"
#include "LED.h"
#include "PWM.h"
#include "RELAY.h"
#include "SYSTEM.h"
#include "TIMERS.h"
#include "TV.h"
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
    volatile unsigned long *gpioBaseAddr;
    unsigned short regOffset;

    /* Disable pin locks */
    SYS_Unlock();
    GpioCtrlRegs.GPALOCK.all = 0x00000000;
    GpioCtrlRegs.GPBLOCK.all = 0x00000000;
    GpioCtrlRegs.GPCLOCK.all = 0x00000000;
    GpioCtrlRegs.GPDLOCK.all = 0x00000000;
    GpioCtrlRegs.GPELOCK.all = 0x00000000;
    GpioCtrlRegs.GPFLOCK.all = 0x00000000;

    /*
     * Fill all registers with zeros. Writing to each register separately for six
     *  GPIO modules would make this function *very* long. Fortunately, we'd be
     *  writing them all with zeros anyway, so this saves a lot of space.
     */
    gpioBaseAddr = (Uint32 *)&GpioCtrlRegs;
    for (regOffset = 0; regOffset < sizeof(GpioCtrlRegs)/2; regOffset++)
    {
        /*
         * Hack to avoid enabling pull-ups on all pins. GPyPUD is offset 0x0C in
         *  each register group of 0x40 words. Since this is a 32-bit pointer,
         *  the addresses must be divided by 2.
         */
        if (regOffset % (0x40/2) != (0x0C/2))
        {
            gpioBaseAddr[regOffset] = 0x00000000;
        }
    }

    gpioBaseAddr = (Uint32 *)&GpioDataRegs;
    for (regOffset = 0; regOffset < sizeof(GpioDataRegs)/2; regOffset++)
    {
        gpioBaseAddr[regOffset] = 0x00000000;
    }

    SYS_Lock();

    /*~~~~~~~~~~~~~~~~~~~ Pin setup ~~~~~~~~~~~~~~~~~~~*/

    /************* LEDs *************/
    /* Red LED */
    SYS_SetupPinMux(RED_LED_GPIO, GPIO_MUX_CPU1, 0);
    SYS_SetupPinOptions(RED_LED_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);

    /* Green LED */
    SYS_SetupPinMux(GREEN_LED_GPIO, GPIO_MUX_CPU1, 0);
    SYS_SetupPinOptions(GREEN_LED_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);

    /************* Zero_cross Optocoupler *************/
    /* optocoupler */
    SYS_SetupPinMux(ZEROCROSS_GPIO, GPIO_MUX_CPU1, 0);
    SYS_SetupPinOptions(ZEROCROSS_GPIO, GPIO_INPUT, GPIO_NONE);

    /************* IR Communications *************/
    /* Connected to the MOSFET controlling the IR LED */
    IR_LED(OFF);
    SYS_SetupPinMux(IR_LED_GPIO, GPIO_MUX_CPU1, 0);
    SYS_SetupPinOptions(IR_LED_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);

    /* Connected to the output of the IR receiver */
    SYS_SetupPinMux(IR_RECEIVER_GPIO, GPIO_MUX_CPU1, 0);
    SYS_SetupPinOptions(IR_RECEIVER_GPIO, GPIO_INPUT, GPIO_NONE);

    /************* Relays *************/
    /* Connected to the Solid State Relay */
    RLY_SolidStateRelay(OFF);
    SYS_SetupPinMux(SS_RELAY_GPIO, GPIO_MUX_CPU1, 0);
    SYS_SetupPinOptions(SS_RELAY_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);

    /* Connected to the Mechanical Relay */
	RLY_MechRelay(OFF);
	SYS_SetupPinMux(MECH_RELAY_GPIO, GPIO_MUX_CPU1, 0);
	SYS_SetupPinOptions(MECH_RELAY_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);

    /************* Pushbutton *************/
    /* Connected to the pushbutton switch */
    SYS_SetupPinMux(PUSHBUTTON_GPIO, GPIO_MUX_CPU1, 0);
    SYS_SetupPinOptions(PUSHBUTTON_GPIO, GPIO_INPUT, GPIO_PULLUP);

    /************* Audio *************/
    /* Nothing to do for analog pins */

    /************* UART over USB *************/
    /* Connected to the input of the FTDI UART */
    SYS_WritePin(UART_TX_GPIO, ON);
    SYS_SetupPinMux(UART_TX_GPIO, GPIO_MUX_CPU1, 0);
    SYS_SetupPinOptions(UART_TX_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);

    /* Connected to the output of the FTDI UART */
	SYS_SetupPinMux(UART_RX_GPIO, GPIO_MUX_CPU1, 0);
	SYS_SetupPinOptions(UART_RX_GPIO, GPIO_INPUT, GPIO_ASYNC);
}

/******************************************************************************/
/* Init_Modules
 *
 * The function initializes the modules.									  */
/******************************************************************************/
void Init_Modules(void)
{
	InitTimers();
	InitCMD();
	InitLEDs();
	InitUART();
	InitButtons();
	InitRelay();
	InitPWM();
	InitIR();
	InitADC();
	InitAudio();
	InitTV();
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
