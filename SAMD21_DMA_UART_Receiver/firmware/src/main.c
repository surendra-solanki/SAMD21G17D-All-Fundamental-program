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

uint16_t RX_DATA;
void dmac_return(DMAC_TRANSFER_EVENT return_event,uintptr_t no_value)
{
       if (DMAC_TRANSFER_EVENT_COMPLETE == return_event)
    {
            DMAC_ChannelTransfer (DMAC_CHANNEL_0, (const void *)&SERCOM0_REGS->USART_INT.SERCOM_DATA, &RX_DATA, sizeof(RX_DATA));
            printf("ADC RETURN = %d",RX_DATA);
            LED_Toggle();
    }
    else if (DMAC_TRANSFER_EVENT_ERROR == return_event)
    {
        while(1); 
        
    }
}

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    DMAC_ChannelCallbackRegister (DMAC_CHANNEL_0,dmac_return , (uintptr_t)NULL);
    DMAC_ChannelTransfer (DMAC_CHANNEL_0, (const void *)&SERCOM0_REGS->USART_INT.SERCOM_DATA, &RX_DATA, sizeof(RX_DATA));
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

