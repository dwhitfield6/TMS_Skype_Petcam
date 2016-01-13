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
/* Contains functions for Universal asynchronous receiver/transmitter
 *  (known as SCI in the TRM).
 *																			  */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include "F2837xS_gpio.h"
#include <stdint.h>
#include <stdbool.h>

#include "CMD.h"
#include "INTERRUPTS.h"
#include "MISC.h"
#include "SYSTEM.h"
#include "UART.h"
#include "USER.h"

/******************************************************************************/
/* Global Variable Declaration 		                                          */
/******************************************************************************/
volatile unsigned int RX_A_Buffer_Place = 0;
unsigned char RX_A_Buffer[UART_A_RECEIVE_SIZE];
unsigned char TX_A_Buffer[UART_A_TRANSMIT_SIZE];
volatile int TX_A_Buffer_ADD_Place = 0;
volatile int TX_A_Buffer_REMOVE_Place = 0;

/******************************************************************************/
/* Inline Functions															  */
/******************************************************************************/

/******************************************************************************/
/* Functions																  */
/******************************************************************************/

/******************************************************************************/
/* InitUART
 *
 * The function initializes the UART module.								  */
/******************************************************************************/
void InitUART(void)
{
	InitUART_A();
}

/******************************************************************************/
/* InitUART_A
 *
 * The function initializes the UART SCIA module.							  */
/******************************************************************************/
void InitUART_A(void)
{
	EALLOW;  // This is needed to write to EALLOW protected registers
	PieVectTable.SCIA_RX_INT = &ISR_UART_A_RX;
	PieVectTable.SCIA_TX_INT = &ISR_UART_A_TX;
	EDIS;   // This is needed to disable write to EALLOW protected registers

	SciaRegs.SCIFFTX.bit.SCIRST = 1; 	// take transmitter out of reset
    UART_SetParametersA(115200, 1, PARITY_NONE);   // set the Baud rate, stop bits, and parity bit
    UART_SetFIFO(OFF);
    UART_SetFIFO(ON);
    UART_ReceiveInterruptA(ON);         // enable the receive interrupt
    UART_TransmitInterruptA(OFF);       // disable the receive interrupt
    UART_ReceiveEnableA(ON);
    UART_TransmitEnableA(ON);
	UART_ModulePinsA(TRUE);
    UART_ModuleEnableA(ON);
}

void UART_SetParametersA(unsigned long Baud, unsigned char stop, ENUM_PARITY parity)
{
	unsigned short BRR;

	if(stop == 1)
	{
		/* 1 stop bit */
		SciaRegs.SCICCR.bit.STOPBITS = 0;
	}
	else
	{
		/* 2 stop bit */
		SciaRegs.SCICCR.bit.STOPBITS = 1;
	}

	if(parity == PARITY_NONE)
	{
		/* parity is disabled */
		SciaRegs.SCICCR.bit.PARITYENA = 0;
	}
	else
	{
		/* parity is enabled */
		SciaRegs.SCICCR.bit.PARITYENA = 1;
		if(parity == PARITY_EVEN)
		{
			/* parity is even */
			SciaRegs.SCICCR.bit.PARITY = 1;
		}
		else
		{
			/* parity is odd */
			SciaRegs.SCICCR.bit.PARITY = 0;
		}
	}

	SciaRegs.SCICCR.bit.SCICHAR = 0x7; // data is 8 bits

	BRR = (unsigned long) MSC_Round((double)LSPCLK / ((double)Baud * 8.0) - 1.0);
	SciaRegs.SCIHBAUD.bit.BAUD = (BRR >> 8);
	SciaRegs.SCILBAUD.bit.BAUD = (BRR & 0x00FF);
}


/******************************************************************************/
/* UART_GetFIFO
 *
 * The function returns TRUE if we are using FIFO mode.						  */
/******************************************************************************/
unsigned char UART_GetFIFO(void)
{
	if(SciaRegs.SCIFFTX.bit.SCIFFENA == 1)
	{
		return TRUE;
	}
	return FALSE;
}

