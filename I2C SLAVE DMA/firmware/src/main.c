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
bool callback(SERCOM_I2C_SLAVE_TRANSFER_EVENT SERCOM_I2C_SLAVE_TRANSFER_EVENT_ERROR, uintptr_t contextHandle)
{
    bool x;
    if (SERCOM1_I2C_ErrorGet() != SERCOM_I2C_SLAVE_ERROR_ALL)
    {
        RX_RECEIVER = SERCOM1_I2C_ReadByte();
            SERCOM5_USART_Write( &RX_RECEIVER, sizeof(RX_RECEIVER) );
//          for(int i=0;i<sizeof(RX_RECEIVER);i++)
//            {
//        RX_RECEIVER = SERCOM1_I2C_ReadByte();
//        SERCOM5_USART_Write( &RX_RECEIVER, sizeof(RX_RECEIVER) );
//            }
        
//            for(int i=0;i<sizeof(RX_Transmitter);i++)
//            {
//               SERCOM2_I2C_WriteByte(RX_Transmitter[i]);
//               SYSTICK_DelayMs(2);
//            }
          
      x=true; 
    }
//    else
//    {       
//      x=false;
//        
//    }
    return x;
} 

int main ( void )
{
    
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SERCOM1_I2C_CallbackRegister(callback,0);
    
    while ( true )                                   ////PA16-SDA PA17-SCL
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        {
            
//            for(int i=0;i<200;i++)
//            {
//            }
//            SERCOM1_REGS->I2CS.SERCOM_CTRLB = SERCOM_I2CS_CTRLB_SMEN_Msk; //Smart mode
//            SERCOM1_REGS->I2CS.SERCOM_INTENSET = SERCOM_I2CS_INTENSET_AMATCH_Msk ;
            
//            if(SERCOM_I2CS_INTENSET_AMATCH_Msk )
            {
//                DMAC_ChannelTransfer (DMAC_CHANNEL_0,  (const void *) &SERCOM1_REGS->I2CM.SERCOM_DATA ,&RX_RECEIVER , sizeof(RX_RECEIVER));
//                RX_RECEIVER = SERCOM1_I2C_ReadByte();
//                SERCOM5_USART_Write( &RX_RECEIVER, sizeof(RX_RECEIVER) ); 
            }
        }
    }
    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

//         SERCOM_I2CM_ADDR_ADDR (0x23) == SERCOM_I2CS_INTFLAG_AMATCH(0x23);  
//        if()

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
//uint8_t RX_RECEIVER;
//uint8_t RX_RECEIVER1;
//
////bool callback(SERCOM_I2C_SLAVE_TRANSFER_EVENT SERCOM_I2C_SLAVE_TRANSFER_EVENT_ERROR, uintptr_t contextHandle)
////{
////    bool x;
////    if (SERCOM1_I2C_ErrorGet() != SERCOM_I2C_SLAVE_ERROR_ALL)
////    {
////      x=true;
//////     RX_RECEIVER = SERCOM1_I2C_ReadByte();
////    }
////    else
////    {
////      x=false;
////    }
////    return x;
////}
//
//
//int main ( void )
//{
//    /* Initialize all modules */
//    SYS_Initialize ( NULL );
////    SERCOM1_I2C_CallbackRegister(callback,0);
//    while ( true )
//    {
//        /* Maintain state machines of all polled MPLAB Harmony modules. */
//        SYS_Tasks ( );
//        {
////        RX_RECEIVER = SERCOM1_I2C_ReadByte();
//        DMAC_ChannelTransfer (DMAC_CHANNEL_0,  (const void *) &SERCOM1_REGS->I2CM.SERCOM_DATA ,&RX_RECEIVER , sizeof(RX_RECEIVER));
//        SERCOM5_USART_Write( &RX_RECEIVER, sizeof(RX_RECEIVER) );   
//        }
//    }
//    /* Execution should not come here during normal operation */
//
//    return ( EXIT_FAILURE );
//}
//
//
///*******************************************************************************
// End of File
//*/