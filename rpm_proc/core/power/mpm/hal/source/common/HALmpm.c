/*
===========================================================================

FILE:         HALmpm.c

DESCRIPTION:  
  This is the generic hardware abstraction layer implementation for the
  MPM Hardware. MPM Interrupt controller abstraction is done in HALmpmint.c

===========================================================================

                             Edit History

$Header: //components/rel/rpm.bf/1.8/core/power/mpm/hal/source/common/HALmpm.c#1 $

when       who     what, where, why
--------   ---     --------------------------------------------------------
04/09/12   mda     MPMv2 for 8974

===========================================================================
          Copyright (c) 2008-20016 Qualcomm Technologies, Inc.
                    All Rights Reserved.
              QUALCOMM Proprietary and Confidential
===========================================================================
*/

/* -----------------------------------------------------------------------
**                           INCLUDES
** ----------------------------------------------------------------------- */

#include "CoreVerify.h"
#include "HALmpmInternal.h"
#include "pm_app_clk.h"
#include "pm_clk_sleep.h"
#include "pm_clk_xo.h"
#include "Chipinfo.h"


/* -----------------------------------------------------------------------
**                           Declarations
** ----------------------------------------------------------------------- */
extern void HAL_mpm_CfgWbootEbiIOCntl  ( bool32 wbootFreezeEBI1, 
                                         bool32 wbootFreezeEBI2 );

extern void HAL_mpm_JTAGEnable         ( void );

void HAL_mpm_true_sleep_xtal_set       ( void );
static uint32_t tcxo_latency;

/* -----------------------------------------------------------------------
**                           TYPES
** ----------------------------------------------------------------------- */

/*------------------------------------------------------------------------
**                          External References
**------------------------------------------------------------------------ */
extern pm_on_off_type tcxo_on;

/*
 * Identifier string for this HAL.
 */
#define HAL_MPM_VERSION_STRING "HAL_MPM_V2"

extern HAL_mpm_PlatformType mpmPlatform;

__attribute__((section("mpm_cram_reclaim_pool")))
void HAL_mpm_Init_Xtal_Latency(void)
{
  uint32_t            cxoWarmup = 0;
  BSP_mpm_MpmCfgType *mpmCfgPtr = &((mpmPlatform.mpmCfg)->mpmCfg);
  tcxo_latency = (tcxo_on == PM_ON ? /* ~4 msec in 32kHz ticks */ 130 : 0);

  if (tcxo_on == PM_ON)
  {
    HAL_mpm_true_sleep_xtal_set();
    pm_clk_xo_set_warmup_time(0, PM_CLK_XO, /* ~4 msec in 32kHz ticks */ 130);
  }

  /* get xo warmup from pmic in usec */
  CORE_VERIFY(PM_ERR_FLAG__SUCCESS == pm_app_clk_get_xo_warmup_time(&cxoWarmup));

  /* convert usec to sclks (32KHz) */
  cxoWarmup = (cxoWarmup * 32) / 1000;
  /* program xo warmup delays */
  cxoWarmup  = MAX(mpmCfgPtr->wakeupDelays.cxoDelay, cxoWarmup);

  if (0 != cxoWarmup)
    HAL_mpm_SetCXOWarmup(cxoWarmup);
}

/* ===========================================================================
**  HAL_mpm_Init
**
** ======================================================================== */
__attribute__((section("mpm_dram_reclaim_pool")))
void HAL_mpm_Init               ( char **ppszVersion )
{
  BSP_mpm_MpmCfgType     *mpmCfgPtr  = NULL;
  BSP_mpm_PeriCfgType    *periCfgPtr = NULL;

  mpmPlatform.mpmCfg = &( MPM_BSP_DATA );
  HAL_mpm_PlatformInitEarly( &mpmPlatform );

  mpmCfgPtr  = &((mpmPlatform.mpmCfg)->mpmCfg);
  periCfgPtr = &((mpmPlatform.mpmCfg)->periCfg);

  /* Initialize MPM with platform specific settings */
  HAL_mpm_CfgWbootEbiIOCntl         ( (mpmCfgPtr->ioCfg).wbootFreezeEBI1,
                                      (mpmCfgPtr->ioCfg).wbootFreezeEBI2 );
  HAL_mpm_ConfigDebugBus            ( mpmCfgPtr->dbgBusEnable );
  HAL_mpm_ConfigDebugBus_1          ( mpmCfgPtr->dbgBusEnable_1 );
  HAL_mpm_DebugThroughPC            ( mpmCfgPtr->dbgThroughPCEnable );
                                   
  HAL_mpm_PenDebounceCtl            ( (periCfgPtr->penDebounceCfg).enable );
  HAL_mpm_ConfigPenDebounceDelay    ( (periCfgPtr->penDebounceCfg).delay );
                                   
  /*
   * Fill in return value
   */
  if (ppszVersion != NULL)
  {
    *ppszVersion = (char*)HAL_MPM_VERSION_STRING;
  }

  if(Chipinfo_GetVersion() >= MPM_BSP_DATA.wakeupTsMinimumHwVersion)
  {
      HAL_mpm_EnableWakeUpIntTimestamp();
  }
}

uint32_t HAL_mpm_GetTCXOLatency(void)
{
  return tcxo_latency;
}

/* ===========================================================================
**  HAL_mpm_Reset
**
** ======================================================================== */
void HAL_mpm_Reset( void )
{
  /*TBD*/
}

/* ===========================================================================
**  HAL_mpm_Save
**
** ======================================================================== */
void HAL_mpm_Save ( void )
{
  /*Not supported. MPM hardware is always-on*/
}

/* ===========================================================================
**  HAL_mpm_Restore
**
** ======================================================================== */
void HAL_mpm_Restore ( void )
{
  /*Not supported. MPM hardware is always-on*/
}