/******************************************************************************/
/* UART_SetFIFO
 *
 * The function controls the UART FIFO for transmitter and receiver.		  */
/******************************************************************************/
void UART_SetFIFO(unsigned char state)
{
	if (state)
	{
		/* TX FIFO */
		SciaRegs.SCIFFTX.bit.SCIFFENA = 1;  	// SCI FIFO enhancements are enabled
		SciaRegs.SCIFFTX.bit.TXFIFORESET = 1;  	// Re-enable transmit FIFO operation
		SciaRegs.SCIFFTX.bit.TXFFIL = 0;		// Interrupt when there is nothing in the FIFO
		SciaRegs.SCIFFTX.bit.TXFFIENA = 1;  	// TX FIFO interrupt based on TXFFIL match (less than or equal to) is enabled.

		/* RX FIFO */
		SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;	// Re-enable receive FIFO operation
		SciaRegs.SCIFFRX.bit.RXFFIL = 0;		// Interrupt when there is anything in the FIFO
		SciaRegs.SCIFFRX.bit.RXFFIL = 1;		// Interrupt when there is nothing in the FIFO
		SciaRegs.SCIFFRX.bit.RXFFIENA = 1;  	// RX FIFO interrupt based on RXFFIL match (less than or equal to) is enabled.
	}
	else
	{
		/* TX FIFO */
		SciaRegs.SCIFFTX.bit.SCIFFENA = 0;  	// SCI FIFO enhancements are disabled
		SciaRegs.SCIFFTX.bit.TXFIFORESET = 0;  	// Reset the FIFO pointer to zero and hold in reset
		SciaRegs.SCIFFTX.bit.TXFFIENA = 0;  	// TX FIFO interrupt based on TXFFIL match (less than or equal to) is disabled.

		/* RX FIFO */
		SciaRegs.SCIFFRX.bit.RXFIFORESET = 0;	// Write 0 to reset the FIFO pointer to zero, and hold in reset.
		SciaRegs.SCIFFRX.bit.RXFFIENA = 0;  	// RX FIFO interrupt based on RXFFIL match (less than or equal to) is disabled.
	}
}

/******************************************************************************/
/* UART_ModuleEnableA
 *
 * The function controls the UART module.									  */
/******************************************************************************/
void UART_ModuleEnableA(unsigned char state)
{
	if (state)
	{
		SciaRegs.SCICTL1.bit.SWRESET = 1; 	// take module out of reset
	}
	else
	{
		SciaRegs.SCICTL1.bit.SWRESET = 0; 	// put module into reset
	}
}

/******************************************************************************/
/* UART_ReceiveInterruptA
 *
 * The function controls the receive interrupt for the UART module.			  */
/******************************************************************************/
void UART_ReceiveInterruptA(unsigned char state)
{
	if (state)
	{
		PieCtrlRegs.PIEIER9.bit.INTx1=1;  	// PIE Group 9, INT1
		SciaRegs.SCICTL2.bit.RXBKINTENA = 1;
	}
	else
	{
		PieCtrlRegs.PIEIER9.bit.INTx1=0;  	// PIE Group 9, INT1
		SciaRegs.SCICTL2.bit.RXBKINTENA = 0;
	}
}

/******************************************************************************/
/* UART_TransmitInterruptA
 *
 * The function controls the transmit interrupt for the UART module.		  */
/******************************************************************************/
void UART_TransmitInterruptA(unsigned char state)
{
	if (state)
	{
		PieCtrlRegs.PIEIER9.bit.INTx2=1;  	// PIE Group 9, INT2
		SciaRegs.SCICTL2.bit.TXINTENA = 1;
	}
	else
	{
		PieCtrlRegs.PIEIER9.bit.INTx2=0;  	// PIE Group 9, INT2
		SciaRegs.SCICTL2.bit.TXINTENA = 0;
	}
}

