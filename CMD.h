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
#define LARGEST_COMMAND 10L

/******************************************************************************/
/* LARGEST_HELP
 *
 * This is the largest help string in characters.							  */
/******************************************************************************/
#define LARGEST_HELP 70L

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
extern unsigned char CommandString[LARGEST_COMMAND];
extern unsigned char NumCommands;

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
void CMD_SetNewCommandFlag(unsigned char status);
unsigned char CMD_GetNewCommandFlag(void);

#endif	/* CMD_H */
