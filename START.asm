;******************************************************************************/
;* Change log                                                                 *
;*
;*
;*
;* Date         Revision    Comments
;* MM/DD/YY
;* --------     ---------   ----------------------------------------------------
;* 01/16/16     13.0_DW0a   Created.
;*                                                                            */
;******************************************************************************/

;******************************************************************************/
;* Contains start code and entry point.
;*																			  */
;******************************************************************************/


;******************************************************************************/
;* entry point																  */
;******************************************************************************/
    .ref _c_int00
    .global code_start
    .sect "codestart"

code_start:
        LB _c_int00         ;Branch to start of boot._asm in RTS library

;******************************************************************************/
;* END OF FILE																  */
;******************************************************************************/
