/*==============================================================================
  FILE:         spm_env.c

  OVERVIEW:     This file sets up the environment where SPM is running. It can
                be different based on different processors/OS/Exception level
                it may run.

  DEPENDENCIES: Environment specific.
                SPM_SS_BASE - must be defined in build script.
                
                Copyright (c) 2015 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================ 
$Header: //components/rel/core.qdsp6/1.0.c2/power/spm/src/env/q6/spm_env.c#1 $
$DateTime: 2020/02/10 01:57:30 $
==============================================================================*/
#include "msmhwiobase.h"
#include "CoreVerify.h"
#include "spm.h"
#include "DALDeviceId.h"
#include "DDIHWIO.h"

/*=======================================================================
 *                             INTERNAL VARIABLES
 *======================================================================*/
/**
 * Generating base address to send to HWIO 
 */
uint8 *g_spmBasePtrAddress = NULL;

#define SSTR(x) STR(x)
#define STR(x) #x

/*==========================================================================
 *                            GLOBAL FUNCTIONS
 *=========================================================================*/
/*
 * spm_env_init
 */
void spm_env_init(spm_handle handle)
{
  DalDeviceHandle *spmDALHandle;
  DALResult       eResult;

  eResult = DAL_DeviceAttach(DALDEVICEID_HWIO, &spmDALHandle);
  if (eResult == DAL_SUCCESS)
  {
    DalHWIO_MapRegion(spmDALHandle, SSTR(SPM_BASE_NAME), &g_spmBasePtrAddress);
  }
  
  CORE_VERIFY(NULL != g_spmBasePtrAddress);
  handle->addr = g_spmBasePtrAddress;

  return;
}

