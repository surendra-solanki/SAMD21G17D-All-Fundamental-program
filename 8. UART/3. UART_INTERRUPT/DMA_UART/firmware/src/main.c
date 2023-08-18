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
 uint8_t TX_DATA[]="ABCD\n";
 uint8_t TX_DATA2[sizeof(TX_DATA)];
 
bool completeStatus = false;
bool errorStatus = false;

void APP_Callback(DMAC_TRANSFER_EVENT status, uintptr_t context)
{
    SERCOM0_USART_Write( TX_DATA,sizeof(TX_DATA) );    //PA04 - TX , PA05- RX
    SERCOM5_USART_Write( TX_DATA,sizeof(TX_DATA) );
    
    if(status == DMAC_TRANSFER_EVENT_COMPLETE)
    {
        completeStatus = true;        
    }
    else
    {
        errorStatus = true;
    }
}
    
int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    DMAC_ChannelCallbackRegister(DMAC_CHANNEL_0, APP_Callback, 0);
//    DMAC_ChannelTransfer(DMAC_CHANNEL_0, &TX_DATA2 ,&TX_DATA2 , 1);
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        for(int i=0;i<4;i++)
        {
          DMAC_ChannelTransfer (DMAC_CHANNEL_0, &TX_DATA[i], &TX_DATA2[i], 1);  
        }   
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

