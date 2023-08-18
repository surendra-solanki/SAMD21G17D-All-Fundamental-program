/////*******************************************************************************
////  Main Source File
////
////  Company:
////    Microchip Technology Inc.
//
////  File Name:
////    main.c
////
////  Summary:
////    This file contains the "main" function for a project.
////
////  Description:
////    This file contains the "main" function for a project.  The
////    "main" function calls the "SYS_Initialize" function to initialize the state
////    machines of all modules in the system
//// *******************************************************************************/
//
//// *****************************************************************************
//// *****************************************************************************
//// Section: Included Files
//// *****************************************************************************
//// *****************************************************************************
//
//#include <stddef.h>                     // Defines NULL
//#include <stdbool.h>                    // Defines true
//#include <stdlib.h>                     // Defines EXIT_FAILURE
//#include "definitions.h"                // SYS function prototypes
//
//
//// *****************************************************************************
//// *****************************************************************************
//// Section: Main Entry Point
//// *****************************************************************************
//// *****************************************************************************
//
//int main ( void )
//{
//    /* Initialize all modules */ //SLAVE
//    SYS_Initialize ( NULL );
//    SERCOM5_USART_TransmitterEnable();
//    
//    uint8_t RX_Receiver;
//
//    while ( true )
//    {
//        /* Maintain state machines of all polled MPLAB Harmony modules. */
//        SYS_Tasks ( );
//        
//        RX_Receiver = SERCOM2_I2C_ReadByte();
//        SERCOM5_USART_Write(&RX_Receiver,1);
//        
//        if(status == SERCOM2_I2C_IsBusy)
//        {
//            __delay_ms(100);
//        }
////        
////        if(status == I2C1_NOERR)
////        {
////            I2C1_WriteNBytes(19,Send,1);
////        } 
//    }
//
//    /* Execution should not come here during normal operation */
//
//    return ( EXIT_FAILURE );
//}
//
//
///*******************************************************************************
// End of File
//*/



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
#include "Interrupts.h"


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************


//uint8_t IsHigh=0;

//uint8_t RX_Transmitter[]="Hi I'm Slave\n";
bool callback(SERCOM_I2C_SLAVE_TRANSFER_EVENT SERCOM_I2C_SLAVE_TRANSFER_EVENT_ERROR, uintptr_t contextHandle)
{
    bool x;
    if (SERCOM2_I2C_ErrorGet() != SERCOM_I2C_SLAVE_ERROR_ALL)
    {
        
//            for(int i=0;i<sizeof(RX_Transmitter);i++)
//            {
//               SERCOM2_I2C_WriteByte(RX_Transmitter[i]);
//               SYSTICK_DelayMs(2);
//            }
        
      x=true; 
    }
    else
    {       
      x=false;
//      IsHigh = 1;
    }
    return x;
}

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SYSTICK_TimerStart ();
    SYSTICK_TimerPeriodSet (10000);
    
    
   SERCOM2_I2C_CallbackRegister(callback,0);
    
    
    while ( true )                        //PA12-SDA    //PA13-SCL
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
       
//        for(int i=0;i<50;i++)
//        {
//        if(IsHigh== 1)
//        {
//            IsHigh = 0;
        uint8_t RX_Receiver = SERCOM2_I2C_ReadByte();   
        SERCOM5_USART_Write( &RX_Receiver, sizeof(RX_Receiver));
//        SYSTICK_DelayMs(1);  
//        }
        
         
//        }
//         
//            SYSTICK_DelayMs(10);
    }
    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}

/*******************************************************************************
 End of File
*/


