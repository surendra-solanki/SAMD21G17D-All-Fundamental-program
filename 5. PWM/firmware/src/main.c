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
 float x,y;
float Period_Set(float x)
{
    float z=48000000,i;
    i=z/x;
    return i;
}

float Duty_Set(float y,float x)
{
    float z;
    z= (Period_Set(x)*y)/100;
    return z;
}

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
   printf("This is PWM\n");
   
    while (true)
    {
    /* Maintain state machines of all polled MPLAB Harmony modules. */
    SYS_Tasks ( );
    
    printf("If you want to change frequency press:1\n");
    printf("If you want to change Duty Cycle press:2\n");
    int a;
    scanf("%d",&a);
    
    switch(a)
    {
        case 1: printf("Enter value of period in KHZ :");
                scanf("%f",&x);
                break;
        
        case 2: printf("Enter value of duty cycle in percentage :");
                scanf("%f",&y);
                break;
        
        default:printf("You enter wrong Input");
        break;
    }
    
    
    
    
    TCC0_PWMStart();
    
    TCC0_PWM24bitPeriodSet(Period_Set(x));
    TCC0_PWM24bitDutySet(1,Duty_Set(y,x));
    /* Execution should not come here during normal operation */
    }
    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

