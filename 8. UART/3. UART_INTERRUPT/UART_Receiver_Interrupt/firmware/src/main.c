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

bool errorStatus = false;
bool readStatus = false;
uint8_t errorRead;
uint8_t readRead;

//SERCOM_USART_RING_BUFFER_CALLBACK
void APP_ReadCallback( uintptr_t context)
{
//    if( event == SERCOM_USART_EVENT_READ_THRESHOLD_REACHED)
//    {
//        
//    }
    if(SERCOM0_USART_ErrorGet() != USART_ERROR_NONE)
    {
     errorStatus = true;   
    }
    else
    {
      readStatus = true;  
    }
}
//    if(SERCOM0_USART_ErrorGet() == USART_ERROR_NONE)
//    {
//        errorStatus = true;
//    }
//    else
//    {
//        readStatus = true;
//    }
////        SERCOM0_USART_ReceiverEnable(  );
////         SERCOM0_USART_Read( &readRead, sizeof(readRead));
////          SERCOM5_USART_Write( &readRead, sizeof(readRead));
//    }
 
//    if(SERCOM_USART_EVENT == SERCOM_USART_EVENT_READ_BUFFER_FULL)
//         if (event == SERCOM_USART_EVENT_READ_THRESHOLD_REACHED)
//    {
//       SERCOM0_USART_Read( &readRead, sizeof(readRead));
//          SERCOM5_USART_Write( &readRead, sizeof(readRead)); 
//    }
//         
//}

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );

    SERCOM0_USART_ReadCallbackRegister(APP_ReadCallback, 0);
    
    while ( true )
    {
//        SERCOM0_USART_Read( &errorRead, sizeof(errorRead));
//        SERCOM5_USART_Write( &errorRead, sizeof(errorRead));
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );                                  ///TX-PA04    RX-PA06
        
        if(errorStatus == true)
        {
          SERCOM0_USART_Read( &errorRead, sizeof(errorRead));
          SERCOM5_USART_Write( &errorRead, sizeof(errorRead));
          errorStatus =false;
        }
        else if(readStatus == true)
        {
//            if(SERCOM_USART_EVENT event == SERCOM_USART_EVENT_READ_THRESHOLD_REACHED)
//            {
            SERCOM0_USART_Read( &readRead, sizeof(readRead));
            
            readStatus = false;   
//            }
//          
        }
        SERCOM5_USART_Write( &readRead, sizeof(readRead));
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

