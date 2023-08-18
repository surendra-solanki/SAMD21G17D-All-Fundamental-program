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
// *****************************************************************************4

// uint8_t TX_Data[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n";
uint8_t TX_Data[] = "HELLO\n";
//uint8_t TX_Receive[sizeof(TX_Data)];
    
int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SYSTICK_TimerStart ();
    SYSTICK_TimerPeriodSet (10000);
    
    while ( true )                            /////////// PA12- SDA PA13-SCL
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
//        SERCOM2_I2C_WriteRead(0x21,TX_Data,sizeof(TX_Data),TX_Receive, sizeof(TX_Receive));
//        for(int i=0;i<5;i++)
//        {
           SERCOM2_I2C_Write( 0x27, TX_Data, sizeof(TX_Data));
//           SERCOM5_USART_Write( &TX_Data,sizeof(TX_Data));
//        }
      
//        
//        SYSTICK_DelayMs(100);
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}

/*******************************************************************************
 End of File
*/

