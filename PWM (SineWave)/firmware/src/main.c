/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

bool continueLoop = true; 
int CurrentCount = 0;
uint32_t count;
uint32_t pulseCounter = 0;
uint16_t timer_period = 0;
uint16_t period = 0;
//bool isError = false;

int newPWM;

int dutyArray[100] = {  10,
                        40,70,100,130,150,180,210,240,260,290,
                        320,340,370,400,420,450,470,490,520,540,
                        560,580,610,630,650,670,680,700,720,740,
                        750,770,780,800,810,820,830,840,850,860,
                        870,880,880,890,890,890,900,900,900,900,
                        900,900,890,890,890,880,880,870,860,850,
                        840,830,820,810,800,780,770,750,740,720,
                        700,680,670,650,630,610,580,560,540,520,
                        490,470,450,420,400,370,340,320,290,260,
                        240,210,180,150,130,100,70,40,10,
                        
};

bool pulseCounterOps(void)
{
    if(pulseCounter == 9)   
    {
        pulseCounter = 0;
        return true;
    }
    pulseCounter++;
    return false;
}

void SetPWM(int PWMCount)
{
    TCC0_PWM24bitDutySet(TCC0_CHANNEL0, PWMCount);
}

//uint16_t ADC_Error(){
//    uint16_t result = 0;
//    result = (ADC0_ConversionResultGet() * 0.805);
//    {
//        
//        isError = true;
//    }
//    return result;
//}

void callback (TC_TIMER_STATUS status, uintptr_t context)
{
    newPWM = dutyArray[CurrentCount];
    continueLoop = false;
    SetPWM(newPWM);
    if(CurrentCount == 100) CurrentCount = 0;
    CurrentCount++;
//    uint16_t adcError = ADC_Error();
//    if(isError){
//        newPWM = dutyArray[CurrentCount-1]*adcError;
//    }
}


bool set_period(uint16_t periodVal)
{
    period = periodVal;
    return true;
}

bool set_timer_period(uint16_t timeperiodVal)
{
    timer_period = timeperiodVal;
    return true;
}


int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    set_period(1000);
    set_timer_period(60000);
    
    TC3_TimerStart();
    TC3_TimerCallbackRegister(callback, (uintptr_t)NULL);
        
    TCC0_PWMStart();
    TCC0_PWM24bitPeriodSet(period);

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        while(continueLoop)
        {           
            SYSTICK_DelayMs (1000);
        }   
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

