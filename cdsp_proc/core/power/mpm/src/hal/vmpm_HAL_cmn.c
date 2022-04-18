/*============================================================================
  
  FILE:         vmpm_HAL_cmn.c
  
  DESCRIPTION:  This is the common hardware abstraction layer implementation 
                for the MPM interrupt controller.
  
  DEPENDENCIES: None

                Copyright (c) 2016 QUALCOMM Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Confidential and Proprietary

===============================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/mpm/src/hal/vmpm_HAL_cmn.c#1 $
$DateTime: 2020/02/10 01:57:30 $
=============================================================================*/ 
#include "comdef.h"
#include "vmpm_HAL.h"
#include "vmpm_HAL_Internal.h"
#include "rpm_messageram.h"

/*=============================================================================
 *                             GLOBAL FUNCTIONS
 *============================================================================*/
/*
 * vmpm_HAL_All_Clear
 */
void vmpm_HAL_All_Clear( void )
{
  uint32                nNumRegs, regIndex;
  volatile vmpm_data_t  *msgRam = vmpm_getProcMpmBaseVA();

  vmpm_HAL_GetNumberMasks(&nNumRegs);

  for( regIndex = 0; regIndex < nNumRegs; regIndex++ )
  {
    msgRam->vmpm_status[regIndex] = 0x0;
  }

  /* No need to notify the RPM, since it has nothing to do in response to
   * a clear. */

}

/*
 * vmpm_HAL_GetNumberMasks
 */
void vmpm_HAL_GetNumberMasks( uint32 *pnNumber )
{
  volatile vmpm_data_t *msgRam = vmpm_getProcMpmBaseVA();

  *pnNumber = sizeof(msgRam->vmpm_enable) / sizeof(msgRam->vmpm_enable[0]);
  return;
}

/*
 * vmpm_HAL_GetNumberMasks
 */
void vmpm_HAL_GetPending ( uint32 nMaskIndex, 
                           uint32 *pnMask )
{
  uint32                nNumRegs;
  volatile vmpm_data_t  *msgRam = vmpm_getProcMpmBaseVA();

  vmpm_HAL_GetNumberMasks(&nNumRegs);

  if((nMaskIndex >= nNumRegs) || (!pnMask))
    return;

  *pnMask = ( msgRam->vmpm_status[nMaskIndex] & msgRam->vmpm_enable[nMaskIndex] );
}

