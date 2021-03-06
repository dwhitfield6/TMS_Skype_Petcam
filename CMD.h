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
/* Files to Include                                                           */
/******************************************************************************/
#ifndef CMD_H
#define	CMD_H

#include "F2837xS_device.h"     		// TMS320F28377S Include file
#include "F2837xS_GlobalPrototypes.h"
#include <stdint.h>
#include <stdbool.h>

#include "UART.h"
#include "USER.h"

/******************************************************************************/
/* LARGEST_COMMAND
 *
 * This is the largest command in characters.								  */
/******************************************************************************/
#define LARGEST_COMMAND 30L

/******************************************************************************/
/* LARGEST_COMMAND_WITH_EXTRA
 *
 * This is the largest command in characters with some extra for command
 *  parameters.																  */
/******************************************************************************/
#define LARGEST_COMMAND_WITH_EXTRA 50L

/******************************************************************************/
/* MISC_BUFFER_SIZE
 *
 * This is the size of the misc buffer.										  */
/******************************************************************************/
#define MISC_BUFFER_SIZE 50

/******************************************************************************/
/* SPRINT_BUFFER_SIZE
 *
 * This is the size of the sprintf buffer.									  */
/******************************************************************************/
#define SPRINT_BUFFER_SIZE 200

/******************************************************************************/
/* LARGEST_HELP
 *
 * This is the largest help string in characters.							  */
/******************************************************************************/
#define LARGEST_HELP 100L

/******************************************************************************/
/* Structures                                                                 */
/******************************************************************************/
typedef void (*pFunction)(void); // function pointer

typedef struct Type_command
{
    unsigned char Command[LARGEST_COMMAND];     // User Command
    pFunction Function;                         // Function to point to
    unsigned char Help[LARGEST_HELP];           // Help explanation
}COMMANDTYPE;

/******************************************************************************/
/* Command responses                                                          */
/******************************************************************************/
#define BAD_COMMAND "BAD COMMAND, TYPE ?+Enter"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
extern const COMMANDTYPE Commands[];
extern unsigned char CommandStringA[LARGEST_COMMAND_WITH_EXTRA];
extern unsigned char CommandStringC[LARGEST_COMMAND_WITH_EXTRA];
extern unsigned char NumCommands;
extern unsigned char MiscBuffer[MISC_BUFFER_SIZE];
extern unsigned char SPRINTBuffer[SPRINT_BUFFER_SIZE];

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/
void InitCMD(void);
void CMD_Help(void);
unsigned char CMD_CheckMatch(unsigned char* received, const COMMANDTYPE* commands, unsigned char size);
void CMD_SetNewCommandFlagA(unsigned char status);
void CMD_SetNewCommandFlagC(unsigned char status);
unsigned char CMD_GetNewCommandFlagA(void);
unsigned char CMD_GetNewCommandFlagC(void);
unsigned char CMD_CommandSize(pFunction function);
void CMD_PrintCommand(const COMMANDTYPE* command);
void CMD_PrintAllCommands(void);
void CMD_SendSanyo(void);
void CMD_SendVisio(void);
void CMD_SendIdylis(void);
void CMD_SetActiveUART(unsigned char state);
unsigned char CMD_GetActiveUART(void);
void CMD_InitBluetooth(void);
void CMD_GoToSKYPE(void);
void CMD_GoToOriginal(void);
void CMD_IncreaseLargeAverageAlot(void);
void CMD_IncreaseLargeAverage(void);
void CMD_DecreaseLargeAverageAlot(void);
void CMD_DecreaseLargeAverage(void);
void CMD_IncreaseSmallAverageAlot(void);
void CMD_IncreaseSmallAverage(void);
void CMD_DecreaseSmallAverageAlot(void);
void CMD_DecreaseSmallAverage(void);
void CMD_VULowpass(void);
void CMD_VUAll(void);
void CMD_SKYPE_SignalInverted(void);
void CMD_SKYPE_SignalNotInverted(void);
void CMD_IncreaseAntiTwitchAverager(void);
void CMD_IncreaseAntiTwitchAveragerAlot(void);
void CMD_DecreaseAntiTwitchAverager(void);
void CMD_DecreaseAntiTwitchAveragerAlot(void);
void CMD_IncreaseAudioTriggerAlot(void);
void CMD_IncreaseAudioTrigger(void);
void CMD_DecreaseAudioTriggerAlot(void);
void CMD_DecreaseAudioTrigger(void);

#endif	/* CMD_H */
