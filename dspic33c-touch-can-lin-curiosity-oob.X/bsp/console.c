
/*
© [2023] Microchip Technology Inc. and its subsidiaries.

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

#include "../mcc_generated_files/adc/adc1.h"
#include "../mcc_generated_files/uart/uart1.h"
#include "../mcc_generated_files/timer/sccp1.h"
#include "console.h"
#include <string.h>
#include <stdio.h>

#define CMD_MAX_SIZE 8

#define LED1_ON "LED1 ON"
#define LED1_OFF "LED1 OFF"
#define LED2_ON "LED2 ON"
#define LED2_OFF "LED2 OFF"
#define LED3_ON "LED3 ON"
#define LED3_OFF "LED3 OFF"
#define LED4_ON "LED4 ON"
#define LED4_OFF "LED4 OFF"
#define LED5_ON "LED5 ON"
#define LED5_OFF "LED5 OFF"

bool readCmdStatus = false;
uint8_t option[CMD_MAX_SIZE];
uint8_t commandCount = 0;
enum CONSOLE_CMDS command;

static void CMD_Reset(void);

void CMDTimer_TimeoutCallback(void)
{
    CMDTimer.Stop();
    commandCount = 0;
    CMD_Reset(); 
}

static void CMD_Reset(void)
{
    uint8_t commandIndex;
    for(commandIndex = 0; commandIndex<CMD_MAX_SIZE ;commandIndex++)
    {
        option[commandIndex] = 0;
    }
}

void CONSOLE_Initilaize(void)
{
    CMDTimer.TimeoutCallbackRegister(CMDTimer_TimeoutCallback);
    TouchUART.Initialize();
}

void CONSOLE_Tasks(void)
{
    uint8_t readChar;
    if(TouchUART.IsRxReady())
    {
        readChar = TouchUART.Read();
        if((readChar != '\r')&&(commandCount <= CMD_MAX_SIZE))
        {
            CMDTimer.Start();
            option[commandCount] = readChar;
            commandCount++;
        }
        else
        {
            commandCount = 0;   
            readCmdStatus = true;
        }
    }
    
    if(readCmdStatus)
    {
        readCmdStatus = false;
        if(strncmp((char *)option,(char *)LED1_ON,7) == 0)
        {
            command = CMD_LED1_ON;
        }
        else if(strncmp((char *)option,(char *)LED2_ON,7) == 0)
        {
            command = CMD_LED2_ON;
        }
        else if(strncmp((char *)option,(char *)LED3_ON,7) == 0)
        {
            command = CMD_LED3_ON;
        }
        else if(strncmp((char *)option,(char *)LED4_ON,7) == 0)
        {
            command = CMD_LED4_ON;
        }
        else if(strncmp((char *)option,(char *)LED5_ON,7) == 0)
        {
            command = CMD_LED5_ON;
        }
        else if(strncmp((char *)option,(char *)LED1_OFF,8) == 0)
        {
            command = CMD_LED1_OFF;
        }
        else if(strncmp((char *)option,(char *)LED2_OFF,8) == 0)
        {
            command = CMD_LED2_OFF;
        }
        else if(strncmp((char *)option,(char *)LED3_OFF,8) == 0)
        {
            command = CMD_LED3_OFF;
        }
        else if(strncmp((char *)option,(char *)LED4_OFF,8) == 0)
        {
            command = CMD_LED4_OFF;
        }
        else if(strncmp((char *)option,(char *)LED5_OFF,8) == 0)
        {
            command = CMD_LED5_OFF;
        }
        else
        {
            command = CMD_ERROR;
        }
        CMD_Reset();
    }
    else
    {
        command = CMD_NONE;
    }
}

bool CONSOLE_InProgress(void)
{
    return (commandCount !=0); 
}

enum CONSOLE_CMDS CONSOLE_OptionGet(void)
{
    return command;
}