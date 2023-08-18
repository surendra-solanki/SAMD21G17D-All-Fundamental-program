/*******************************************************************************
  Real Time Counter (RTC) PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_rtc_timer.c

  Summary:
    RTC PLIB Implementation file

  Description:
    This file defines the interface to the RTC peripheral library. This
    library provides access to and control of the associated peripheral
    instance in timer mode.

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

#include "plib_rtc.h"
#include "device.h"
#include <stdlib.h>
#include <limits.h>
#include "interrupts.h"

 static RTC_OBJECT rtcObj;

static void RTC_CountReadSynchronization(void)
{
   /* Enable continuous read-synchronization for COUNT register */
   if( (RTC_REGS->MODE1.RTC_READREQ & RTC_READREQ_RCONT_Msk) != RTC_READREQ_RCONT_Msk)
   {
       RTC_REGS->MODE1.RTC_READREQ = RTC_READREQ_RCONT_Msk | RTC_READREQ_ADDR(0x10U);
       RTC_REGS->MODE1.RTC_READREQ |= RTC_READREQ_RREQ_Msk;
       while((RTC_REGS->MODE1.RTC_STATUS & RTC_STATUS_SYNCBUSY_Msk) == RTC_STATUS_SYNCBUSY_Msk)
       {
           /* Wait for Read-Synchronization */
       }
   }
}

void RTC_Initialize(void)
{
   /* Writing to CTRL register will trigger write-synchronization */
   RTC_REGS->MODE1.RTC_CTRL = RTC_MODE1_CTRL_SWRST_Msk;
   while((RTC_REGS->MODE1.RTC_STATUS & RTC_STATUS_SYNCBUSY_Msk) == RTC_STATUS_SYNCBUSY_Msk)
   {
       /* Wait for Write-Synchronization */
   }

   /* Writing to CTRL register will trigger write-synchronization */
   RTC_REGS->MODE1.RTC_CTRL = RTC_MODE1_CTRL_MODE(1U) | RTC_MODE1_CTRL_PRESCALER(0x0U);

   /* Writing to COMP register will trigger write-synchronization */
   RTC_REGS->MODE1.RTC_COMP[0] = 0x512U;
   while((RTC_REGS->MODE1.RTC_STATUS & RTC_STATUS_SYNCBUSY_Msk) == RTC_STATUS_SYNCBUSY_Msk)
   {
       /* Wait for Write-Synchronization */
   }

   /* Writing to COMP register will trigger write-synchronization */
   RTC_REGS->MODE1.RTC_COMP[1] = 0x0U;
   while((RTC_REGS->MODE1.RTC_STATUS & RTC_STATUS_SYNCBUSY_Msk) == RTC_STATUS_SYNCBUSY_Msk)
   {
       /* Wait for Write-Synchronization */
   }

   /* Writing to PER register will trigger write-synchronization */
   RTC_REGS->MODE1.RTC_PER = 0xffffU;
   while((RTC_REGS->MODE1.RTC_STATUS & RTC_STATUS_SYNCBUSY_Msk) == RTC_STATUS_SYNCBUSY_Msk)
   {
       /* Wait for Write-Synchronization */
   }

   RTC_REGS->MODE1.RTC_INTENSET = 0x41U;

   /* Enable continuous read request for COUNT register */
   RTC_CountReadSynchronization();
}



void RTC_Timer16Start ( void )
{
   /* Writing to CTRL register will trigger write-synchronization */
   RTC_REGS->MODE1.RTC_CTRL |= RTC_MODE1_CTRL_ENABLE_Msk;
   while((RTC_REGS->MODE1.RTC_STATUS & RTC_STATUS_SYNCBUSY_Msk) == RTC_STATUS_SYNCBUSY_Msk)
   {
       /* Wait for Write-Synchronization */
   }
}