/******************************************************************************/
/* UART_TransmitEnableA
 *
 * The function controls the transmit portion of the module.				  */
/******************************************************************************/
void UART_TransmitEnableA(unsigned char state)
{
	if (state)
	{
		SciaRegs.SCICTL1.bit.TXENA = 1;
	}
	else
	{
		SciaRegs.SCICTL1.bit.TXENA = 0;
	}
}

/******************************************************************************/
/* UART_ReceiveEnableA
 *
 * The function controls the receive portion of the module.					  */
/******************************************************************************/
void UART_ReceiveEnableA(unsigned char state)
{
	if (state)
	{
		SciaRegs.SCICTL1.bit.RXENA = 1;
	}
	else
	{
		SciaRegs.SCICTL1.bit.RXENA = 0;
	}
}

/******************************************************************************/
/* UART_ModulePinsA
 *
 * The function assigns the pins to either the UART module or to GPIOs.		  */
/******************************************************************************/
void UART_ModulePinsA(unsigned char state)
{
	if(state)
	{
		EALLOW;
		/* TX */
		GpioCtrlRegs.GPCGMUX2.bit.GPIO84 	= b01; // set to SCITXDA
		GpioCtrlRegs.GPCMUX2.bit.GPIO84 	= b01; // set to SCITXDA

		/* RX */
		GpioCtrlRegs.GPCGMUX2.bit.GPIO85 	= b01; // set to SCIRXDA
		GpioCtrlRegs.GPCMUX2.bit.GPIO85 	= b01; // set to SCIRXDA
		EDIS;
	}
	else
	{
	    /* Connected to the input of the FTDI UART */
		GPIO_WritePin(UART_TX_GPIO, ON);
	    GPIO_SetupPinMux(UART_TX_GPIO, GPIO_MUX_CPU1, 0);
		GPIO_SetupPinOptions(UART_TX_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);

	    /* Connected to the output of the FTDI UART */
	    GPIO_SetupPinMux(UART_RX_GPIO, GPIO_MUX_CPU1, 0);
	    GPIO_SetupPinOptions(UART_RX_GPIO, GPIO_INPUT, GPIO_ASYNC);
	}
}

/******************************************************************************/
/* UART_PutChar
 *
 * The function puts a character into the transmit FIFO.					  */
/******************************************************************************/
void UART_PutCharA(unsigned char data)
{
	SciaRegs.SCITXBUF.bit.TXDT = data;
}

/******************************************************************************/
/* UART_GetChar
 *
 * The function gets a character from the receive FIFO.						  */
/******************************************************************************/
unsigned char UART_GetCharA(unsigned char* FramingError, unsigned char* ParityError)
{
	unsigned short data;

	data = SciaRegs.SCIRXBUF.all;

	/* check for parity error */
	if(data & 0x4000)
	{
		*ParityError = TRUE;
	}
	else
	{
		*ParityError = FALSE;
	}

	/* check for framing error */
	if(data & 0x8000)
	{
		*FramingError = TRUE;
	}
	else
	{
		*FramingError = FALSE;
	}

	return (unsigned char) data;
}

/******************************************************************************/
/* UART_SendChar
 *
 * The function puts a character into the transmit buffer to be sent.		  */
