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
/* Interrupt Vector Options
 *
 * PIE1_RESERVED_INT;	// Reserved
 * PIE2_RESERVED_INT;	// Reserved
 * PIE3_RESERVED_INT;	// Reserved
 * PIE4_RESERVED_INT;	// Reserved
 * PIE5_RESERVED_INT;	// Reserved
 * PIE6_RESERVED_INT;	// Reserved
 * PIE7_RESERVED_INT;	// Reserved
 * PIE8_RESERVED_INT;	// Reserved
 * PIE9_RESERVED_INT;	// Reserved
 * PIE10_RESERVED_INT;  // Reserved
 * PIE11_RESERVED_INT;  // Reserved
 * PIE12_RESERVED_INT;  // Reserved
 * PIE13_RESERVED_INT;  // Reserved
 * TIMER1_INT;	   		// CPU Timer 1 Interrupt
 * TIMER2_INT;	        // CPU Timer 2 Interrupt
 * DATALOG_INT;	        // Datalogging Interrupt
 * RTOS_INT;	        // RTOS Interrupt
 * EMU_INT;	            // Emulation Interrupt
 * NMI_INT;	            // Non-Maskable Interrupt
 * ILLEGAL_INT;	        // Illegal Operation Trap
 * USER1_INT;	        // User Defined Trap 1
 * USER2_INT;	        // User Defined Trap 2
 * USER3_INT;	        // User Defined Trap 3
 * USER4_INT;	        // User Defined Trap 4
 * USER5_INT;	        // User Defined Trap 5
 * USER6_INT;	        // User Defined Trap 6
 * USER7_INT;	        // User Defined Trap 7
 * USER8_INT;	        // User Defined Trap 8
 * USER9_INT;	        // User Defined Trap 9
 * USER10_INT;	        // User Defined Trap 10
 * USER11_INT;	        // User Defined Trap 11
 * USER12_INT;	        // User Defined Trap 12
 * ADCA1_INT;	        // 1.1 - ADCA Interrupt 1
 * ADCB1_INT;	        // 1.2 - ADCB Interrupt 1
 * ADCC1_INT;	        // 1.3 - ADCC Interrupt 1
 * XINT1_INT;	        // 1.4 - XINT1 Interrupt
 * XINT2_INT;	        // 1.5 - XINT2 Interrupt
 * ADCD1_INT;	        // 1.6 - ADCD Interrupt 1
 * TIMER0_INT;	        // 1.7 - Timer 0 Interrupt
 * WAKE_INT;	        // 1.8 - Standby and Halt Wakeup Interrupt
 * EPWM1_TZ_INT;	    // 2.1 - ePWM1 Trip Zone Interrupt
 * EPWM2_TZ_INT;	    // 2.2 - ePWM2 Trip Zone Interrupt
 * EPWM3_TZ_INT;	    // 2.3 - ePWM3 Trip Zone Interrupt
 * EPWM4_TZ_INT;	    // 2.4 - ePWM4 Trip Zone Interrupt
 * EPWM5_TZ_INT;	    // 2.5 - ePWM5 Trip Zone Interrupt
 * EPWM6_TZ_INT;	    // 2.6 - ePWM6 Trip Zone Interrupt
 * EPWM7_TZ_INT;	    // 2.7 - ePWM7 Trip Zone Interrupt
 * EPWM8_TZ_INT;	    // 2.8 - ePWM8 Trip Zone Interrupt
 * EPWM1_INT;	        // 3.1 - ePWM1 Interrupt
 * EPWM2_INT;	        // 3.2 - ePWM2 Interrupt
 * EPWM3_INT;	        // 3.3 - ePWM3 Interrupt
 * EPWM4_INT;	        // 3.4 - ePWM4 Interrupt
 * EPWM5_INT;	        // 3.5 - ePWM5 Interrupt
 * EPWM6_INT;	        // 3.6 - ePWM6 Interrupt
 * EPWM7_INT;	        // 3.7 - ePWM7 Interrupt
 * EPWM8_INT;	        // 3.8 - ePWM8 Interrupt
 * ECAP1_INT;	        // 4.1 - eCAP1 Interrupt
 * ECAP2_INT;	        // 4.2 - eCAP2 Interrupt
 * ECAP3_INT;	        // 4.3 - eCAP3 Interrupt
 * ECAP4_INT;	        // 4.4 - eCAP4 Interrupt
 * ECAP5_INT;	        // 4.5 - eCAP5 Interrupt
 * ECAP6_INT;	        // 4.6 - eCAP6 Interrupt
 * PIE14_RESERVED_INT;  // 4.7 - Reserved
 * PIE15_RESERVED_INT;  // 4.8 - Reserved
 * EQEP1_INT;	        // 5.1 - eQEP1 Interrupt
 * EQEP2_INT;	        // 5.2 - eQEP2 Interrupt
 * EQEP3_INT;	        // 5.3 - eQEP3 Interrupt
 * PIE16_RESERVED_INT;  // 5.4 - Reserved
 * PIE17_RESERVED_INT;  // 5.5 - Reserved
 * PIE18_RESERVED_INT;  // 5.6 - Reserved
 * PIE19_RESERVED_INT;  // 5.7 - Reserved
 * PIE20_RESERVED_INT;  // 5.8 - Reserved
 * SPIA_RX_INT;	        // 6.1 - SPIA Receive Interrupt
 * SPIA_TX_INT;	        // 6.2 - SPIA Transmit Interrupt
 * SPIB_RX_INT;	        // 6.3 - SPIB Receive Interrupt
 * SPIB_TX_INT;	        // 6.4 - SPIB Transmit Interrupt
 * MCBSPA_RX_INT;	    // 6.5 - McBSPA Receive Interrupt
 * MCBSPA_TX_INT;	    // 6.6 - McBSPA Transmit Interrupt
 * MCBSPB_RX_INT;	    // 6.7 - McBSPB Receive Interrupt
 * MCBSPB_TX_INT;	    // 6.8 - McBSPB Transmit Interrupt
 * DMA_CH1_INT;	        // 7.1 - DMA Channel 1 Interrupt
 * DMA_CH2_INT;	        // 7.2 - DMA Channel 2 Interrupt
 * DMA_CH3_INT;	        // 7.3 - DMA Channel 3 Interrupt
 * DMA_CH4_INT;	        // 7.4 - DMA Channel 4 Interrupt
 * DMA_CH5_INT;	        // 7.5 - DMA Channel 5 Interrupt
 * DMA_CH6_INT;	        // 7.6 - DMA Channel 6 Interrupt
 * PIE21_RESERVED_INT;  // 7.7 - Reserved
 * PIE22_RESERVED_INT;  // 7.8 - Reserved
 * I2CA_INT;	        // 8.1 - I2CA Interrupt 1
 * I2CA_FIFO_INT;	    // 8.2 - I2CA Interrupt 2
 * I2CB_INT;	        // 8.3 - I2CB Interrupt 1
 * I2CB_FIFO_INT;	    // 8.4 - I2CB Interrupt 2
 * SCIC_RX_INT;	        // 8.5 - SCIC Receive Interrupt
 * SCIC_TX_INT;	        // 8.6 - SCIC Transmit Interrupt
 * SCID_RX_INT;	        // 8.7 - SCID Receive Interrupt
 * SCID_TX_INT;	        // 8.8 - SCID Transmit Interrupt
 * SCIA_RX_INT;	        // 9.1 - SCIA Receive Interrupt
 * SCIA_TX_INT;	        // 9.2 - SCIA Transmit Interrupt
 * SCIB_RX_INT;	        // 9.3 - SCIB Receive Interrupt
 * SCIB_TX_INT;	        // 9.4 - SCIB Transmit Interrupt
 * CANA0_INT;	        // 9.5 - CANA Interrupt 0
 * CANA1_INT;	        // 9.6 - CANA Interrupt 1
 * CANB0_INT;	        // 9.7 - CANB Interrupt 0
 * CANB1_INT;	        // 9.8 - CANB Interrupt 1
 * ADCA_EVT_INT;	    // 10.1 - ADCA Event Interrupt
 * ADCA2_INT;	        // 10.2 - ADCA Interrupt 2
 * ADCA3_INT;	        // 10.3 - ADCA Interrupt 3
 * ADCA4_INT;	        // 10.4 - ADCA Interrupt 4
 * ADCB_EVT_INT;	    // 10.5 - ADCB Event Interrupt
 * ADCB2_INT;	        // 10.6 - ADCB Interrupt 2
 * ADCB3_INT;	        // 10.7 - ADCB Interrupt 3
 * ADCB4_INT;	        // 10.8 - ADCB Interrupt 4
 * CLA1_1_INT;	        // 11.1 - CLA1 Interrupt 1
 * CLA1_2_INT;	        // 11.2 - CLA1 Interrupt 2
 * CLA1_3_INT;	        // 11.3 - CLA1 Interrupt 3
 * CLA1_4_INT;	        // 11.4 - CLA1 Interrupt 4
 * CLA1_5_INT;	        // 11.5 - CLA1 Interrupt 5
 * CLA1_6_INT;	        // 11.6 - CLA1 Interrupt 6
 * CLA1_7_INT;	        // 11.7 - CLA1 Interrupt 7
 * CLA1_8_INT;	        // 11.8 - CLA1 Interrupt 8
 * XINT3_INT;	        // 12.1 - XINT3 Interrupt
 * XINT4_INT;	        // 12.2 - XINT4 Interrupt
 * XINT5_INT;	        // 12.3 - XINT5 Interrupt
 * PIE23_RESERVED_INT;  // 12.4 - Reserved
 * PIE24_RESERVED_INT;  // 12.5 - Reserved
 * VCU_INT;	            // 12.6 - VCU Interrupt
 * FPU_OVERFLOW_INT;	// 12.7 - FPU Overflow Interrupt
 * FPU_UNDERFLOW_INT;	// 12.8 - FPU Underflow Interrupt
 * PIE25_RESERVED_INT;  // 1.9 - Reserved
 * PIE26_RESERVED_INT;  // 1.10 - Reserved
 * PIE27_RESERVED_INT;  // 1.11 - Reserved
 * PIE28_RESERVED_INT;  // 1.12 - Reserved
 * IPC0_INT;	        // 1.13 - IPC Interrupt 0
 * IPC1_INT;	        // 1.14 - IPC Interrupt 1
 * IPC2_INT;	        // 1.15 - IPC Interrupt 2
 * IPC3_INT;	        // 1.16 - IPC Interrupt 3
 * EPWM9_TZ_INT;	    // 2.9 - ePWM9 Trip Zone Interrupt
 * EPWM10_TZ_INT;	    // 2.10 - ePWM10 Trip Zone Interrupt
 * EPWM11_TZ_INT;	    // 2.11 - ePWM11 Trip Zone Interrupt
 * EPWM12_TZ_INT;	    // 2.12 - ePWM12 Trip Zone Interrupt
 * PIE29_RESERVED_INT;  // 2.13 - Reserved
 * PIE30_RESERVED_INT;  // 2.14 - Reserved
 * PIE31_RESERVED_INT;  // 2.15 - Reserved
 * PIE32_RESERVED_INT;  // 2.16 - Reserved
 * EPWM9_INT;	        // 3.9 - ePWM9 Interrupt
 * EPWM10_INT;	        // 3.10 - ePWM10 Interrupt
 * EPWM11_INT;	        // 3.11 - ePWM11 Interrupt
 * EPWM12_INT;	        // 3.12 - ePWM12 Interrupt
 * PIE33_RESERVED_INT;  // 3.13 - Reserved
 * PIE34_RESERVED_INT;  // 3.14 - Reserved
 * PIE35_RESERVED_INT;  // 3.15 - Reserved
 * PIE36_RESERVED_INT;  // 3.16 - Reserved
 * PIE37_RESERVED_INT;  // 4.9 - Reserved
 * PIE38_RESERVED_INT;  // 4.10 - Reserved
 * PIE39_RESERVED_INT;  // 4.11 - Reserved
 * PIE40_RESERVED_INT;  // 4.12 - Reserved
 * PIE41_RESERVED_INT;	// 4.13 - Reserved
 * PIE42_RESERVED_INT;  // 4.14 - Reserved
 * PIE43_RESERVED_INT;  // 4.15 - Reserved
 * PIE44_RESERVED_INT;  // 4.16 - Reserved
 * SD1_INT;	            // 5.9 - SD1 Interrupt
 * SD2_INT;	            // 5.10 - SD2 Interrupt
 * PIE45_RESERVED_INT;  // 5.11 - Reserved
 * PIE46_RESERVED_INT;  // 5.12 - Reserved
 * PIE47_RESERVED_INT;  // 5.13 - Reserved
 * PIE48_RESERVED_INT;  // 5.14 - Reserved
 * PIE49_RESERVED_INT;  // 5.15 - Reserved
 * PIE50_RESERVED_INT;  // 5.16 - Reserved
 * SPIC_RX_INT;	        // 6.9 - SPIC Receive Interrupt
 * SPIC_TX_INT;	        // 6.10 - SPIC Transmit Interrupt
 * PIE51_RESERVED_INT;  // 6.11 - Reserved
 * PIE52_RESERVED_INT;  // 6.12 - Reserved
 * PIE53_RESERVED_INT;  // 6.13 - Reserved
 * PIE54_RESERVED_INT;  // 6.14 - Reserved
 * PIE55_RESERVED_INT;  // 6.15 - Reserved
 * PIE56_RESERVED_INT;  // 6.16 - Reserved
 * PIE57_RESERVED_INT;  // 7.9 - Reserved
 * PIE58_RESERVED_INT;  // 7.10 - Reserved
 * PIE59_RESERVED_INT;  // 7.11 - Reserved
 * PIE60_RESERVED_INT;  // 7.12 - Reserved
 * PIE61_RESERVED_INT;  // 7.13 - Reserved
 * PIE62_RESERVED_INT;  // 7.14 - Reserved
 * PIE63_RESERVED_INT;  // 7.15 - Reserved
 * PIE64_RESERVED_INT;  // 7.16 - Reserved
 * PIE65_RESERVED_INT;  // 8.9 - Reserved
 * PIE66_RESERVED_INT;  // 8.10 - Reserved
 * PIE67_RESERVED_INT;  // 8.11 - Reserved
 * PIE68_RESERVED_INT;  // 8.12 - Reserved
 * PIE69_RESERVED_INT;  // 8.13 - Reserved
 * PIE70_RESERVED_INT;  // 8.14 - Reserved
 * UPPA_INT;	        // 8.15 - uPPA Interrupt
 * PIE71_RESERVED_INT;  // 8.16 - Reserved
 * PIE72_RESERVED_INT;  // 9.9 - Reserved
 * PIE73_RESERVED_INT;  // 9.10 - Reserved
 * PIE74_RESERVED_INT;  // 9.11 - Reserved
 * PIE75_RESERVED_INT;  // 9.12 - Reserved
 * PIE76_RESERVED_INT;  // 9.13 - Reserved
 * PIE77_RESERVED_INT;  // 9.14 - Reserved
 * USBA_INT;	        // 9.15 - USBA Interrupt
 * PIE78_RESERVED_INT;  // 9.16 - Reserved
 * ADCC_EVT_INT;	    // 10.9 - ADCC Event Interrupt
 * ADCC2_INT;	        // 10.10 - ADCC Interrupt 2
 * ADCC3_INT;	        // 10.11 - ADCC Interrupt 3
 * ADCC4_INT;	        // 10.12 - ADCC Interrupt 4
 * ADCD_EVT_INT;	    // 10.13 - ADCD Event Interrupt
 * ADCD2_INT;	        // 10.14 - ADCD Interrupt 2
 * ADCD3_INT;	        // 10.15 - ADCD Interrupt 3
 * ADCD4_INT;	        // 10.16 - ADCD Interrupt 4
 * PIE79_RESERVED_INT;  // 11.9 - Reserved
 * PIE80_RESERVED_INT;  // 11.10 - Reserved
 * PIE81_RESERVED_INT;  // 11.11 - Reserved
 * PIE82_RESERVED_INT;  // 11.12 - Reserved
 * PIE83_RESERVED_INT;  // 11.13 - Reserved
 * PIE84_RESERVED_INT;  // 11.14 - Reserved
 * PIE85_RESERVED_INT;  // 11.15 - Reserved
 * PIE86_RESERVED_INT;  // 11.16 - Reserved
 * EMIF_ERROR_INT;	    // 12.9 - EMIF Error Interrupt
 * RAM_CORRECTABLE_ERROR_INT;	// 12.10 - RAM Correctable Error Interrupt
 * FLASH_CORRECTABLE_ERROR_INT; // 12.11 - Flash Correctable Error Interrupt
 * RAM_ACCESS_VIOLATION_INT;                   // 12.12 - RAM Access Violation Interrupt
 * SYS_PLL_SLIP_INT;	// 12.13 - System PLL Slip Interrupt
 * AUX_PLL_SLIP_INT;	// 12.14 - Auxiliary PLL Slip Interrupt
 * CLA_OVERFLOW_INT;	// 12.15 - CLA Overflow Interrupt
 * CLA_UNDERFLOW_INT;	// 12.16 - CLA Underflow Interrupt
 *                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "ADC.h"
#include "AUDIO.h"
#include "BUTTON.h"
#include "INTERRUPTS.h"
#include "IR.h"
#include "LED.h"
#include "PWM.h"
#include "RELAY.h"
#include "SYSTEM.h"
#include "TIMERS.h"
#include "UART.h"
#include "USER.h"

/******************************************************************************/
/* Global Variables                                                           */
/******************************************************************************/

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/******************************************************************************/
/* UART RX interrupt
 *
 * Used for UART Terminal.                                                    */
