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
    
    uint8_t UART_TX[]= "uartefghijklmnopqrstuvwxyz\n";
    uint8_t UART_RX[sizeof(UART_TX)];
    
    uint8_t I2C_TX[]="i2cdefghijklmnopqrstuvwxyz\n";
    uint8_t I2C_RX[sizeof(I2C_TX)];
    
    
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        
        SERCOM0_USART_Write(UART_TX ,sizeof(UART_TX));
        
        SERCOM0_USART_Read(UART_RX ,sizeof(UART_RX));
        SERCOM5_USART_Write(UART_RX ,sizeof(UART_RX));
        
        for(int i=0;i<sizeof(I2C_RX);i++)
        {
        I2C_RX[i] =SERCOM1_I2C_ReadByte();
        SERCOM5_USART_Write(&I2C_RX[i] ,sizeof(I2C_RX[i]));
        SERCOM1_I2C_WriteByte(I2C_TX[i]);  
        }
        
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

