/*==============================================================================

FILE:      uGPIOInt.c

DESCRIPTION
  This modules implements the API to utilize the Micro GPIO interrupt controller.
  This Micro GPIO Interrupt Controller module is strictly used in USER Protection
  Domain and in Micro image.The definitions in this module are implemented internally
  and should not be exposed for external client usage directly without using the
  accompanying uGPIOInt.h in the core/api/systemdrivers interface file for this module.

REFERENCES

       Copyright (c) 2014-2015 QUALCOMM Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
==============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/GPIOInt/src/user/uimage/uGPIOIntUserIsland.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
1/1/2010   aratin  First draft created. 
===========================================================================*/

// #include "uTimetick.h" so far now not sure about the logging plan.

#include <atomic_ops.h>
#include <qurt.h>
#include "qurt_int.h"
#include "qurt_anysignal.h"
#include "stringl.h"
#include "HALhwio.h"
#include "uGPIOIntHWIO.h"
#include "uGPIOIntUser.h"
#include "uGPIOIntQDI.h"
#include "HALaonint.h"

/*------------------------------------------------------------------------------
 GPIOInt Data Declarations.
------------------------------------------------------------------------------*/ 

/*
 * This is static uGPIOInt state data. It can be accessed for debugging 
 * uGPIO Interrupts to see what is the current registration state of the GPIO.
 */
uGPIOIntCntrlType uGPIOIntData;
//uGPIOIntConfigMapType uGPIOIntConfigMap;

/*------------------------------------------------------------------------------
 GPIOInt Macro Declarations.
------------------------------------------------------------------------------*/ 
#define UGPIOINT_PRIORITY 4

#define VALID_UGPIO(x) ((x) < MAX_NUMBER_OF_GPIOS)
#define VALID_UGPIO_IDX(x) (uGPIOIntData.aGPIOLUT[x] != UGPIOINT_NONE)
#define UGPIOINT_IDX(x) (uGPIOIntData.aGPIOLUT[x])

/* 
 * For each interrupt handler thread a Default IST stack size is declared.
 */
#define GPIOINT_IST_STACK_SIZE  2048

/*------------------------------------------------------------------------------
Following functions are internal functions.
------------------------------------------------------------------------------*/

void uGPIOInt_ISTMain(void * ISTParam);


static uint32 uGPIOInt_GetHighestBmsk
(
   uint32 nSignalMask
)
{
  uint32 nIter;

  if ( nSignalMask == 0x0 || nSignalMask == SIG_INT_ABORT )
  {
    return 0;
  }

  for ( nIter = 0; nIter < 31; nIter++ )
  {
    if ( nSignalMask & ( 0x1 << nIter ) )
    {
      return ( 0x1 << nIter );
    }
  }

  return 0;
}

/*==========================================================================

  FUNCTION      GetGPIOFromSignalMask
 
  DESCRIPTION   This function returns the gpio to be registered by the IST
  that matches the given signal mask.
  
==========================================================================*/

static uint32 GetGPIOFromSignalMask
(
  uint32 nSignalMask
 
)
{
  uint32 nIdx;
  for (nIdx=0; nIdx < MAX_NUMBER_OF_UGPIOS; nIdx++) 
  {
    if (uGPIOIntData.state[nIdx].nInterruptMask & nSignalMask) 
    {
      return (uint32)uGPIOIntData.state[nIdx].nGPIO;
    }
  }
  return UGPIOINT_NONE;
} /* END GetGPIOFromSignalMask */


