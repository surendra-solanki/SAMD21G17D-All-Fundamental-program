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
void CALL(TC_TIMER_STATUS status, uintptr_t context)    ////Method1
{
   GPIO_PA14_Toggle();
//   SYSTICK_DelayMs (1000);
//   GPIO_PA14_Clear();
}

int main ( void )
{   
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SYSTICK_TimerStart ();
    
    TC3_TimerStart();  //////////////Method1
    TC3_TimerCallbackRegister(CALL,(uintptr_t)NULL);    ////Method1
    
    
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        
    }
    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