/******************************************************************************/
void UART_SendChar(unsigned char data)
{
    if(TX_A_Buffer_REMOVE_Place > TX_A_Buffer_ADD_Place)
    {
        if((TX_A_Buffer_REMOVE_Place - TX_A_Buffer_ADD_Place) == 1)
        {
            /* transmit buffer is full */
            if(SciaRegs.SCICTL1.bit.TXENA)
            {
                /* we are currently in a transmitting cycle */
                while((TX_A_Buffer_REMOVE_Place - TX_A_Buffer_ADD_Place) == 1); // the transmit is happening so wait for the buffer to make space
            }
        }
    }

    if(TX_A_Buffer_ADD_Place > TX_A_Buffer_REMOVE_Place)
    {
        if((TX_A_Buffer_ADD_Place - TX_A_Buffer_REMOVE_Place) == (UART_A_TRANSMIT_SIZE - 1))
        {
            /* transmit buffer is full and wrapped around */
            if(SciaRegs.SCICTL1.bit.TXENA)
            {
                /* we are currently in a transmitting cycle */
                while((TX_A_Buffer_ADD_Place - TX_A_Buffer_REMOVE_Place) == (UART_A_TRANSMIT_SIZE - 1));
            }
        }
    }

    TX_A_Buffer[TX_A_Buffer_ADD_Place] = data;
    TX_A_Buffer_ADD_Place++;

    if(TX_A_Buffer_ADD_Place >= UART_A_TRANSMIT_SIZE)
    {
        TX_A_Buffer_ADD_Place = 0;
    }
    UART_TransmitInterruptA(ON);
}

/******************************************************************************/
/* UART_SendString
 *
 * The function puts a string into the transmit buffer to be sent.		  */
/******************************************************************************/
void UART_SendString(unsigned char* data)
{
    while(*data != 0)
    {
        UART_SendChar(*data);
        data++;
    }
}

/******************************************************************************/
/* UART_SendStringCRLN
 *
 * The function puts a string into the transmit buffer to be sent and then a
 *  new line.																  */
/******************************************************************************/
void UART_SendStringCRLN(unsigned char* data)
{
	UART_SendString(data);
	UART_SendString(CRLN);
}

/******************************************************************************/
/* UART_SendBanner
 *
 * The function puts the banner into the trnasmit buffer.					  */
/******************************************************************************/
void UART_SendBanner(void)
{
	UART_SendStringCRLN("");
	UART_SendStringCRLN("");
	UART_SendStringCRLN(PROJECT_NAME);
	UART_SendString("Firmware version: ");
	UART_SendStringCRLN(FIRMWARE_VERSION);
	UART_SendStringCRLN(COPYWRITE_MESSAGE);
	UART_SendStringCRLN("");
	UART_SendStringCRLN("");
}

/******************************************************************************/
/* UART_SendPrompt
 *
 * The function prints the prompt.											  */
/******************************************************************************/
void UART_SendPrompt(void)
{
	UART_SendString("> ");
}

/******************************************************************************/
/* UART_ProcessCharacter
 *
 * The function processes the received character.							  */
/******************************************************************************/
void UART_ProcessCharacter(unsigned char data)
{
	if(data == LN)
	{
		/* dont do anything with line feeds */
		NOP();
	}
	else if(data == BACKSPACE || data == DELETE)
	{
		if(RX_A_Buffer_Place > 0)
		{
			UART_SendChar(BACKSPACE);
			UART_SendChar(SPACE);
			UART_SendChar(BACKSPACE);
			RX_A_Buffer_Place--;
			RX_A_Buffer[RX_A_Buffer_Place] = 0;
		}
	}
	else if(data == CR)
	{
		if(RX_A_Buffer_Place > 0)
		{
			RX_A_Buffer[RX_A_Buffer_Place] = 0;
			RX_A_Buffer_Place = 0;
			UART_SendStringCRLN("");
			if(RX_A_Buffer_Place <= (LARGEST_COMMAND - 1))
			{
				MSC_StringCopy(RX_A_Buffer, CommandString);
				CMD_SetNewCommandFlag(TRUE);
			}
			else
			{
				UART_SendStringCRLN(BAD_COMMAND);
				UART_SendPrompt();
			}
		}
		else
		{
			UART_SendStringCRLN("");
			UART_SendPrompt();
		}
	}
	else if(MSC_IsPrintable(data))
	{
		UART_SendChar(data);
		if(RX_A_Buffer_Place < (UART_A_RECEIVE_SIZE - 1))
		{
			RX_A_Buffer[RX_A_Buffer_Place] = data;
			RX_A_Buffer_Place++;
		}
	}
	else
	{
		/* dont do anything with non-printable characters */
		NOP();
	}
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
