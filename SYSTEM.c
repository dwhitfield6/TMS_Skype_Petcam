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
/* Contains system functions.
 *																			  */
/******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "MISC.h"
#include "SYSTEM.h"

/******************************************************************************/
/* Global Variable Declaration 		                                          */
/******************************************************************************/
unsigned long PLLSYSCLK = 0;
unsigned long EPWMCLK = 0;
unsigned long SYSCLK = 0;
unsigned long LSPCLK = 0;

#if CPU_FRQ_200MHZ
unsigned long CPU_FREQ = 200000000;
#endif

#if CPU_FRQ_150MHZ
unsigned long CPU_FREQ = 150000000;
#endif

#if CPU_FRQ_120MHZ
unsigned long CPU_FREQ = 120000000;
#endif

/******************************************************************************/
/* Functions																  */
/******************************************************************************/

/******************************************************************************/
/* SYS_ConfigureOscillator
 *
 * The function waits for the high frequency oscillator to be working and
 *  stable.																	  */
/******************************************************************************/
void SYS_ConfigureOscillator(void)
{    
	SYS_DisableWatchdog();

#ifdef _FLASH
	/*
	 * Copy time critical code and Flash setup code to RAM. This includes the
	 *  following functions:  InitFlash(); The  RamfuncsLoadStart, RamfuncsLoadSize, and RamfuncsRunStart
	 *  symbols are created by the linker. Refer to the device .cmd file.
	 */
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);

    /* Call Flash Initialization to setup flash waitstates. This function must reside in RAM */
    SYS_InitFlash_Bank0();
#endif

    SYS_Unlock();
   	CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
   	CpuSysRegs.PCLKCR13.bit.ADC_B = 1;
   	CpuSysRegs.PCLKCR13.bit.ADC_C = 1;
   	CpuSysRegs.PCLKCR13.bit.ADC_D = 1;

	//check if device is trimmed
	if(*((Uint16 *)0x5D1B6) == 0x0000)
	{
	   //device is not trimmed, apply static calibration values
	   AnalogSubsysRegs.ANAREFTRIMA.all = 31709;
	   AnalogSubsysRegs.ANAREFTRIMB.all = 31709;
	   AnalogSubsysRegs.ANAREFTRIMC.all = 31709;
	   AnalogSubsysRegs.ANAREFTRIMD.all = 31709;
	}

   	CpuSysRegs.PCLKCR13.bit.ADC_A = 0;
   	CpuSysRegs.PCLKCR13.bit.ADC_B = 0;
   	CpuSysRegs.PCLKCR13.bit.ADC_C = 0;
   	CpuSysRegs.PCLKCR13.bit.ADC_D = 0;
   	SYS_Lock();

   	/* configure the PLL */
   	SYS_InitSysPll(XTAL_OSC,IMULT_40,FMULT_0,PLLCLK_BY_2); 		//PLLSYSCLK = (XTAL_OSC) * (IMULT + FMULT) / (PLLSYSCLKDIV)

	/* Turn on all peripherals */
   	SYS_InitPeripheralClocks();

	/* Calculate Clock variables */
   	PLLSYSCLK = CPU_FREQ;
	SYSCLK = PLLSYSCLK;

	/* Calculate clocks for globals */
	SYS_Unlock();
	ClkCfgRegs.LOSPCP.bit.LSPCLKDIV = b010; // SYSCLK / 4
	LSPCLK = SYSCLK / 4;

	ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 0; 	// x0 = /1 of PLLSYSCLK
	EPWMCLK = PLLSYSCLK;
	SYS_Lock();

}

/******************************************************************************/
/* SYS_InitPeripheralClocks
 *
 * The function initializes the clocks for the peripherals					  */
