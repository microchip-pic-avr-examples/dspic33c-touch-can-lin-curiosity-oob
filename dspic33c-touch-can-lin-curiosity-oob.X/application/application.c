

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

#include "application.h"
#include "../bsp/led.h"
#include "../bsp/console.h"
#include "../bsp/touch.h"
#include "../bsp/pot.h"

static enum LED_CONTROL
{
    LED_CONTROL_BY_TOUCH,
    LED_CONTROL_BY_UART  
}ledControl;


static void Process_Touch_Tasks(void);
static void Process_Potentiometer_Tasks(void);
static void Process_Led_Tasks(void);

void Application_Initialze(void)
{
    CONSOLE_Initilaize();
    LED_Initialize();
    POT_Initialize();
    TOUCH_Initialize();
}

void Application_Tasks(void)
{
    Process_Touch_Tasks();
    Process_Potentiometer_Tasks();
    Process_Led_Tasks();
}

static void Process_Touch_Tasks(void)
{
    TOUCH_Tasks();
    switch(TOUCH_PadPositionGet())
    {
        case TOUCH_PAD_A:
            LED_ClearAll();
            LED_Set(LED_1);
            ledControl = LED_CONTROL_BY_TOUCH;
            break;       
        case TOUCH_PAD_A_n_B:
            LED_ClearAll();
            LED_Set(LED_1);
            LED_Set(LED_2);
            ledControl = LED_CONTROL_BY_TOUCH;
            break;
        case TOUCH_PAD_B:
            LED_ClearAll();
            LED_Set(LED_1);
            LED_Set(LED_2);
            LED_Set(LED_3);
            ledControl = LED_CONTROL_BY_TOUCH;
            break;
        case TOUCH_PAD_B_n_C:
            LED_ClearAll();
            LED_Set(LED_1);
            LED_Set(LED_2);
            LED_Set(LED_3);
            LED_Set(LED_4);
            ledControl = LED_CONTROL_BY_TOUCH;
            break;
        case TOUCH_PAD_C:
            LED_ClearAll();
            LED_Set(LED_1);
            LED_Set(LED_2);
            LED_Set(LED_3);
            LED_Set(LED_4);
            LED_Set(LED_5);
            ledControl = LED_CONTROL_BY_TOUCH;
            break;
        case TOUCH_NONE:
            if(ledControl == LED_CONTROL_BY_TOUCH)
            {
                LED_ClearAll();
            }
            break;
        default:
            break;
    }
}

static void Process_Potentiometer_Tasks(void)
{
    float __attribute__((unused)) float potVoltage;
    potVoltage = POT_VoltageGet();
}

static void Process_Led_Tasks(void)
{
    enum CONSOLE_CMDS consoleInput;
    CONSOLE_Tasks();
    consoleInput = CONSOLE_OptionGet();

    if(consoleInput == CMD_ERROR)
    {    
    }
    else if(consoleInput != CMD_NONE)
    {
        ledControl = LED_CONTROL_BY_UART;
    }

    switch(consoleInput)
    {
        case CMD_LED1_ON:
            LED_Set(LED_1);
            break;
        case CMD_LED2_ON:
            LED_Set(LED_2);
            break;
        case CMD_LED3_ON:
            LED_Set(LED_3);
            break;
        case CMD_LED4_ON:
            LED_Set(LED_4);
            break;
        case CMD_LED5_ON:
            LED_Set(LED_5);
            break;
        case CMD_LED1_OFF:
            LED_Clear(LED_1);
            break;
        case CMD_LED2_OFF:
            LED_Clear(LED_2);
            break;
        case CMD_LED3_OFF:
            LED_Clear(LED_3);
            break;
        case CMD_LED4_OFF:
            LED_Clear(LED_4);
            break;
        case CMD_LED5_OFF:
            LED_Clear(LED_5);
            break;
        default:
            break;
    }
    consoleInput = CMD_NONE;
    
}