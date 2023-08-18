///*******************************************************************************
//  Main Source File
//
//  Company:
//    Microchip Technology Inc.
//
//  File Name:
//    main.c
//
//  Summary:
//    This file contains the "main" function for a project.
//
//  Description:
//    This file contains the "main" function for a project.  The
//    "main" function calls the "SYS_Initialize" function to initialize the state
//    machines of all modules in the system
// *******************************************************************************/
//
//// *****************************************************************************
//// *****************************************************************************
//// Section: Included Files
//// *****************************************************************************
//// *****************************************************************************

//#include <stddef.h>                     // Defines NULL
//#include <stdbool.h>                    // Defines true
//#include <stdlib.h>                     // Defines EXIT_FAILURE
//#include "definitions.h"                // SYS function prototypes


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

//uint8_t TX_DATA[]= "Hi Master\n";
//uint8_t TX_Receive[10];
//    
//void callback()
//{
//       if(SERCOM0_USART_ErrorGet() != USART_ERROR_NONE)
//    {
//        /* ErrorGet clears errors, set error flag to notify console */
//        SERCOM0_USART_Read(TX_Receive,sizeof(TX_Receive));
//        SERCOM5_USART_Write(TX_Receive,sizeof(TX_Receive));
//    }        
//}
//void callback()
//{
//       if(SERCOM0_USART_ErrorGet() != USART_ERROR_NONE)
//    {
//        /* ErrorGet clears errors, set error flag to notify console */
//        SERCOM0_USART_Read(TX_Receive,sizeof(TX_Receive));
//        SERCOM5_USART_Write(TX_Receive,sizeof(TX_Receive));
//    }        
//}
//int main ( void )
//{
//    /* Initialize all modules */
//    SYS_Initialize ( NULL );
//    
//    SERCOM0_USART_WriteCallbackRegister( callback,0);
//
//    while ( true )
//    {
//        /* Maintain state machines of all polled MPLAB Harmony modules. */
//        SYS_Tasks ( );
//        SERCOM0_USART_Write(TX_DATA,sizeof(TX_DATA));         //PA04-TX , PA05- RX
// 
//    /* Execution should not come here during normal operation */
//    }
//    return ( EXIT_FAILURE );
//}


///*******************************************************************************
// End of File
//*/
//


#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <string.h>
#include "definitions.h"                // SYS function prototypes

#define RX_BUFFER_SIZE 10


char messageStart[] = {};
char receiveBuffer[RX_BUFFER_SIZE] = {};
char echoBuffer[RX_BUFFER_SIZE] = {};
char messageError[] = "**** USART error occurred ****\r\n";
char sendmessage[10] = "HI Master";

bool errorStatus = false;
bool writeStatus = false;
bool readStatus = false;


void APP_WriteCallback(uintptr_t context)
{
    writeStatus = true;
}

void APP_ReadCallback(uintptr_t context)
{
    if(SERCOM0_USART_ErrorGet() != USART_ERROR_NONE)
    {
        /* ErrorGet clears errors, set error flag to notify console */
        errorStatus = true;
    }
    else
    {
        readStatus = true;
    }
}

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );

    /* Register callback functions and send start message */
    SERCOM0_USART_WriteCallbackRegister(APP_WriteCallback, 0);
    SERCOM0_USART_ReadCallbackRegister(APP_ReadCallback, 0);
    SERCOM0_USART_Write(&messageStart[0], sizeof(messageStart));

    while ( true )
    {
        if(errorStatus == true)
        {
            /* Send error message to console */
            errorStatus = false;
            SERCOM0_USART_Write(&messageError[0], sizeof(messageError));
        }
        else if(readStatus == true)
        {
            /* Echo back received buffer and Toggle LED */
            readStatus = false;
            SERCOM0_USART_Write(&sendmessage[0], sizeof(sendmessage));
        }
        else if(writeStatus == true)
        {
            /* Submit buffer to read user data */
            writeStatus = false;
            SERCOM0_USART_Read(&receiveBuffer[0], sizeof(receiveBuffer));
            SERCOM5_USART_Write(&receiveBuffer[0], sizeof(receiveBuffer));
        }
        else
        {
            /* Repeat the loop */
            ;
        }
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}