/*=============================================================================

  FUNCTION      uGPIOInt_ISTMain

  DESCRIPTION   This is the main Micro Interrupt service thread function that 
  processes incoming GPIO interrupts from QURT.

  PARAMETERS
  void * ISTParam  this parameter for now is ignored.

  DEPENDENCIES  None.

  RETURN VALUE  None.

  SIDE EFFECTS  None.


==========================================================================*/
void uGPIOInt_ISTMain
(
  void * ISTParam
)
{
  int                            nStatus;
  uint32                         nTrigger;
  uint32                         gpio;
  uGPIOINTISR                    ClientIsr;
  uGPIOINTISRCtx                 ClientIsrParam;
  //unsigned int nSignalValue;
  
  gpio = UGPIOINT_NONE;
  uGPIOIntData.nThreadID = qurt_thread_get_id();

  /*
   * Main loop.  Process an interrupt IPC, then wait for another.
   */
  while(1)
  {

    while (1)
    {
      unsigned int nSignalValue;
      
      nSignalValue = qurt_anysignal_wait( &uGPIOIntData.ISTSignal, 
                                          UGPIOINT_TASK_INTMASK | SIG_INT_ABORT );
      
      if (SIG_INT_ABORT & nSignalValue)
      {
        /*
         * Clear task stop signal.
         */
        qurt_anysignal_clear(&uGPIOIntData.ISTSignal,SIG_INT_ABORT);
        break;
      }

      nSignalValue = uGPIOInt_GetHighestBmsk(nSignalValue);

      qurt_mutex_lock(&uGPIOIntData.uGPIOIntLock);
      if (nSignalValue & uGPIOIntData.nGPIOIntRegistrationMask)
      {
        /*
         * we get the GPIO and clear the interrupt registration mask that was set.
         */
        gpio = GetGPIOFromSignalMask(nSignalValue & uGPIOIntData.nGPIOIntRegistrationMask);
        if ( gpio == UGPIOINT_NONE ||
             gpio >= MAX_NUMBER_OF_GPIOS ) 
        {
          /*
           * Clear signal that may be recently deregistered.
           */
          nSignalValue &= uGPIOIntData.nGPIOIntRegistrationMask;
          qurt_anysignal_clear(&uGPIOIntData.ISTSignal, nSignalValue);
          qurt_mutex_unlock(&uGPIOIntData.uGPIOIntLock);
          continue;
        }
         /* 
          * Register with QURT using the interrupt vector
          */
        nStatus = qurt_interrupt_register(uGPIOIntData.state[UGPIOINT_IDX(gpio)].qurt_intr_id,&uGPIOIntData.ISTSignal,
                                    uGPIOIntData.state[UGPIOINT_IDX(gpio)].nInterruptMask);

        if ( uGPIOIntData.state[UGPIOINT_IDX(gpio)].nAONID != UGPIOINT_NOAONID )
        {
          /* Register */
          HAL_aonint_Enable ( uGPIOIntData.state[UGPIOINT_IDX(gpio)].nAONID );
        }

        /*
         * Clear registration signal
         */
        uGPIOIntData.nGPIOIntRegistrationMask &= ~nSignalValue;
        qurt_anysignal_clear(&uGPIOIntData.ISTSignal,nSignalValue);

        qurt_mutex_unlock(&uGPIOIntData.uGPIOIntLock); 
        if (nStatus != QURT_EOK) 
        {
          /* throw an error  */
          break;
        }
        continue;     
      }
      else
      {
        qurt_mutex_unlock(&uGPIOIntData.uGPIOIntLock);
      }

      /*
       * If its not a task stop due to deregistration or an error due to qdi
       * we should error fatal if we still do not get the interrupt registration signal.
       */
      if ( !(uGPIOIntData.nGPIOIntMask  & nSignalValue) )
      {
        /* Ideally throw an error in Uimage*/
        break;
      }

      qurt_mutex_lock(&uGPIOIntData.uGPIOIntLock);

      /*
       * find the interrupt that fired.
       */
      gpio = GetGPIOFromSignalMask(nSignalValue);
 
      if((gpio == UGPIOINT_NONE) || (gpio >= MAX_NUMBER_OF_GPIOS))
      {
        /*
         * Could not find the interrupt that fired.
         */
        qurt_mutex_unlock(&uGPIOIntData.uGPIOIntLock);
        continue; 
      }
 
      ClientIsr = uGPIOIntData.state[UGPIOINT_IDX(gpio)].isr;
      ClientIsrParam = uGPIOIntData.state[UGPIOINT_IDX(gpio)].isr_param;

      nTrigger = uGPIOIntData.state[UGPIOINT_IDX(gpio)].intr_trigger;

      qurt_mutex_unlock(&uGPIOIntData.uGPIOIntLock); 

      if ( nTrigger != UGPIOINT_TRIGGER_HIGH &&
           nTrigger != UGPIOINT_TRIGGER_LOW )
      {
        /*
         * Clear signal and reactivate interrupt.
         */
        if ( uGPIOIntData.state[UGPIOINT_IDX(gpio)].nAONID != UGPIOINT_NOAONID )
        {
          /* Clear */
          HAL_aonint_Clear ( uGPIOIntData.state[UGPIOINT_IDX(gpio)].nAONID );
        }

        qurt_anysignal_clear(&uGPIOIntData.ISTSignal,(uGPIOIntData.state[UGPIOINT_IDX(gpio)].nInterruptMask | SIG_INT_ABORT));
        nStatus = qurt_interrupt_acknowledge(uGPIOIntData.state[UGPIOINT_IDX(gpio)].qurt_intr_id);
      }

      if (ClientIsr != NULL) 
      {
        ClientIsr(ClientIsrParam);
      }
      
      if ( nTrigger == UGPIOINT_TRIGGER_HIGH ||
           nTrigger == UGPIOINT_TRIGGER_LOW )
      {
        /*
         * Clear signal and reactivate interrupt.
         */
        if ( uGPIOIntData.state[UGPIOINT_IDX(gpio)].nAONID != UGPIOINT_NOAONID )
        {
          /* Clear */
          HAL_aonint_Clear ( uGPIOIntData.state[UGPIOINT_IDX(gpio)].nAONID );
        }

        qurt_anysignal_clear(&uGPIOIntData.ISTSignal,(uGPIOIntData.state[UGPIOINT_IDX(gpio)].nInterruptMask | SIG_INT_ABORT));
        nStatus = qurt_interrupt_acknowledge(uGPIOIntData.state[UGPIOINT_IDX(gpio)].qurt_intr_id);
      }
    }
  }
} /* END GPIOInt_ISTMain */


