/*==============================================================================
  FILE:         vmpm_cmn.c

  OVERVIEW:     This file provides the common functionality for the 
                Subsystem.

  DEPENDENCIES: None

                Copyright (c) 2016 QUALCOMM Technologies Inc (QTI).
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/mpm/src/vmpm_cmn.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "vmpm_utils.h"
#include "vmpm_hw_hwio.h"
#include "vmpm_HAL_Internal.h"
#include "vmpm_internal.h"
#include "vmpm_types.h"
#include "CoreIntrinsics.h"
#include "rpm_messageram.h"

/*==========================================================================
 *                      GLOBAL VARIABLES DECLARATIONS
 *==========================================================================*/
/* Pointer to mpm<->master interrupt/gpio mapping table
 * If island is enabled, the data must be copied to an island accessable table
 * If island is disabled, then the devcfg data table can be used directly */
#ifdef UMPM_ISLAND_MODE_ENABLE
mpm_int_pin_mapping_type vmpm_pinMapTbl[MPM_MAX_NUM_INTS];
#else
mpm_int_pin_mapping_type *vmpm_pinMapTbl;
#endif

/* Supported interrupt table size */
uint32 g_mpmMapTblSize = 0;

/* After initialization, this variable will be contain the Virtual Address
 * for the RPM message ram for the particular master */ 
volatile vmpm_data_t *g_messageRamBase = 0;

/*===========================================================================
 *                        GLOBAL FUNCTION DEFINITIONS
 *=========================================================================*/
/* Accessor function for static variable g_messageRamBase */
volatile vmpm_data_t* vmpm_getProcMpmBaseVA( void )
{
   return g_messageRamBase;
}

/*
 * vmpm_SetWakeupTimetick
 */
void vmpm_SetWakeupTimetick(uint64_t wakeupTick)
{
  volatile vmpm_data_t *msgRam = vmpm_getProcMpmBaseVA();

  msgRam->wakeup_time = wakeupTick;

  return;
}

/*
 * vmpm_getMapTblSize
 */
uint32 vmpm_getMapTblSize( void )
{
  return g_mpmMapTblSize;
}

/*
 * vmpm_IsGpio
 */
mpm_status_type vmpm_IsGpio( uint32 mpmPinNum )
{
  mpm_status_type status = MPM_FAIL;

  if( ( mpmPinNum < vmpm_getMapTblSize() ) &&
      ( MPM_GPIO == vmpm_pinMapTbl[mpmPinNum].mpm_pin_type )  &&
      ( vmpm_pinMapTbl[mpmPinNum].local_pin_num < MPM_MAX_LOC_IC_VAL ) )
  {
    status = MPM_SUCCESS;
  }

  return status;
}

/*
 * vmpm_IsIrq
 */
mpm_status_type vmpm_IsIrq( uint32 mpmPinNum )
{
  mpm_status_type status = MPM_FAIL;

  if( ( mpmPinNum < vmpm_getMapTblSize() ) &&
      ( MPM_IRQ == vmpm_pinMapTbl[mpmPinNum].mpm_pin_type ) &&
      ( vmpm_pinMapTbl[mpmPinNum].local_pin_num < MPM_MAX_LOC_IC_VAL ) )
  {
    status = MPM_SUCCESS;
  }

  return status;
}

/*
 * vmpm_IsPinSupported
 */
mpm_status_type vmpm_IsPinSupported( uint32 mpmPinNum )
{
  if ( (mpmPinNum < vmpm_getMapTblSize()) &&
       (MPM_OPEN != vmpm_pinMapTbl[mpmPinNum].mpm_pin_type) )
  {
    return MPM_SUCCESS;
  }
  else
  {
    return MPM_FAIL;
  }
}

/*
 * vmpm_getIrqNum
 */
mpm_status_type  vmpm_getIrqNum( uint32 nMPM, uint32 *ptr_IrqNum )
{
  mpm_status_type bIsWakeupIRQ = MPM_FAIL;

  if( ( MPM_FAIL == vmpm_IsIrq(nMPM) ) || 
       ( NULL == ptr_IrqNum ) )
  {
    /* Invalid input */
    return bIsWakeupIRQ;
  }

  if( MPM_IRQ == vmpm_pinMapTbl[nMPM].mpm_pin_type )
  {
    /* Given entry in mapping table is a valid IRQ */
    *ptr_IrqNum = vmpm_pinMapTbl[nMPM].local_pin_num;
    bIsWakeupIRQ = MPM_SUCCESS;
  }

  return bIsWakeupIRQ;
}

/*
 * vmpm_getGpioNum
 */
mpm_status_type  vmpm_getGpioNum( uint32 nMPM, uint32 *ptr_GpioNum )
{
  mpm_status_type status = MPM_FAIL;

  if( ( MPM_FAIL == vmpm_IsGpio(nMPM) ) || 
      ( NULL == ptr_GpioNum ) )
  {
    /* Invalid input */
    return status;
  }

  if( MPM_GPIO == vmpm_pinMapTbl[nMPM].mpm_pin_type )
  {
    /* Given entry in mapping table is a valid GPIO */
    *ptr_GpioNum = vmpm_pinMapTbl[nMPM].local_pin_num;
    status = MPM_SUCCESS;
  }

  return status;
}

/**
 * vmpm_retriggerInternal
 */
void vmpm_retriggerInternal(mpm_retrigger_functions *triggerFunctions)
{
  uint32  numMasks, status, temp, mpmPinNum;
  uint32  intNum, i;
  
  vmpm_HAL_GetNumberMasks(&numMasks);

  for(i = 0; i < numMasks; i++)
  {
    vmpm_HAL_GetPending(i, &status);

    temp = status;
    while(temp)
    {
      /* Get the next interrupt's physical id and remove it for the future */
      mpmPinNum = (31 - CoreCountLeadingZeros32(temp)) + (32 * i);
      temp      &= ~(1 << (31 - CoreCountLeadingZeros32(temp)));

      /* try to figure out which interrupt it is */
      if(MPM_FAIL == vmpm_IsPinSupported(mpmPinNum))
      {
        continue;
      }

      /* If it's a gpio, perform soft-trigger into that driver */
      if(MPM_SUCCESS == vmpm_getGpioNum(mpmPinNum, &intNum))
      {
        triggerFunctions->log_message(4, "GPIO soft trigger " 
                                         "(num: %u) (bit: %u) " 
                                         "(pending mask num: %u) "
                                         "(pending mask: 0x%x)", 
                                         intNum, mpmPinNum, i, status);

        triggerFunctions->gpio_retrigger(intNum);
      }
      /* Else check if it was a wakeup irq */
      else if(MPM_SUCCESS == vmpm_getIrqNum(mpmPinNum, &intNum))
      {
        triggerFunctions->log_message(4, "Interrupt soft trigger " 
                                         "(num: %u) (bit: %u) " 
                                         "(pending mask num: %u) "
                                         "(pending mask: 0x%x)", 
                                         intNum, mpmPinNum, i, status);

        triggerFunctions->int_retrigger(intNum);
      }
    } /* end of while(temp) */
  }

  /* Clearing all interrupts for next cycle */
  vmpm_HAL_All_Clear();
}