/******************************************************************************/
void SYS_InitPeripheralClocks(void)
{
	SYS_Unlock();

	CpuSysRegs.PCLKCR0.bit.CLA1 = 1;
	CpuSysRegs.PCLKCR0.bit.DMA = 1;
	CpuSysRegs.PCLKCR0.bit.CPUTIMER0 = 1;
	CpuSysRegs.PCLKCR0.bit.CPUTIMER1 = 1;
	CpuSysRegs.PCLKCR0.bit.CPUTIMER2 = 1;
	CpuSysRegs.PCLKCR0.bit.HRPWM = 1;
	CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;

	CpuSysRegs.PCLKCR1.bit.EMIF1 = 1;
	CpuSysRegs.PCLKCR1.bit.EMIF2 = 1;

	CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM2 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM3 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM4 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM5 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM6 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM7 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM8 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM9 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM10 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM11 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM12 = 1;

	CpuSysRegs.PCLKCR3.bit.ECAP1 = 1;
	CpuSysRegs.PCLKCR3.bit.ECAP2 = 1;
	CpuSysRegs.PCLKCR3.bit.ECAP3 = 1;
	CpuSysRegs.PCLKCR3.bit.ECAP4 = 1;
	CpuSysRegs.PCLKCR3.bit.ECAP5 = 1;
	CpuSysRegs.PCLKCR3.bit.ECAP6 = 1;

	CpuSysRegs.PCLKCR4.bit.EQEP1 = 1;
	CpuSysRegs.PCLKCR4.bit.EQEP2 = 1;
	CpuSysRegs.PCLKCR4.bit.EQEP3 = 1;

	CpuSysRegs.PCLKCR6.bit.SD1 = 1;
	CpuSysRegs.PCLKCR6.bit.SD2 = 1;

	CpuSysRegs.PCLKCR7.bit.SCI_A = 1;
	CpuSysRegs.PCLKCR7.bit.SCI_B = 1;
	CpuSysRegs.PCLKCR7.bit.SCI_C = 1;
	CpuSysRegs.PCLKCR7.bit.SCI_D = 1;

	CpuSysRegs.PCLKCR8.bit.SPI_A = 1;
	CpuSysRegs.PCLKCR8.bit.SPI_B = 1;
	CpuSysRegs.PCLKCR8.bit.SPI_C = 1;

	CpuSysRegs.PCLKCR9.bit.I2C_A = 1;
	CpuSysRegs.PCLKCR9.bit.I2C_B = 1;

	CpuSysRegs.PCLKCR10.bit.CAN_A = 1;
	CpuSysRegs.PCLKCR10.bit.CAN_B = 1;

	CpuSysRegs.PCLKCR11.bit.McBSP_A = 1;
	CpuSysRegs.PCLKCR11.bit.McBSP_B = 1;
	CpuSysRegs.PCLKCR11.bit.USB_A = 1;

	CpuSysRegs.PCLKCR12.bit.uPP_A = 1;

	CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
	CpuSysRegs.PCLKCR13.bit.ADC_B = 1;
	CpuSysRegs.PCLKCR13.bit.ADC_C = 1;
	CpuSysRegs.PCLKCR13.bit.ADC_D = 1;

	CpuSysRegs.PCLKCR14.bit.CMPSS1 = 1;
	CpuSysRegs.PCLKCR14.bit.CMPSS2 = 1;
	CpuSysRegs.PCLKCR14.bit.CMPSS3 = 1;
	CpuSysRegs.PCLKCR14.bit.CMPSS4 = 1;
	CpuSysRegs.PCLKCR14.bit.CMPSS5 = 1;
	CpuSysRegs.PCLKCR14.bit.CMPSS6 = 1;
	CpuSysRegs.PCLKCR14.bit.CMPSS7 = 1;
	CpuSysRegs.PCLKCR14.bit.CMPSS8 = 1;

	CpuSysRegs.PCLKCR16.bit.DAC_A = 1;
	CpuSysRegs.PCLKCR16.bit.DAC_B = 1;
	CpuSysRegs.PCLKCR16.bit.DAC_C = 1;

	SYS_Lock();
}

/******************************************************************************/
/* SYS_InitSysPll
 *
 * The function initializes the PLL registers.								  */
