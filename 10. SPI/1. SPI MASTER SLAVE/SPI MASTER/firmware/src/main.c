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

uint8_t TX_DATA[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n";
uint8_t RX_DATA[sizeof(TX_DATA)];
int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SYSTICK_TimerStart ( );
    SYSTICK_TimerPeriodSet ( 10000);
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        
        GPIO_PA06_Clear();
//        SERCOM0_SPI_WriteRead (TX_DATA, sizeof(TX_DATA),RX_DATA,sizeof(RX_DATA));
//        SERCOM5_USART_Write( RX_DATA, sizeof(RX_DATA) );
        
        SERCOM0_SPI_Write(TX_DATA, sizeof(TX_DATA));
        SERCOM5_USART_Write(TX_DATA, sizeof(TX_DATA));
        SYSTICK_DelayMs ( 100 );
        GPIO_PA06_Set();
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

