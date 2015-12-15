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
#include <stdint.h>
#include <stdbool.h>

#include "SYSTEM.h"

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
        //__builtin_enable_interrupts();
    }
    else
    {
       // __builtin_disable_interrupts();
    }
}

/******************************************************************************/
/* SYS_Sleep
 *
 * The function puts the system to sleep.									  */
/******************************************************************************/
void SYS_Sleep(void)
{
   // SYS_SystemUnlock();
   // OSCCONbits.SLPEN = 1; // Device will enter Sleep mode when a WAIT instruction is executed
  //  SYS_SystemLock();
 //   _wait();
}

/******************************************************************************/
/* SYS_Idle
 *
 * The function puts the system in idle.									  */
/******************************************************************************/
void SYS_Idle(void)
{
   // SYS_SystemUnlock();
  //  OSCCONbits.SLPEN = 0; // Device will enter Idle mode when a WAIT instruction is executed
  //  SYS_SystemLock();
  //  _wait();
}

/******************************************************************************/
/* Init_Watchdog
 *
 * The function initializes the watchdog timer.								  */
/******************************************************************************/
void Init_Watchdog(void)
{
    /* does not enable when in debug mode */
  //  WDTCONbits.WDTWINEN = 0; // Disable windowed Watchdog Timer
  //  SYS_Watchdog(OFF);
}

/******************************************************************************/
/* SYS_SoftwareReset
 *
 * The function does a software reset.										  */
/******************************************************************************/
void SYS_SoftwareReset(void)
{
    unsigned long dummy;
 //   SYS_SystemUnlock();
  //  DMA_Suspend(ON);
//    RSWRSTbits.SWRST = 1;
 //   dummy = RSWRSTbits.SWRST; // read the register to start the reset
  //  while(1)
  //  {
  //      Nop();
  //  }
}

/******************************************************************************/
/* SYS_Watchdog
 *
 * The function enables/disables the watchdog timer.						  */
/******************************************************************************/
unsigned char SYS_Watchdog(unsigned char state)
{
    
}

/******************************************************************************/
/* SYS_PetFluffyPuppy
 *
 * The function pets the watchdog otherwise known as a the "fluffy puppy".	  */
/******************************************************************************/
void SYS_PetFluffyPuppy(void)
{
    //WDTCONbits.WDTCLR = 1; // clear the watchdog
}

/******************************************************************************/
/* SYS_PetFluffyPuppy
 *
 * The function pets the watchdog otherwise known as a the "fluffy puppy".	  */
/******************************************************************************/
void SYS_PetWatchDog(void)
{
    SYS_PetFluffyPuppy();
}

/******************************************************************************/
/* SYS_CheckWatchdogReset
 *
 * The function checks for a watchdog reset.								  */
/******************************************************************************/
unsigned char SYS_CheckWatchdogReset(void)
{
	return FALSE;
}

/*-----------------------------------------------------------------------------/
 End of File
/-----------------------------------------------------------------------------*/