/******************************************************************************/
interrupt void ISR_UART_A_RX(void)
{
	unsigned char Framing_Error;
	unsigned char Parity_Error;
	unsigned char data;

	while(SciaRegs.SCIFFRX.bit.RXFFST)
	{
		/* get all of the data out of the FIFO */
		data = UART_GetCharA(&Framing_Error, &Parity_Error);
		if(Framing_Error || Parity_Error)
		{
			/* error occured */
		}
		else
		{
			UART_ProcessCharacter(data);
		}
	}

    SciaRegs.SCIFFRX.bit.RXFFOVRCLR = 1;   // Clear Overflow flag
    SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;   // Clear Interrupt flag

    PieCtrlRegs.PIEACK.all |= INTERRUPT_GROUP9;       // Issue PIE ack
}

/******************************************************************************/
/* UART TX interrupt
 *
 * Used for UART Terminal.                                                    */
/******************************************************************************/
interrupt void ISR_UART_A_TX(void)
{
	if(TX_A_Buffer_REMOVE_Place != TX_A_Buffer_ADD_Place)
	{
		while(SciaRegs.SCIFFTX.bit.TXFFST != 0x10)
		{
			/* Fill the FIFO if we can */
			if(TX_A_Buffer_REMOVE_Place != TX_A_Buffer_ADD_Place)
			{
				UART_PutCharA(TX_A_Buffer[TX_A_Buffer_REMOVE_Place]);
				TX_A_Buffer_REMOVE_Place++;
				if(TX_A_Buffer_REMOVE_Place >= UART_A_TRANSMIT_SIZE)
				{
					TX_A_Buffer_REMOVE_Place = 0;
				}
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		UART_TransmitInterruptA(OFF);
	}

	SciaRegs.SCIFFTX.bit.TXFFINTCLR = 1;  		// Clear SCI Interrupt flag
	PieCtrlRegs.PIEACK.all |= INTERRUPT_GROUP9; // Issue PIE ACK
}

/******************************************************************************/
/* External Interrupt 1
 *
 *	Used for pushbutton.                                                      */
/******************************************************************************/
interrupt void ISR_INT1_BUTTON(void)
{
	BUT_ButtonInterrupt(OFF);
	BUT_SetButtonFlag(TRUE);
	LED_RedLED(OFF);
	LED_GreenLED(ON);

	/* Acknowledge this interrupt from group 1 */
	PieCtrlRegs.PIEACK.all = INTERRUPT_GROUP1;
}

/******************************************************************************/
/* External Interrupt 2
 *
 *	Used for zero cross detection.                                             */
/******************************************************************************/
interrupt void ISR_INT2_ZEROCROSS(void)
{
	/* turn off the relay and set the timer to fire */

	if(RLY_SSRelayDuty == 0)
	{
		TMR_StartTimer2(OFF);
		TMR_Interrupt2(OFF);
		RLY_SolidStateRelay(OFF);
	}
	else if(RLY_SSRelayDuty == 100)
	{
		TMR_StartTimer2(OFF);
		TMR_Interrupt2(OFF);
		RLY_SolidStateRelay(ON);
	}
	else
	{
		RLY_SolidStateRelay(OFF);
		TMR_SetTimerWithPeriod2();
		TMR_Interrupt2(ON);
		TMR_StartTimer2(ON);
	}

	/* Acknowledge this interrupt from group 1 */
	PieCtrlRegs.PIEACK.all = INTERRUPT_GROUP1;
}

/******************************************************************************/
/* External Interrupt 3
 *
 *	Used IR receiver timing.	                                              */
/******************************************************************************/
interrupt void ISR_INT3_IR_RECEIVE(void)
{
	unsigned long microseconds;
	unsigned long counts;
	unsigned char done = FALSE;

	TMR_SetTimer1Mode(IR);
	counts = IR_RECEIVE_COUNTS_TIMEOUT - TMR_GetTimer1();
	microseconds = TMR_CountsToMicroseconds(counts);

	if(TMR_GetStartTimerStatus1())
	{
		/* timer is running */
		if(!IR_NEC_Start)
		{
			if((microseconds >= NEC_HEADER_LOW) && (microseconds <= NEC_HEADER_HIGH))
			{
				/* header was seen so this is the start of an NEC code */
				IR_Receive_Timing_place = 0;
				NEC_REPEAT = FALSE;
				IR_NEC_Start = TRUE;
				IR_Receive_Timing_Counts[IR_Receive_Timing_place] = counts;
				IR_Receive_Timing_MicroSeconds[IR_Receive_Timing_place] = microseconds;
				IR_Receive_Timing_place++;
			}
		}
		else
		{
			if(IR_Receive_Timing_place == 1)
			{
				if((microseconds >= NEC_REPEAT_LOW) && (microseconds <= NEC_REPEAT_HIGH))
				{
					NEC_REPEAT = TRUE;
				}
				else if((microseconds >= NEC_NONREPEAT_LOW) && (microseconds <= NEC_NONREPEAT_HIGH))
				{
					NEC_REPEAT = FALSE;
				}
			}
			if(IR_Receive_Timing_place < MAX_IR_RECEIVE_EVENTS)
			{
				IR_Receive_Timing_Counts[IR_Receive_Timing_place] = counts;
				IR_Receive_Timing_MicroSeconds[IR_Receive_Timing_place] = microseconds;
				IR_Receive_Timing_place++;
			}
			if(NEC_REPEAT)
			{
				if(IR_Receive_Timing_place >= NEC_CODE_EDGES_REPEAT)
				{
					/* This is the end of a repeat code so turn off the timer and external interrupt and process */
					IR_ReceiverInterrupt(OFF);
					IR_SetReceiveFlag();
					done = TRUE;
				}
			}
			else
			{
				if(IR_Receive_Timing_place >= NEC_CODE_EDGES_NONREPEAT)
				{
					/* This is the end of a code so turn off the timer and external interrupt and process */
					IR_SetReceiveFlag();
					done = TRUE;
				}
			}
		}
	}

	/* load and start timer */
	TMR_StartTimer1(FALSE);
	TMR_SetTimerWithPeriod1();
	if(done)
	{
		IR_ReceiverInterrupt(OFF);
		IR_NEC_Start = FALSE;
		TMR_SetTimer1Mode(AUDIO);
	}
	else
	{
		TMR_StartTimer1(TRUE);
	}

	/* Acknowledge this interrupt from group 12 */
	PieCtrlRegs.PIEACK.all = INTERRUPT_GROUP12;
}

/******************************************************************************/
/* Timer 0 interrupt
 *
 * Used for MSC_DelayUS() as a misc. delay.                                   */
/******************************************************************************/
interrupt void ISR_TIMER0_DELAY(void)
{
	TMR_StartTimer0(FALSE);	// stop timer
	TMR_Interrupt0(OFF);
	TMR_SetTimerFlag0();

	/* Acknowledge this interrupt from group 1 */
	PieCtrlRegs.PIEACK.all = INTERRUPT_GROUP1;
}

/******************************************************************************/
/* Timer 1 interrupt
 *
 * Used for IR Receiver timing.				                                  */
/******************************************************************************/
interrupt void ISR_TIMER1_IR_RECEIVE(void)
{
	/* IR receiver timout */
	IR_NEC_Start = FALSE;
	TMR_StartTimer1(FALSE);
	TMR_SetTimerWithPeriod1();
}

/******************************************************************************/
/* Timer 2 interrupt
 *
 * Used for Solid state relay dimming.		                                  */
/******************************************************************************/
interrupt void ISR_TIMER2_SS_Relay(void)
{
	RLY_SolidStateRelay(ON);
	TMR_StartTimer2(OFF);
	TMR_Interrupt2(OFF);
}

/******************************************************************************/
/* ePWM 8
 *
 * Used for IR LED.							                                  */
/******************************************************************************/
interrupt void ISR_EPWM_8_IRLED(void)
{
	//PWM_Interrupt1(OFF);
	EPwm8Regs.CMPB.bit.CMPB = PWM_GetCMPB();	// update Compare A value

    /* Clear INT flag for this timer */
    EPwm8Regs.ETCLR.bit.INT = 1;

	/* Acknowledge this interrupt from group 3 */
	PieCtrlRegs.PIEACK.all = INTERRUPT_GROUP3;
}

/******************************************************************************/
/* ADC A1
 *
 * Used for audio sampling.					                                  */
/******************************************************************************/
interrupt void ISR_ADC_AUDIO(void)
{
	unsigned short ADC_counts0;
	unsigned short ADC_counts1;

	AUD_Sampling(OFF);

	/* ADC unfiltered audio sampling */
	ADC_counts0 = AdcaResultRegs.ADCRESULT0;
	if(Audio_ADC_Counts_Unfiltered_place < AUDIO_ADC_BUFFER_SIZE)
	{
		Audio_ADC_Counts_Unfiltered_Buffer[Audio_ADC_Counts_Unfiltered_place] = ADC_counts0;
		Audio_ADC_Counts_Unfiltered_place++;
	}

	/* ADC low-pass filtered audio sampling */
	ADC_counts1 = AdcaResultRegs.ADCRESULT1;
	if(TMR_GetTimer1Mode() == AUDIO)
	{
		Audio_ADC_Counts_LowPass_Buffer[Audio_ADC_Counts_LowPass_place].ADC = ADC_counts1;
		Audio_ADC_Counts_LowPass_Buffer[Audio_ADC_Counts_LowPass_place].TimingCounts	= TMR_GetTimer1();
		Audio_ADC_Counts_LowPass_place++;

		TMR_StartTimer1(FALSE);
		TMR_SetTimerWithPeriod1();
		TMR_StartTimer1(TRUE);
	}

	AUD_SetSampleReadyFlag();

	AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
	PieCtrlRegs.PIEACK.all = INTERRUPT_GROUP1;
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
