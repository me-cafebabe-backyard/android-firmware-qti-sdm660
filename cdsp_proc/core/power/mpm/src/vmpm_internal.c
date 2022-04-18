/*===========================================================================
  FILE:         vmpm_internal.c
  
  OVERVIEW:     This file contains the necessary functions to interface
                the MPM IC hardware registers.

  DEPENDENCIES: None

                Copyright (c) 2013-2014,2016 QUALCOMM Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Confidential and Proprietary

===============================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/mpm/src/vmpm_internal.c#1 $
$DateTime: 2020/02/10 01:57:30 $
=============================================================================*/ 
#include "CoreString.h"
#include "vmpm_internal.h"
#include "vmpm_HAL.h"
#include "vmpm_types.h"
#include "CoreVerify.h"
#include "vmpm.h"

/*===========================================================================
 *                           EXTERNAL VARIABLES
 *===========================================================================*/
extern uint32 g_mpmMapTblSize;

/*===========================================================================
 *                      STATIC VARIABLE DEFINITIONS
 *===========================================================================*/
static uint32 s_mpmNumMappedIrqs  = 0;
static uint32 s_mpmNumMappedGpios = 0;

/*============================================================================
 *                      EXTERNAL FUNCTION DECLARATIONS
 *===========================================================================*/
/*
 * vmpm_setMapTblData
 */
void vmpm_setMapTblData(mpm_int_pin_mapping_type *mappingTablePtr)
{
#ifdef UMPM_ISLAND_MODE_ENABLE
  /* Make a local copy of the table data so island can access it */
  memscpy(vmpm_pinMapTbl, 
          sizeof(mpm_int_pin_mapping_type) * MPM_MAX_NUM_INTS,
          mappingTablePtr, 
          sizeof(mpm_int_pin_mapping_type) * vmpm_getMapTblSize());
#else
  /* Otherwise, just set the pointer to the given data */
  vmpm_pinMapTbl = mappingTablePtr;
#endif

  return;
}

/**
 * vmpm_setMapTblSize
 */
void vmpm_setMapTblSize( mpm_int_pin_mapping_type *tableData )
{
  uint32                cnt     = 0;
  volatile vmpm_data_t  *msgram = vmpm_getProcMpmBaseVA();
  
  if (NULL == tableData)
  {
    g_mpmMapTblSize = 0;
    return;
  }

  /* Calculate actual table size */
  while( MPM_EOT != tableData[cnt].mpm_pin_type )
  { 
    cnt++;
  }

  /* Does not include MPM_EOT entry in count */
  g_mpmMapTblSize = cnt;
  
  /* Ensure table entries are no more than the max supported */
  CORE_VERIFY(g_mpmMapTblSize <= MPM_MAX_NUM_INTS);

  /* Ensure the mapped interrupts fit into the RPM defined message ram by using the number
   * of enable registers */
  CORE_VERIFY(((g_mpmMapTblSize + 31) / 32) <= 
              (sizeof(msgram->vmpm_enable) / sizeof(msgram->vmpm_enable[0])));
}

/**
 * @brief Determines the number of interrupts (IRQs) that are 
 *        mapped to mpm.
 *
 * @return As above
 */
void vmpm_setNumMappedIrqs( void )
{
  uint32 idx = 0;
  uint32 mpmIrqCnt = 0;

  for ( idx = 0; idx < vmpm_getMapTblSize(); idx++ ) 
  {
    if( MPM_SUCCESS == vmpm_IsIrq(idx) )
    {
      mpmIrqCnt++;
    }
  }

  s_mpmNumMappedIrqs = mpmIrqCnt;
}

/**
 * @brief Returns the number of interrupts (IRQs) that are mapped to mpm for
 *        a master processor
 *
 * @return As above
 */
uint32 vmpm_getNumMappedIrqs( void )
{
  return s_mpmNumMappedIrqs;
}

/**
 * @brief Determines the number of GPIOs that are mapped to mpm
 *        for a master processor
 *
 * @return As above
 */
void vmpm_setNumMappedGpios( void )
{
  uint32 idx = 0;
  uint32 mpmGpioCnt = 0;

  for ( idx = 0; idx < vmpm_getMapTblSize(); idx++ ) 
  {
    if( MPM_SUCCESS == vmpm_IsGpio( idx) )
    {
      mpmGpioCnt++;
    }
  }

  s_mpmNumMappedGpios = mpmGpioCnt;
}

/**
 * @brief Returns the number of GPIOs that are mapped to mpm for
 *        a master processor
 *
 * @return As above
 */
uint32 vmpm_getNumMappedGpios( void )
{
  return s_mpmNumMappedGpios;
}