/******************************************************************************/
void SYS_InitSysPll(unsigned short clock_source, unsigned short imult, unsigned short fmult, unsigned short divsel)
{
    if((clock_source == ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL)    &&
      (imult         == ClkCfgRegs.SYSPLLMULT.bit.IMULT)           &&
      (fmult         == ClkCfgRegs.SYSPLLMULT.bit.FMULT)           &&
      (divsel        == ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV))
    {
        /* everything is set as required, so just return */
        return;
    }

    if(clock_source != ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL)
    {
        switch (clock_source)
        {
            case INT_OSC1:
                SYS_InitOsc1Sel();
                break;

            case INT_OSC2:
                SYS_InitOsc2Sel();
                break;

            case XTAL_OSC:
            	SYS_InitXtalOscSel();
                break;
        }
    }

    SYS_Unlock();

     /* Modify the PLL multipliers */
    if(imult != ClkCfgRegs.SYSPLLMULT.bit.IMULT || fmult != ClkCfgRegs.SYSPLLMULT.bit.FMULT)
    {
        /* Bypass PLL and set dividers to /1 */
        ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 0;
        ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = 0;

        /* Program PLL multipliers */
        Uint32 temp_syspllmult = ClkCfgRegs.SYSPLLMULT.all;
        ClkCfgRegs.SYSPLLMULT.all = ((temp_syspllmult & ~(0x37FU)) |
                                     ((fmult << 8U) | imult));

        ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 1;            // Enable SYSPLL

        /*
         * Write a multiplier again to ensure proper PLL initialization
         * This will force the PLL to lock a second time
         */
        ClkCfgRegs.SYSPLLMULT.bit.IMULT = imult;        // Setting integer multiplier
    }

    /* Set divider to produce slower output frequency to limit current increase */
    if(divsel != PLLCLK_BY_126)
    {
         ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = divsel + 1;
    }else
    {
         ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = divsel;
    }

    /* Enable PLLSYSCLK is fed from system PLL clock */
    ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 1;

    /* Small 100 cycle delay */
    MSC_DelayNOP(100);

    /* Set the divider to user value */
    ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = divsel;
    SYS_Lock();
}

/******************************************************************************/
/* SYS_InitXtalOscSel
 *
 * This function switches to External CRYSTAL oscillator and turns off all
 *  other clock sources to minimize power consumption. This option may not be
 *  available on all device packages.										  */
/******************************************************************************/
void SYS_InitXtalOscSel(void)
{

	SYS_Unlock();
    ClkCfgRegs.CLKSRCCTL1.bit.XTALOFF=0;        // Turn on XTALOSC
    ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 1; // Clk Src = XTAL
    SYS_Lock();
}

/******************************************************************************/
/* SYS_InitOsc2Sel
 *
 * This function switches to Internal oscillator 2 from External Oscillator
 *  and turns off all other clock sources to minimize power consumption.
 *
 *  NOTE: If there is no external clock connection, when switching from
 *   INTOSC1 to INTOSC2, EXTOSC and XLCKIN must be turned OFF prior to
 *   switching to internal oscillator 1.										  */
/******************************************************************************/
void SYS_InitOsc2Sel(void)
{

	SYS_Unlock();
    ClkCfgRegs.CLKSRCCTL1.bit.INTOSC2OFF=0;     // Turn on INTOSC2
    ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 0; // Clk Src = INTOSC2
    SYS_Lock();
}

/******************************************************************************/
/* SYS_InitOsc1Sel
 *
 * This function switches to Internal oscillator 1 from External Oscillator
 *  and turns off all other clock sources to minimize power consumption.      */
/******************************************************************************/
void SYS_InitOsc1Sel(void)
{

	SYS_Unlock();
	ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 2; // Clk Src = INTOSC1
    SYS_Lock();
}

/******************************************************************************/
/* SYS_InitFlash_Bank0
 *
 * This function initializes the Flash Control registers for Bank0      	  */
