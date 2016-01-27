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
volatile unsigned int RX_C_Buffer_Place = 0;
unsigned char RX_A_Buffer[UART_A_RECEIVE_SIZE];
unsigned char RX_C_Buffer[UART_C_RECEIVE_SIZE];
unsigned char TX_A_Buffer[UART_A_TRANSMIT_SIZE];
unsigned char TX_C_Buffer[UART_C_TRANSMIT_SIZE];
volatile int TX_A_Buffer_ADD_Place = 0;
volatile int TX_C_Buffer_ADD_Place = 0;
volatile int TX_A_Buffer_REMOVE_Place = 0;
volatile int TX_C_Buffer_REMOVE_Place = 0;

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
	InitUART_A(); 	// used for FTDI
	InitUART_C(); 	// used for BLUETOOTH
}

/******************************************************************************/
/* InitUART_A
 *
 * The function initializes the UART SCIA module.							  */
/******************************************************************************/
void InitUART_A(void)
{
	/* Set UART ISRs */
	SYS_Unlock();
	PieVectTable.SCIA_RX_INT = &ISR_UART_A_RX;
	PieVectTable.SCIA_TX_INT = &ISR_UART_A_TX;
	SYS_Lock();

	SYS_EnableInterruptGroup(INTERRUPT_GROUP9);	// Group for UART
	SciaRegs.SCIFFTX.bit.SCIRST = 1; 	// take transmitter out of reset
    UART_SetParametersA(115200, 1, PARITY_NONE);   // set the Baud rate, stop bits, and parity bit
    UART_SetFIFOA(OFF);
    UART_SetFIFOA(ON);
    UART_ReceiveInterruptA(ON);         // enable the receive interrupt
    UART_TransmitInterruptA(OFF);       // disable the receive interrupt
    UART_ReceiveEnableA(ON);
    UART_TransmitEnableA(ON);
	UART_ModulePinsA(TRUE);
    UART_ModuleEnableA(ON);
}

/******************************************************************************/
/* InitUART_C
 *
 * The function initializes the UART SCIC module.							  */
/******************************************************************************/
void InitUART_C(void)
{
	/* Set UART ISRs */
	SYS_Unlock();
	PieVectTable.SCIC_RX_INT = &ISR_UART_C_RX;
	PieVectTable.SCIC_TX_INT = &ISR_UART_C_TX;
	SYS_Lock();

	SYS_EnableInterruptGroup(INTERRUPT_GROUP8);	// Group for UART
	ScicRegs.SCIFFTX.bit.SCIRST = 1; 	// take transmitter out of reset
    UART_SetParametersC(115200, 1, PARITY_NONE);   // set the Baud rate, stop bits, and parity bit
    UART_SetFIFOC(OFF);
    UART_SetFIFOC(ON);
    UART_ReceiveInterruptC(ON);         // enable the receive interrupt
    UART_TransmitInterruptC(OFF);       // disable the receive interrupt
    UART_ReceiveEnableC(ON);
    UART_TransmitEnableC(ON);
	UART_ModulePinsC(TRUE);
    UART_ModuleEnableC(ON);
}

/******************************************************************************/
/* UART_SetParametersA
 *
 * The function sets up the UART parameters baud rate, stop its, and parity.  */
/******************************************************************************/
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
/* UART_SetParametersC
 *
 * The function sets up the UART parameters baud rate, stop its, and parity.  */
/******************************************************************************/
void UART_SetParametersC(unsigned long Baud, unsigned char stop, ENUM_PARITY parity)
{
	unsigned short BRR;

	if(stop == 1)
	{
		/* 1 stop bit */
		ScicRegs.SCICCR.bit.STOPBITS = 0;
	}
	else
	{
		/* 2 stop bit */
		ScicRegs.SCICCR.bit.STOPBITS = 1;
	}

	if(parity == PARITY_NONE)
	{
		/* parity is disabled */
		ScicRegs.SCICCR.bit.PARITYENA = 0;
	}
	else
	{
		/* parity is enabled */
		ScicRegs.SCICCR.bit.PARITYENA = 1;
		if(parity == PARITY_EVEN)
		{
			/* parity is even */
			ScicRegs.SCICCR.bit.PARITY = 1;
		}
		else
		{
			/* parity is odd */
			ScicRegs.SCICCR.bit.PARITY = 0;
		}
	}

	ScicRegs.SCICCR.bit.SCICHAR = 0x7; // data is 8 bits

	BRR = (unsigned long) MSC_Round((double)LSPCLK / ((double)Baud * 8.0) - 1.0);
	ScicRegs.SCIHBAUD.bit.BAUD = (BRR >> 8);
	ScicRegs.SCILBAUD.bit.BAUD = (BRR & 0x00FF);
}