void RTC_Timer16Stop ( void )
{
   /* Writing to CTRL register will trigger write-synchronization */
   RTC_REGS->MODE1.RTC_CTRL &= ~(RTC_MODE1_CTRL_ENABLE_Msk);
   while((RTC_REGS->MODE1.RTC_STATUS & RTC_STATUS_SYNCBUSY_Msk) == RTC_STATUS_SYNCBUSY_Msk)
   {
       /* Wait for Write-Synchronization */
   }
}

void RTC_Timer16CounterSet ( uint16_t count )
{
   /* Writing to COUNT register will trigger write-synchronization */
   RTC_REGS->MODE1.RTC_COUNT = count;
   while((RTC_REGS->MODE1.RTC_STATUS & RTC_STATUS_SYNCBUSY_Msk) == RTC_STATUS_SYNCBUSY_Msk)
   {
       /* Wait for Write-Synchronization */
   }
}

void RTC_Timer16PeriodSet ( uint16_t period )
{
   /* Writing to PER register will trigger write-synchronization */
   RTC_REGS->MODE1.RTC_PER = period;
   while((RTC_REGS->MODE1.RTC_STATUS & RTC_STATUS_SYNCBUSY_Msk) == RTC_STATUS_SYNCBUSY_Msk)
   {
       /* Wait for Write-Synchronization */
   }
}

uint16_t RTC_Timer16CounterGet ( void )
{
   /* Enable read-synchronization for COUNT register to avoid CPU stall */
   RTC_CountReadSynchronization();

   return(RTC_REGS->MODE1.RTC_COUNT);
}

uint16_t RTC_Timer16PeriodGet ( void )
{
   return (RTC_REGS->MODE1.RTC_PER);
}

void RTC_Timer16Compare0Set ( uint16_t comparisionValue )
{
   /* Writing to COMP register will trigger write-synchronization */
   RTC_REGS->MODE1.RTC_COMP[0] = comparisionValue;
   while((RTC_REGS->MODE1.RTC_STATUS & RTC_STATUS_SYNCBUSY_Msk) == RTC_STATUS_SYNCBUSY_Msk)
   {
       /* Wait for Write-Synchronization */
   }
}

void RTC_Timer16Compare1Set ( uint16_t comparisionValue )
{
   /* Writing to COMP register will trigger write-synchronization */
   RTC_REGS->MODE1.RTC_COMP[1] = comparisionValue;
   while((RTC_REGS->MODE1.RTC_STATUS & RTC_STATUS_SYNCBUSY_Msk) == RTC_STATUS_SYNCBUSY_Msk)
   {
       /* Wait for Write-Synchronization */
   }
}

uint32_t RTC_Timer16FrequencyGet ( void )
{
   return RTC_COUNTER_CLOCK_FREQUENCY;
}


void RTC_Timer16InterruptEnable(RTC_TIMER16_INT_MASK interrupt)
{
   RTC_REGS->MODE1.RTC_INTENSET = (uint8_t)interrupt;
}

void RTC_Timer16InterruptDisable(RTC_TIMER16_INT_MASK interrupt)
{
   RTC_REGS->MODE1.RTC_INTENCLR = (uint8_t)interrupt;
}



void RTC_Timer16CallbackRegister ( RTC_TIMER16_CALLBACK callback, uintptr_t context )
{
   rtcObj.timer16BitCallback = callback;

   rtcObj.context            = context;
}

void RTC_InterruptHandler(void)
{
   /* Update the event in RTC Peripheral Callback object */
   rtcObj.timer16intCause = (RTC_TIMER16_INT_MASK) RTC_REGS->MODE1.RTC_INTFLAG;
   RTC_REGS->MODE1.RTC_INTFLAG = RTC_MODE1_INTFLAG_Msk;

   /* Invoke registered Callback function */
   if(rtcObj.timer16BitCallback != NULL)
   {
       rtcObj.timer16BitCallback( rtcObj.timer16intCause, rtcObj.context );
   }
}
