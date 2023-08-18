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
uint8_t TX_DATA[] = "abcdefghijklmnopqrstuvwxyz\n";
//uint8_t RX_DATA[sizeof(TX_DATA)];
uint8_t RX_DATA[10];

 void callBack(  )
{
     if(SERCOM0_SPI_ErrorGet() == SPI_SLAVE_ERROR_NONE)
     {
//        for(int i=0;i<=sizeof(TX_DATA);i++){
//            SERCOM0_SPI_Write( TX_DATA , sizeof(TX_DATA));
//           // SYSTICK_DelayMs(5);
//        }
     }
}

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SYSTICK_TimerStart ();
    SYSTICK_TimerPeriodSet (10000);
    SERCOM0_SPI_CallbackRegister(callBack,0);
    
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        SERCOM0_SPI_Read(RX_DATA,sizeof(RX_DATA) );
        
        SERCOM5_USART_Write( RX_DATA,sizeof(RX_DATA) );
        SYSTICK_DelayMs ( 100);
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