/******************************************************************************/
/* UART_GetFIFOA
 *
 * The function returns TRUE if we are using FIFO mode.						  */
/******************************************************************************/
unsigned char UART_GetFIFOA(void)
{
	if(SciaRegs.SCIFFTX.bit.SCIFFENA == 1)
	{
		return TRUE;
	}
	return FALSE;
}

/******************************************************************************/
/* UART_GetFIFOC
 *
 * The function returns TRUE if we are using FIFO mode.						  */
/******************************************************************************/
unsigned char UART_GetFIFOC(void)
{
	if(ScicRegs.SCIFFTX.bit.SCIFFENA == 1)
	{
		return TRUE;
	}
	return FALSE;
}

/******************************************************************************/
/* UART_SetFIFOA
 *
 * The function controls the UART FIFO for transmitter and receiver.		  */
/******************************************************************************/
void UART_SetFIFOA(unsigned char state)
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
/* UART_SetFIFOC
 *
 * The function controls the UART FIFO for transmitter and receiver.		  */
/******************************************************************************/
void UART_SetFIFOC(unsigned char state)
{
	if (state)
	{
		/* TX FIFO */
		ScicRegs.SCIFFTX.bit.SCIFFENA = 1;  	// SCI FIFO enhancements are enabled
		ScicRegs.SCIFFTX.bit.TXFIFORESET = 1;  	// Re-enable transmit FIFO operation
		ScicRegs.SCIFFTX.bit.TXFFIL = 0;		// Interrupt when there is nothing in the FIFO
		ScicRegs.SCIFFTX.bit.TXFFIENA = 1;  	// TX FIFO interrupt based on TXFFIL match (less than or equal to) is enabled.

		/* RX FIFO */
		ScicRegs.SCIFFRX.bit.RXFIFORESET = 1;	// Re-enable receive FIFO operation
		ScicRegs.SCIFFRX.bit.RXFFIL = 0;		// Interrupt when there is anything in the FIFO
		ScicRegs.SCIFFRX.bit.RXFFIL = 1;		// Interrupt when there is nothing in the FIFO
		ScicRegs.SCIFFRX.bit.RXFFIENA = 1;  	// RX FIFO interrupt based on RXFFIL match (less than or equal to) is enabled.
	}
	else
	{
		/* TX FIFO */
		ScicRegs.SCIFFTX.bit.SCIFFENA = 0;  	// SCI FIFO enhancements are disabled
		ScicRegs.SCIFFTX.bit.TXFIFORESET = 0;  	// Reset the FIFO pointer to zero and hold in reset
		ScicRegs.SCIFFTX.bit.TXFFIENA = 0;  	// TX FIFO interrupt based on TXFFIL match (less than or equal to) is disabled.

		/* RX FIFO */
		ScicRegs.SCIFFRX.bit.RXFIFORESET = 0;	// Write 0 to reset the FIFO pointer to zero, and hold in reset.
		ScicRegs.SCIFFRX.bit.RXFFIENA = 0;  	// RX FIFO interrupt based on RXFFIL match (less than or equal to) is disabled.
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
/* UART_ModuleEnableC
 *
 * The function controls the UART module.									  */
/******************************************************************************/
void UART_ModuleEnableC(unsigned char state)
{
	if (state)
	{
		ScicRegs.SCICTL1.bit.SWRESET = 1; 	// take module out of reset
	}
	else
	{
		ScicRegs.SCICTL1.bit.SWRESET = 0; 	// put module into reset
	}
}

/******************************************************************************/
/* UART_ReceiveInterruptA
 *
 * The function controls the receive interrupt for the UART module.			  */
/******************************************************************************/
void UART_ReceiveInterruptA(unsigned char state)
{
	SYS_Unlock();
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
	SYS_Lock();
}

/******************************************************************************/
/* UART_ReceiveInterruptC
 *
 * The function controls the receive interrupt for the UART module.			  */
/******************************************************************************/
void UART_ReceiveInterruptC(unsigned char state)
{
	SYS_Unlock();
	if (state)
	{
		PieCtrlRegs.PIEIER8.bit.INTx5 = 1;  	// PIE Group 8, INT5
		ScicRegs.SCICTL2.bit.RXBKINTENA = 1;
	}
	else
	{
		PieCtrlRegs.PIEIER8.bit.INTx5 = 0;  	// PIE Group 8, INT5
		ScicRegs.SCICTL2.bit.RXBKINTENA = 0;
	}
	SYS_Lock();
}

/******************************************************************************/
/* UART_TransmitInterruptA
 *
 * The function controls the transmit interrupt for the UART module.		  */
/******************************************************************************/
void UART_TransmitInterruptA(unsigned char state)
{
	SYS_Unlock();
	if (state)
	{
		PieCtrlRegs.PIEIER9.bit.INTx2 = 1;  	// PIE Group 9, INT2
		SciaRegs.SCICTL2.bit.TXINTENA = 1;
	}
	else
	{
		PieCtrlRegs.PIEIER9.bit.INTx2 = 0;  	// PIE Group 9, INT2
		SciaRegs.SCICTL2.bit.TXINTENA = 0;
	}
	SYS_Lock();
}

/******************************************************************************/
/* UART_TransmitInterruptC
 *
 * The function controls the transmit interrupt for the UART module.		  */
/******************************************************************************/
void UART_TransmitInterruptC(unsigned char state)
{
	SYS_Unlock();
	if (state)
	{
		PieCtrlRegs.PIEIER8.bit.INTx6 = 1;  	// PIE Group 9, INT2
		ScicRegs.SCICTL2.bit.TXINTENA = 1;
	}
	else
	{
		PieCtrlRegs.PIEIER8.bit.INTx6 = 0;  	// PIE Group 9, INT2
		ScicRegs.SCICTL2.bit.TXINTENA = 0;
	}
	SYS_Lock();
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
/* UART_TransmitEnableC
 *
 * The function controls the transmit portion of the module.				  */
/******************************************************************************/
void UART_TransmitEnableC(unsigned char state)
{
	if (state)
	{
		ScicRegs.SCICTL1.bit.TXENA = 1;
	}
	else
	{
		ScicRegs.SCICTL1.bit.TXENA = 0;
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
/* UART_ReceiveEnableC
 *
 * The function controls the receive portion of the module.					  */
/******************************************************************************/
void UART_ReceiveEnableC(unsigned char state)
{
	if (state)
	{
		ScicRegs.SCICTL1.bit.RXENA = 1;
	}
	else
	{
		ScicRegs.SCICTL1.bit.RXENA = 0;
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
		SYS_Unlock();
		/* TX */
		GpioCtrlRegs.GPCGMUX2.bit.GPIO84 	= b01; // set to SCITXDA
		GpioCtrlRegs.GPCMUX2.bit.GPIO84 	= b01; // set to SCITXDA

		/* RX */
		GpioCtrlRegs.GPCGMUX2.bit.GPIO85 	= b01; // set to SCIRXDA
		GpioCtrlRegs.GPCMUX2.bit.GPIO85 	= b01; // set to SCIRXDA
		SYS_Lock();
	}
	else
	{
	    /* Connected to the input of the FTDI UART */
		SYS_WritePin(UART_TX_GPIO, ON);
	    SYS_SetupPinMux(UART_TX_GPIO, GPIO_MUX_CPU1, 0);
		SYS_SetupPinOptions(UART_TX_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);

	    /* Connected to the output of the FTDI UART */
		SYS_SetupPinMux(UART_RX_GPIO, GPIO_MUX_CPU1, 0);
		SYS_SetupPinOptions(UART_RX_GPIO, GPIO_INPUT, GPIO_ASYNC);
	}
}

/******************************************************************************/
/* UART_ModulePinsC
 *
 * The function assigns the pins to either the UART module or to GPIOs.		  */
/******************************************************************************/
void UART_ModulePinsC(unsigned char state)
{
	if(state)
	{
		SYS_Unlock();
		/* TX */
		GpioCtrlRegs.GPCGMUX2.bit.GPIO89 	= b01; // set to SCITXDC
		GpioCtrlRegs.GPCMUX2.bit.GPIO89 	= b10; // set to SCITXDC

		/* RX */
		GpioCtrlRegs.GPCGMUX2.bit.GPIO90 	= b01; // set to SCIRXDC
		GpioCtrlRegs.GPCMUX2.bit.GPIO90 	= b10; // set to SCIRXDC
		SYS_Lock();
	}
	else
	{
	    /* Connected to the input of the HC05 IC */
	    SYS_WritePin(BLUETOOTH_TX_GPIO, ON);
	    SYS_SetupPinMux(BLUETOOTH_TX_GPIO, GPIO_MUX_CPU1, 0);
	    SYS_SetupPinOptions(BLUETOOTH_TX_GPIO, GPIO_OUTPUT, GPIO_PUSHPULL);

	    /* Connected to the output of the HC05 IC */
		SYS_SetupPinMux(BLUETOOTH_RX_GPIO, GPIO_MUX_CPU1, 0);
		SYS_SetupPinOptions(BLUETOOTH_RX_GPIO, GPIO_INPUT, GPIO_ASYNC);
	}
}

/******************************************************************************/
/* UART_PutCharA
 *
 * The function puts a character into the transmit FIFO.					  */
/******************************************************************************/
void UART_PutCharA(unsigned char data)
{
	SciaRegs.SCITXBUF.bit.TXDT = data;
}

/******************************************************************************/
/* UART_PutCharC
 *
 * The function puts a character into the transmit FIFO.					  */
/******************************************************************************/
void UART_PutCharC(unsigned char data)
{
	ScicRegs.SCITXBUF.bit.TXDT = data;
}

/******************************************************************************/
/* UART_GetCharA
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
/* UART_GetCharC
 *
 * The function gets a character from the receive FIFO.						  */
/******************************************************************************/
unsigned char UART_GetCharC(unsigned char* FramingError, unsigned char* ParityError)
{
	unsigned short data;

	data = ScicRegs.SCIRXBUF.all;

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
/* UART_SendCharA
 *
 * The function puts a character into the transmit buffer to be sent.		  */
/******************************************************************************/
void UART_SendCharA(unsigned char data)
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
/* UART_SendCharC
 *
 * The function puts a character into the transmit buffer to be sent.		  */
/******************************************************************************/
void UART_SendCharC(unsigned char data)
{
    if(TX_C_Buffer_REMOVE_Place > TX_C_Buffer_ADD_Place)
    {
        if((TX_C_Buffer_REMOVE_Place - TX_C_Buffer_ADD_Place) == 1)
        {
            /* transmit buffer is full */
            if(ScicRegs.SCICTL1.bit.TXENA)
            {
                /* we are currently in a transmitting cycle */
                while((TX_C_Buffer_REMOVE_Place - TX_C_Buffer_ADD_Place) == 1); // the transmit is happening so wait for the buffer to make space
            }
        }
    }

    if(TX_C_Buffer_ADD_Place > TX_C_Buffer_REMOVE_Place)
    {
        if((TX_C_Buffer_ADD_Place - TX_C_Buffer_REMOVE_Place) == (UART_C_TRANSMIT_SIZE - 1))
        {
            /* transmit buffer is full and wrapped around */
            if(ScicRegs.SCICTL1.bit.TXENA)
            {
                /* we are currently in a transmitting cycle */
                while((TX_C_Buffer_ADD_Place - TX_C_Buffer_REMOVE_Place) == (UART_C_TRANSMIT_SIZE - 1));
            }
        }
    }

    TX_C_Buffer[TX_A_Buffer_ADD_Place] = data;
    TX_C_Buffer_ADD_Place++;

    if(TX_C_Buffer_ADD_Place >= UART_C_TRANSMIT_SIZE)
    {
        TX_C_Buffer_ADD_Place = 0;
    }
    UART_TransmitInterruptC(ON);
}

/******************************************************************************/
/* UART_SendStringA
 *
 * The function puts a string into the transmit buffer to be sent.			  */
/******************************************************************************/
void UART_SendStringA(unsigned char* data)
{
    while(*data != 0)
    {
        UART_SendCharA(*data);
        data++;
    }
}

/******************************************************************************/
/* UART_SendStringC
 *
 * The function puts a string into the transmit buffer to be sent.			  */
/******************************************************************************/
void UART_SendStringC(unsigned char* data)
{
    while(*data != 0)
    {
        UART_SendCharC(*data);
        data++;
    }
}

/******************************************************************************/
/* UART_SendStringCRLNA
 *
 * The function puts a string into the transmit buffer to be sent and then a
 *  new line.																  */
/******************************************************************************/
void UART_SendStringCRLNA(unsigned char* data)
{
	UART_SendStringA(data);
	UART_SendStringA(CRLN);
}

/******************************************************************************/
/* UART_SendStringCRLNC
 *
 * The function puts a string into the transmit buffer to be sent and then a
 *  new line.																  */
/******************************************************************************/
void UART_SendStringCRLNC(unsigned char* data)
{
	UART_SendStringC(data);
	UART_SendStringC(CRLN);
}

/******************************************************************************/
/* UART_SendBannerA
 *
 * The function puts the banner into the transmit buffer.					  */
/******************************************************************************/
void UART_SendBannerA(void)
{
	UART_SendStringCRLNA("");
	UART_SendStringCRLNA("");
	UART_SendStringCRLNA(PROJECT_NAME);
	UART_SendStringA("Firmware version: ");
	UART_SendStringCRLNA(FIRMWARE_VERSION);
	UART_SendStringCRLNA(COPYWRITE_MESSAGE);
	UART_SendStringCRLNA("");
	UART_SendStringCRLNA("");
}

/******************************************************************************/
/* UART_SendBannerC
 *
 * The function puts the banner into the transmit buffer.					  */
/******************************************************************************/
void UART_SendBannerC(void)
{
	UART_SendStringCRLNC("");
	UART_SendStringCRLNC("");
	UART_SendStringCRLNC(PROJECT_NAME);
	UART_SendStringC("Firmware version: ");
	UART_SendStringCRLNC(FIRMWARE_VERSION);
	UART_SendStringCRLNC(COPYWRITE_MESSAGE);
	UART_SendStringCRLNC("");
	UART_SendStringCRLNC("");
}


/******************************************************************************/
/* UART_SendPromptA
 *
 * The function prints the prompt.											  */
/******************************************************************************/
void UART_SendPromptA(void)
{
	UART_SendStringA("> ");
}

/******************************************************************************/
/* UART_SendPromptC
 *
 * The function prints the prompt.											  */
/******************************************************************************/
void UART_SendPromptC(void)
{
	UART_SendStringC("> ");
}

/******************************************************************************/
/* UART_ProcessCharacterA
 *
 * The function processes the received character.							  */
/******************************************************************************/
void UART_ProcessCharacterA(unsigned char data)
{
	if((data == LN))
	{
		/* dont do anything with line feeds */
		NOP();
	}
	else if(data == BACKSPACE || data == DELETE)
	{
		if(RX_A_Buffer_Place > 0)
		{
			UART_SendCharA(BACKSPACE);
			UART_SendCharA(SPACE);
			UART_SendCharA(BACKSPACE);
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
			UART_SendStringCRLNA("");
			if(RX_A_Buffer_Place <= (LARGEST_COMMAND_WITH_EXTRA - 1))
			{
				MSC_StringCopy(RX_A_Buffer, CommandStringA);
				CMD_SetNewCommandFlagA(TRUE);
			}
			else
			{
				UART_SendStringCRLNA(BAD_COMMAND);
				UART_SendPromptA();
			}
		}
		else
		{
			UART_SendStringCRLNA("");
			UART_SendPromptA();
		}
	}
	else if(MSC_IsPrintable(data))
	{
		UART_SendCharA(data);
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

/******************************************************************************/
/* UART_ProcessCharacterC
 *
 * The function processes the received character.							  */
/******************************************************************************/
void UART_ProcessCharacterC(unsigned char data)
{
	if((data == LN))
	{
		/* dont do anything with line feeds */
		NOP();
	}
	else if(data == BACKSPACE || data == DELETE)
	{
		if(RX_C_Buffer_Place > 0)
		{
			UART_SendCharC(BACKSPACE);
			UART_SendCharC(SPACE);
			UART_SendCharC(BACKSPACE);
			RX_C_Buffer_Place--;
			RX_C_Buffer[RX_A_Buffer_Place] = 0;
		}
	}
	else if(data == CR)
	{
		if(RX_C_Buffer_Place > 0)
		{
			RX_C_Buffer[RX_A_Buffer_Place] = 0;
			RX_C_Buffer_Place = 0;
			UART_SendStringCRLNC("");
			if(RX_C_Buffer_Place <= (LARGEST_COMMAND_WITH_EXTRA - 1))
			{
				MSC_StringCopy(RX_C_Buffer, CommandStringC);
				CMD_SetNewCommandFlagC(TRUE);
			}
			else
			{
				UART_SendStringCRLNC(BAD_COMMAND);
				UART_SendPromptC();
			}
		}
		else
		{
			UART_SendStringCRLNC("");
			UART_SendPromptC();
		}
	}
	else if(MSC_IsPrintable(data))
	{
		UART_SendCharC(data);
		if(RX_C_Buffer_Place < (UART_C_RECEIVE_SIZE - 1))
		{
			RX_C_Buffer[RX_C_Buffer_Place] = data;
			RX_C_Buffer_Place++;
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
