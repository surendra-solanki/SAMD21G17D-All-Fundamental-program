/*******************************************************************************
  Real Time Counter (RTC) PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_rtc.h

  Summary:
    RTC PLIB Header file

  Description:
    This file defines the interface to the RTC peripheral library. This
    library provides access to and control of the associated peripheral
    instance.

*******************************************************************************/
// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef PLIB_RTC_H
#define PLIB_RTC_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

/* Frequency of Counter Clock for RTC */
#define RTC_COUNTER_CLOCK_FREQUENCY        (48000000U / (1UL << (0x0U)))

typedef enum
{
    RTC_TIMER16_INT_MASK_COMPARE0_MATCH = 0x0001,
    RTC_TIMER16_INT_MASK_COMPARE1_MATCH = 0x0002,
    RTC_TIMER16_INT_MASK_PERIOD_MATCH = 0x0080,
} RTC_TIMER16_INT_MASK;

typedef void (*RTC_TIMER16_CALLBACK)( RTC_TIMER16_INT_MASK intCause, uintptr_t context );


typedef struct
{
    /* Timer 16Bit */
    RTC_TIMER16_CALLBACK timer16BitCallback;
    RTC_TIMER16_INT_MASK timer16intCause;
    uintptr_t context;
} RTC_OBJECT;

void RTC_Initialize(void);

void RTC_Timer16Start ( void );
void RTC_Timer16Stop ( void );
void RTC_Timer16CounterSet ( uint16_t count );
void RTC_Timer16PeriodSet ( uint16_t period );
uint16_t RTC_Timer16PeriodGet ( void );
uint16_t RTC_Timer16CounterGet ( void );
uint32_t RTC_Timer16FrequencyGet ( void );
void RTC_Timer16Compare0Set ( uint16_t comparisionValue );
void RTC_Timer16Compare1Set ( uint16_t comparisionValue );
void RTC_Timer16InterruptEnable(RTC_TIMER16_INT_MASK interrupt);
void RTC_Timer16InterruptDisable(RTC_TIMER16_INT_MASK interrupt);

void RTC_Timer16CallbackRegister ( RTC_TIMER16_CALLBACK callback, uintptr_t context );

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
}
#endif
// DOM-IGNORE-END

#endif /* PLIB_RTC_H */
