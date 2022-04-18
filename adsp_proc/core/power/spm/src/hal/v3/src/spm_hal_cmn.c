/*==============================================================================
  FILE:         spm_hal_cmn.c

  OVERVIEW:     This is the commong generic hardware abstraction layer implementation
                for the SPMv3 (SAW3) Hardware.

  DEPENDENCIES: None
  
                Copyright (c) 2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/spm/src/hal/v3/src/spm_hal_cmn.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "spm_hal.h"
#include "spm_hwio.h"

/*===========================================================================
 *                            EXTERNAL FUNCTIONS
 *==========================================================================*/
/*
 * spm_hal_config_rpm_handshake
 */
void spm_hal_config_rpm_handshake(uint8 *spm_base, uint8 rpm_hs)
{
  rpm_hs = (0 != rpm_hs) ? 1 : 0;
  SPM_HWIO_OUTF(spm_base, SPM_CTL, SLP_CMD_MODE, rpm_hs);
}

