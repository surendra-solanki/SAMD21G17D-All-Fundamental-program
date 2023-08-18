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
//////////////////////////PIN CONFIGURATION OF RECEIVER/////////////////////////
/////PA08-UART_TX-SERCOM0_PAD0
/////PA07-UART_RX-SERCOM0_PAD3
/////PA22-CDC_TX-SERCOM5_PAD0
/////PB22-CDC_RX-SERCOM5_PAD2


int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SYSTICK_TimerStart ();
    SYSTICK_TimerPeriodSet (10000);
    
//    uint8_t RX_DATA;
    uint8_t RX_Receive[8];
    
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        SERCOM0_USART_Read(RX_Receive ,sizeof(RX_Receive));
        SERCOM5_USART_Write(RX_Receive ,sizeof(RX_Receive));
        SYSTICK_DelayMs (10);
//        SERCOM0_USART_Write(RX_DATA ,sizeof(RX_DATA));
//        SERCOM5_USART_Write(RX_DATA,5);
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}



/*******************************************************************************
 End of File
*/
