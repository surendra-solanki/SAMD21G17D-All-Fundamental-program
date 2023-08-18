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

uint16_t ADC;
uint8_t UART_TX[]="UARTEFGHIJKLMNOPQRSTUVWXYZ\n";
uint8_t UART_RX[sizeof(UART_TX)];

uint8_t I2C_TX[]="I2CDEFGHIJKLMNOPQRSTUVWXYZ\n";
uint8_t I2C_RX[sizeof(I2C_TX)];

uint8_t SPI_TX[]="SPIDEFGHIJKLMNOPQRSTUVWXYZ\n";
uint8_t SPI_RX[sizeof(SPI_TX)];
   


void UART_CALLBACK()
{
    if(SERCOM0_USART_ErrorGet() == USART_ERROR_NONE)
    {
    SERCOM0_USART_Read( UART_TX, sizeof(UART_TX));
    SERCOM5_USART_Write( UART_TX, sizeof(UART_TX));
    
    }
//    SERCOM0_USART_Write( UART_TX, sizeof(UART_TX));
//    SERCOM0_USART_Read( UART_RX, sizeof(UART_RX));
    
}

void I2C_CALLBACK()
{
     
     if(SERCOM1_I2C_ErrorGet() == SERCOM_I2C_ERROR_NONE)
    {
       SERCOM1_I2C_Read(40, I2C_RX, sizeof(I2C_RX)); 
     }
}

//void SPI_CALLBACK()
//{
////    SS_Clear();
////    if((SERCOM2_REGS->SPIM.SERCOM_INTFLAG & SERCOM_SPIM_INTFLAG_DRE_Msk) == SERCOM_SPIM_INTFLAG_DRE_Msk)
//    
//        {
//     SERCOM2_SPI_Read(SPI_RX,sizeof(SPI_RX));
//    SERCOM5_USART_Read(SPI_RX, sizeof(SPI_RX));   
//    }
//    
////    SS_Set();
//}

void GPIO_CALLBACK()
{
    LED1_Toggle();
}

void ADC1_CALLBACK(TC_TIMER_STATUS status, uintptr_t context)
{
    LED_Set();
    SYSTICK_DelayMs (100);  ////take external pull down
    LED_Clear();
    SYSTICK_DelayMs (100);
    
    ADC = ADC_ConversionResultGet();
    printf("ADC = %d\n",ADC);
}

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    ADC_Enable();
    SYSTICK_TimerStart ();
    SYSTICK_TimerPeriodSet (10000);
    TC3_TimerStart();
    SS_Set();
    
    SERCOM0_USART_ReadCallbackRegister( UART_CALLBACK,0);
    SERCOM1_I2C_CallbackRegister(I2C_CALLBACK,0);
    
//    SERCOM2_SPI_CallbackRegister(SPI_CALLBACK,0);
    
    TC3_TimerCallbackRegister( ADC1_CALLBACK, (uintptr_t)NULL );
    EIC_CallbackRegister(EIC_PIN_8, GPIO_CALLBACK, 0);
    
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        SERCOM0_USART_Write( UART_TX, sizeof(UART_TX));
        
//        SERCOM1_I2C_Read(0x40, I2C_RX, sizeof(I2C_RX));
//        SERCOM5_USART_Write(I2C_RX, sizeof(I2C_RX));
        
//        SERCOM1_I2C_WriteRead(40, I2C_TX, sizeof(I2C_TX), I2C_RX, sizeof(I2C_RX));
        
        SERCOM1_I2C_Write(40, I2C_TX, sizeof(I2C_TX)); 
//        SERCOM5_USART_Write(I2C_TX, sizeof(I2C_TX));
        
//        SERCOM2_SPI_Write(SPI_TX,sizeof(SPI_TX));
        
        SS_Clear();
        SERCOM2_SPI_WriteRead(SPI_TX,sizeof(SPI_TX),SPI_RX,sizeof(SPI_RX));
//        SERCOM5_USART_Write(SPI_RX, sizeof(SPI_RX));
        SS_Set();
        
            for(int i=0 ;i<250;i++)
            {
            DAC_DataWrite(ADC);   
            }
        
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