/******************************************************************************/
void SYS_InitFlash_Bank0(void)
{
	SYS_Unlock();

    /*
     * Set VREADST to the proper value for the flash banks to power up properly
     * This sets the bank power up delay
     */
    Flash0CtrlRegs.FBAC.bit.VREADST = 0x14;

    /*
     * At reset bank and pump are in sleep. A Flash access will power up the bank
     *  and pump automatically. After a Flash access, bank and pump go to low
     *  power mode (configurable in FBFALLBACK/FPAC1 registers)- if there is no
     *  further access to flash. Power up Flash bank and pump and this also
     *  sets the fall back mode of flash and pump as active.
     */
    Flash0CtrlRegs.FPAC1.bit.PMPPWR = 0x1;
    Flash0CtrlRegs.FBFALLBACK.bit.BNKPWR0 = 0x3;

    /* Disable Cache and prefetch mechanism before changing wait states */
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.DATA_CACHE_EN = 0;
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.PREFETCH_EN = 0;

    /* Set waitstates according to frequency
     *
     * Minimum waitstates required for the flash operating at a given CPU rate
     *  must be characterized by TI. Refer to the datasheet for the latest
     *  information.
     */
    #if CPU_FRQ_200MHZ
    Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x3;
    #endif

    #if CPU_FRQ_150MHZ
    Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x2;
    #endif

    #if CPU_FRQ_120MHZ
    Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x2;
    #endif

    /* Enable Cache and prefetch mechanism to improve performance of code executed from Flash.*/
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.DATA_CACHE_EN = 1;
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.PREFETCH_EN = 1;

    /*
     * At reset, ECC is enabled. If it is disabled by application software and if application
     *  again wants to enable ECC
     */
    Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0xA;

    SYS_Lock();

    /* Flush pipeline */
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
}

/******************************************************************************/
/* SYS_DisableWatchdog
 *
 * The function disables the watch dog.										  */
/******************************************************************************/
void SYS_DisableWatchdog(void)
{
	volatile Uint16 temp;

	SYS_Unlock();

    /* Save the watchdog clock configuration */
    temp = WdRegs.WDCR.all & 0x0007;
    WdRegs.WDCR.all = 0x0068 | temp;
    SYS_Lock();
}

/******************************************************************************/
/* SYS_Interrupts
 *
 * The function controls the interrupts.									  */
/******************************************************************************/
void SYS_Interrupts(unsigned char state)
{
    if(state)
    {
    	__asm(" clrc INTM");
    }
    else
    {
    	__asm(" setc INTM");
    }
}

/******************************************************************************/
/* SYS_ClearPIE
 *
 * The function clears all registers associated with the PIE
 *  (Peripheral interrupts Enable).											  */
/******************************************************************************/
void SYS_ClearPIE(void)
{
    /* Disable the PIE */
    PieCtrlRegs.PIECTRL.bit.ENPIE = 0;

    /* Clear all PIEIER registers */
	PieCtrlRegs.PIEIER1.all = 0;
	PieCtrlRegs.PIEIER2.all = 0;
	PieCtrlRegs.PIEIER3.all = 0;
	PieCtrlRegs.PIEIER4.all = 0;
	PieCtrlRegs.PIEIER5.all = 0;
	PieCtrlRegs.PIEIER6.all = 0;
	PieCtrlRegs.PIEIER7.all = 0;
	PieCtrlRegs.PIEIER8.all = 0;
	PieCtrlRegs.PIEIER9.all = 0;
	PieCtrlRegs.PIEIER10.all = 0;
	PieCtrlRegs.PIEIER11.all = 0;
	PieCtrlRegs.PIEIER12.all = 0;

	/* Clear all PIEIFR registers */
	PieCtrlRegs.PIEIFR1.all = 0;
	PieCtrlRegs.PIEIFR2.all = 0;
	PieCtrlRegs.PIEIFR3.all = 0;
	PieCtrlRegs.PIEIFR4.all = 0;
	PieCtrlRegs.PIEIFR5.all = 0;
	PieCtrlRegs.PIEIFR6.all = 0;
	PieCtrlRegs.PIEIFR7.all = 0;
	PieCtrlRegs.PIEIFR8.all = 0;
	PieCtrlRegs.PIEIFR9.all = 0;
	PieCtrlRegs.PIEIFR10.all = 0;
	PieCtrlRegs.PIEIFR11.all = 0;
	PieCtrlRegs.PIEIFR12.all = 0;
}

/******************************************************************************/
/* SYS_PerInterrupts
 *
 * Controls the Peripheral interupts. See 2.4.5 PIE Channel Mapping in TRM
 *  page 88 for cahnnel mapping.					 					 	  */
/******************************************************************************/
void SYS_PerInterrupts(unsigned char state)
{
	if(state)
	{
		PieCtrlRegs.PIECTRL.bit.ENPIE  =  1;
	}
	else
	{
		PieCtrlRegs.PIECTRL.bit.ENPIE  =  0;
	}
}

