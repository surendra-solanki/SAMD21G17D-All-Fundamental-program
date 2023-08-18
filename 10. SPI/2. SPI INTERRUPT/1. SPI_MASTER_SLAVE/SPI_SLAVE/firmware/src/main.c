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

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SYSTICK_TimerStart ();
    SYSTICK_TimerPeriodSet (1000);

    uint8_t RX_Transmiter[]="abcdefghijklmnopqrstuvwxyz\n";
    uint8_t RX_Receiver[sizeof(RX_Transmiter)];
    SS_Set();
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        SS_Clear();
            SERCOM0_SPI_Write(RX_Transmiter,sizeof(RX_Transmiter));
//            SERCOM5_USART_Write(&RX_Transmiter[i],1);
            SYSTICK_DelayMs(100);
            SERCOM0_SPI_Read(RX_Receiver,sizeof(RX_Transmiter));
            SYSTICK_DelayMs(100);
            SERCOM5_USART_Write(RX_Receiver,sizeof(RX_Transmiter));
            SYSTICK_DelayMs(100);
            SS_Set();
           
//        for (int i=0;i<sizeof(RX_Transmiter);i++)
//        {
//         SERCOM0_SPI_Read(&RX_Receiver[i],1);
//         SERCOM5_USART_Write(&RX_Receiver[i],1);
////            SYSTICK_DelayMs (100);
//         SERCOM0_SPI_Write(&RX_Transmiter[i],1);
////         SERCOM5_USART_Write(&RX_Transmiter[i],1);
//            SYSTICK_DelayMs (100); 
//        }
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

