/*==============================================================================
  FILE:         spm.c

  OVERVIEW:     This file implements some of the APIs defined in spm public 
                header file to interact with SPM HW block(s).

  DEPENDENCIES: None
                
                Copyright (c) 2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/spm/src/common/spm_cmn.c#1 $
$DateTime: 2020/02/10 01:57:30 $
================================================================================*/
#include "spm.h"
#include "spm_hal.h"
#include "spm_hal_bsp.h"
#include "spm_internal.h"

/*=======================================================================
 *                     GLOBAL SPM INSTANCE FUNCTIONS
 *======================================================================*/
/*
 * spm_instance_set_rpm_handshake
 */
spm_result_t spm_instance_set_rpm_handshake(spm_handle handle, boolean handshake)
{
  if(!SPM_VALID_HANDLE(handle))
    return SPM_INVALID_HANDLE;

  spm_hal_config_rpm_handshake(handle->addr, (handshake ? 1 : 0));

  return SPM_SUCCESS;
}