/******************************************************************************/
/* SYS_Unlock
 *
 * Calls EALLOW so that config bits can be set.		 					 	  */
/******************************************************************************/
void SYS_Unlock(void)
{
	__asm(" EALLOW");
}

/******************************************************************************/
/* SYS_Unlock
 *
 * Calls EDIS so that config bits can't be set.		 					 	  */
/******************************************************************************/
void SYS_Lock(void)
{
	__asm(" EDIS");
}

/******************************************************************************/
/* SYS_EnableInterruptGroup
 *
 * Enables IER register for a certain group. See page 89 in TRM.		 	  */
/******************************************************************************/
void SYS_EnableInterruptGroup(ENUM_INTERRUPT_GROUP group)
{
	IER |= group;
}

/******************************************************************************/
/* SYS_EnableRealTime
 *
 * Enables IER register for a certain group.		 					 	  */
/******************************************************************************/
void SYS_EnableRealTime(void)
{
	__asm(" clrc DBGM");
}

/******************************************************************************/
/* SYS_SetupPinMux
 *
 * This function sets the peripheral muxing for the specified pin.		 	  */
/******************************************************************************/
void SYS_SetupPinMux(unsigned short pin, unsigned short cpu, unsigned short peripheral)
{
    volatile unsigned long *gpioBaseAddr;
    volatile unsigned long *mux, *gmux, *csel;
    unsigned short pin32, pin16, pin8;

    pin32 = pin % 32;
    pin16 = pin % 16;
    pin8 = pin % 8;
    gpioBaseAddr = (Uint32 *)&GpioCtrlRegs + (pin/32)*GPY_CTRL_OFFSET;

    /* Sanity check for valid cpu and peripheral values */
    if (cpu > GPIO_MUX_CPU2CLA || peripheral > 0xF)
    {
    	return;
    }


    /*
     * Create pointers to the appropriate registers. This is a workaround for the
     *  way GPIO registers are defined. The standard definition in the header file
     *  makes it very easy to do named accesses of one register or bit, but hard
     *  to do arbitrary numerical accesses. It's register or bit, but hard to do
     *  arbitrary numerical accesses. It's easier to have an array of GPIO modules
     *  with identical registers, including arrays for multi-register groups like
     *  GPyCSEL1-4. But the header file doesn't define anything we can turn into
     *  an array, so manual pointer arithmetic is used instead.
     */
    mux = gpioBaseAddr + GPYMUX + pin32/16;
    gmux = gpioBaseAddr + GPYGMUX + pin32/16;
    csel = gpioBaseAddr + GPYCSEL + pin32/8;

    SYS_Unlock();
    /*
     * To change the muxing, set the peripheral mux to 0/GPIO first to avoid glitches,
     *  then change the group mux, then set the peripheral mux to its target value.
     *  Finally, set the CPU select. This procedure is described in the TRM.
     *  Unfortunately, since we don't know the pin in advance we can't hardcode
     *  a bitfield reference, so there's some tricky bit twiddling here.
     */
    *mux &= ~(0x3UL << (2*pin16));
    *gmux &= ~(0x3UL << (2*pin16));
    *gmux |= (Uint32)((peripheral >> 2) & 0x3UL) << (2*pin16);
    *mux |= (Uint32)(peripheral & 0x3UL) << (2*pin16);
    *csel &= ~(0x3L << (4*pin8));
    *csel |= (Uint32)(cpu & 0x3L) << (4*pin8);
    SYS_Lock();
}

/******************************************************************************/
/* SYS_SetupPinOptions
 *
 * Setup up the GPIO input/output options for the specified pin.
 *
 * Input pins, the valid flags are:
 *
 * GPIO_PULLUP	Enable pull-up
 * GPIO_INVERT	Enable input polarity inversion
 * GPIO_SYNC		Synchronize the input latch to PLLSYSCLK (default -- you don't need to specify this)
 * GPIO_QUAL3	Use 3-sample qualification
 * GPIO_QUAL6	Use 6-sample qualification
 * GPIO_ASYNC	Do not use synchronization or qualification
 *
 * For output pins, the valid flags are:
 *
 * GPIO_OPENDRAIN	Output in open drain mode
 * GPIO_PULLUP		If open drain enabled, also enable the pull-up
 * GPIO_PUSHPULL		Push and pull
 * 																			  */