/*==========================================================================

   FUNCTION      uGPIOInt_IsInterruptPending

   DESCRIPTION   See uGPIOInt.h

==========================================================================*/
int32
uGPIOInt_IsInterruptPending( uint32  gpio, uint32 *  state)
{
  int nStatus;
  int32 nResult;
  nResult = UGPIOINT_SUCCESS;
  if ((!VALID_UGPIO(gpio))||(!VALID_UGPIO_IDX(gpio)))
  {
    return UGPIOINT_ERROR;
  }
  qurt_mutex_lock(&uGPIOIntData.uGPIOIntLock);
  if (QURT_EOK != qurt_interrupt_status(uGPIOIntData.state[UGPIOINT_IDX(gpio)].qurt_intr_id, &nStatus))
  {
    *state = 0;

    nResult = UGPIOINT_ERROR;
  }
  else 
  {
    if((nStatus == 1)&&(uGPIOIntData.state[UGPIOINT_IDX(gpio)].gpio_intr_flags & UGPIOINTF_REGISTERED))
    {
      *state = 1;
    }
    else
    {
      *state = 0;
    }
  }
 
  qurt_mutex_unlock(&uGPIOIntData.uGPIOIntLock); 

  return nResult;


} /* END uGPIOInt_IsInterruptPending */


/*==========================================================================

   FUNCTION      uGPIOInt_TriggerInterrupt

   DESCRIPTION   See uGPIOInt.h

==========================================================================*/
int32
uGPIOInt_TriggerInterrupt(uint32 gpio)
{
  if ((!VALID_UGPIO(gpio))||(!VALID_UGPIO_IDX(gpio)))
  {
    return UGPIOINT_ERROR;
  }
  qurt_mutex_lock(&uGPIOIntData.uGPIOIntLock);
  qurt_interrupt_raise((unsigned int) uGPIOIntData.state[UGPIOINT_IDX(gpio)].qurt_intr_id); 
  qurt_mutex_unlock(&uGPIOIntData.uGPIOIntLock); 

  return UGPIOINT_SUCCESS;

} /* END uGPIOInt_TriggerInterrupt */



