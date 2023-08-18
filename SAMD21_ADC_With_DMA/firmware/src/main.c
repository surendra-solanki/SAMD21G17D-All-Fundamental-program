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
uint16_t TX_DATA ;
float output_voltage;
volatile bool dma_ch0Done = false;

void dmac_call_back(DMAC_TRANSFER_EVENT return_event,uintptr_t no_value)
{
    
     if (DMAC_TRANSFER_EVENT_COMPLETE == return_event)
    {
        dma_ch0Done = true;
//        DMAC_ChannelTransfer (DMAC_CHANNEL_0,(const void*)&ADC_REGS->ADC_RESULT ,&TX_DATA, sizeof(TX_DATA));
//        output_voltage = (float)TX_DATA * 3.3 / 4095;
//        printf("ADC=%.2f ",output_voltage);
//        
//        dma_ch0Done = false;
       
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
    SYSTICK_TimerStart ( );
    SYSTICK_TimerPeriodSet ( 10000 );
    
 
    ADC_Enable();
//    ADC_ChannelSelect( ADC_POSINPUT_PIN0,  ADC_NEGINPUT_GND );
//    ADC_ConversionStart( );
    
    DMAC_ChannelCallbackRegister (DMAC_CHANNEL_0,dmac_call_back, ( uintptr_t) NULL);
    DMAC_ChannelTransfer (DMAC_CHANNEL_0,(const void*)&ADC_REGS->ADC_RESULT ,(const void*)&SERCOM0_REGS->USART_INT.SERCOM_DATA, sizeof(TX_DATA));
    while ( true )                                                                   ////destination &TX_DATA
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        
             if(dma_ch0Done == true)
             {
                 output_voltage = (float)TX_DATA * 3.3 / 4095;
                 printf("ADC=%.2f ",output_voltage);
                 dma_ch0Done = false;
                 DMAC_ChannelTransfer (DMAC_CHANNEL_0,(const void*)&ADC_REGS->ADC_RESULT ,(const void*)&SERCOM0_REGS->USART_INT.SERCOM_DATA, sizeof(TX_DATA));
             }
        SYSTICK_DelayMs (100);
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