/******************************************************************************/
void SYS_SetupPinOptions(unsigned short pin, unsigned short output, unsigned short flags)
{
    volatile unsigned long *gpioBaseAddr;
    volatile unsigned long *dir, *pud, *inv, *odr, *qsel;
    unsigned long pin32, pin16, pinMask, qual;

    pin32 = pin % 32;
    pin16 = pin % 16;
    pinMask = 1UL << pin32;
    gpioBaseAddr = (Uint32 *)&GpioCtrlRegs + (pin/32)*GPY_CTRL_OFFSET;

    /*
     * Create pointers to the appropriate registers. This is a workaround for the
     *  way GPIO registers are defined. The standard definition in the header file
     *  makes it very easy to do named accesses of one register or bit, but hard
     *  to do arbitrary numerical accesses. It's easier to have an array of GPIO
     *  modules with identical registers, including arrays for multi-register groups
     *  like GPyQSEL1-2. But the header file doesn't define anything we can turn
     *  into an array, so manual pointer arithmetic is used instead.
     */
    dir = gpioBaseAddr + GPYDIR;
    pud = gpioBaseAddr + GPYPUD;
    inv = gpioBaseAddr + GPYINV;
    odr = gpioBaseAddr + GPYODR;
    qsel = gpioBaseAddr + GPYQSEL + pin32/16;

    SYS_Unlock();
    /* Set the data direction */
    *dir &= ~pinMask;
    if (output == 1)
    {
        /* Output, with optional open drain mode and pull-up */
        *dir |= pinMask;

        /* Enable open drain if necessary */
        if (flags & GPIO_OPENDRAIN)
        {
            *odr |= pinMask;
        }
        else
        {
            *odr &= ~pinMask;
        }

        /* Enable pull-up if necessary. Open drain mode must be active. */
        if (flags & (GPIO_OPENDRAIN | GPIO_PULLUP))
        {
            *pud &= ~pinMask;
        }
        else
        {
            *pud |= pinMask;
        }
    }
    else
    {
        /* Input, with optional pull-up, qualification, and polarity inversion */
        *dir &= ~pinMask;

        /* Enable pull-up if necessary */
        if (flags & GPIO_PULLUP)
        {
            *pud &= ~pinMask;
        }
        else
        {
            *pud |= pinMask;
        }

        /* Invert polarity if necessary */
        if (flags & GPIO_INVERT)
        {
            *inv |= pinMask;
        }
        else
        {
            *inv &= ~pinMask;
        }
    }

    /*
     * Extract the qualification parameter and load it into the register. This is
     *  also needed for open drain outputs, so we might as well do it all the time.
     */
    qual = (flags & GPIO_ASYNC) / GPIO_QUAL3;
    *qsel &= ~(0x3L << (2 * pin16));
    if (qual != 0x0)
    {
        *qsel |= qual << (2 * pin16);
    }
    SYS_Lock();
}

/******************************************************************************/
/* SYS_ReadPin
 *
 * This function read the GPyDAT register bit for the specified pin.		  */
/******************************************************************************/
unsigned short SYS_ReadPin(unsigned short pin)
{
	volatile unsigned long *gpioDataReg;
	unsigned short pinVal;

	gpioDataReg = (volatile Uint32 *)&GpioDataRegs + (pin/32)*GPY_DATA_OFFSET;
	pinVal = (gpioDataReg[GPYDAT] >> (pin % 32)) & 0x1;

	return pinVal;
}

/******************************************************************************/
/* SYS_WritePin
 *
 * This function sets the GPyDAT register bit for the specified pin.		  */
/******************************************************************************/
void SYS_WritePin(unsigned short pin, unsigned short outVal)
{
	volatile unsigned long *gpioDataReg;
	unsigned long pinMask;

	gpioDataReg = (volatile Uint32 *)&GpioDataRegs + (pin/32)*GPY_DATA_OFFSET;
	pinMask = 1UL << (pin % 32);

	if (outVal == 0)
	{
		gpioDataReg[GPYCLEAR] = pinMask;
	}
	else
	{
		gpioDataReg[GPYSET] = pinMask;
	}
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
