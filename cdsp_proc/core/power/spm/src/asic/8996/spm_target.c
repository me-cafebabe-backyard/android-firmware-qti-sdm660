/*==============================================================================
  FILE:         spm_target.c

  OVERVIEW:     This file implements any target specific functions for SPM.

  DEPENDENCIES: None

  NOTES:        This needs to be refactored once full DeviceCfg (or equivalent)
                support is present.
                
                Copyright (c) 2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.qdsp6/1.0.c2/power/spm/src/asic/8996/spm_target.c#1 $
$DateTime: 2020/02/10 01:57:30 $
================================================================================*/
#include "comdef.h"
#include "spm.h"

/*=======================================================================
 *                             INTERNAL VARIABLES
 *======================================================================*/
/* Global variables to be used by driver. This must be set up during
 * target initialization. */
spm_t   *g_spms     = NULL;
uint32  g_spmCount  = 0;

/* Externed variables containing SPM configuration information */
extern spm_t g_spmInstances[];

/*=======================================================================
 *                             GLOBAL FUNCTIONS
 *======================================================================*/
/*
 * spm_target_init
 */ 
void spm_target_init()
{
  g_spms     = g_spmInstances;
  g_spmCount = 1;

  return;
}
