/**
 * @file      console.h
 * 
 * @defgroup  touch_demo
 * 
 * @brief     This is the function header file for console input functions
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdbool.h>

/**
 @ingroup  touch_demo
 @enum     CONSOLE_CMDS
 @brief    Defines the UART commands
*/
enum CONSOLE_CMDS
{
    CMD_NONE = 0,
    CMD_ERROR = 1,
    CMD_LED1_ON = 2,
    CMD_LED1_OFF = 3,
    CMD_LED2_ON = 4,
    CMD_LED2_OFF = 5,
    CMD_LED3_ON = 6,
    CMD_LED3_OFF = 7,
    CMD_LED4_ON = 8,
    CMD_LED4_OFF = 9,
    CMD_LED5_ON = 10,
    CMD_LED5_OFF = 11
};

/**
 * @ingroup     touch_demo
 * @brief       This function initializes console to read commands
 * @param[in]   none
 * @return      none
 */
void CONSOLE_Initilaize(void);

/**
 * @ingroup     touch_demo
 * @brief       This function performs the process tasks to read commands
 * @param[in]   none
 * @return      none
 */
void CONSOLE_Tasks(void);

/**
 * @ingroup     touch_demo
 * @brief       This function performs the process tasks to display debug message
 * @param[in]   none
 * @return      true  -Read command in progress
 *              false  -Read command is not in progress or completed
 */
bool CONSOLE_InProgress(void);

/**
 * @ingroup     touch_demo
 * @brief       This function gets the command read status
 * @param[in]   none
 * @return      \ref CONSOLE_CMDS
 */
enum CONSOLE_CMDS CONSOLE_OptionGet(void);

#endif //CONSOLE_H