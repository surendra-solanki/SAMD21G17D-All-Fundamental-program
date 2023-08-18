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
uint8_t RX_RECEIVER;
int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        {
            SERCOM1_REGS->I2CS.SERCOM_CTRLB = SERCOM_I2CS_CTRLB_SMEN_Msk; //Smart mode
//            SERCOM1_REGS->I2CS.SERCOM_INTENSET = SERCOM_I2CS_INTENSET_AMATCH_Msk ;
            
//            if(SERCOM_I2CS_INTENSET_AMATCH_Msk )
            {
            DMAC_ChannelTransfer (DMAC_CHANNEL_0,  (const void *) &SERCOM1_REGS->I2CM.SERCOM_DATA ,&RX_RECEIVER , sizeof(RX_RECEIVER));
            SERCOM5_USART_Write( &RX_RECEIVER, sizeof(RX_RECEIVER) ); 
            }
        }
    }
    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/
