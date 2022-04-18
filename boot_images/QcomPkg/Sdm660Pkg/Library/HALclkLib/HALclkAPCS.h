#ifndef __HALCLKAPCS_H__
#define __HALCLKAPCS_H__

/*
===========================================================================
*/
/**
  @file HALclkAPCS.h

  Header APCS-specific HAL functions.
*/
/*
  ====================================================================

  Copyright (c) 2013-2015 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================


  ====================================================================
*/

/* ============================================================================
**    Include files
** ==========================================================================*/

#include "HALclkInternal.h"


/* ============================================================================
**    Definitions
** ==========================================================================*/


/*
 * Common APCS MUX config fields/masks (*_GFM)
 */
#define HAL_CLK_GFM_CLUST_CLK_ON_FMSK                                  0x80000000
#define HAL_CLK_GFM_CLUST_CLK_ON_SHFT                                  0x1f
#define HAL_CLK_GFM_SEC_PLL_MAIN_DIV_FMSK                              0x00000040
#define HAL_CLK_GFM_SEC_PLL_MAIN_DIV_SHFT                              0x6
#define HAL_CLK_GFM_PRI_PLL_MAIN_DIV_FMSK                              0x00000020
#define HAL_CLK_GFM_PRI_PLL_MAIN_DIV_SHFT                              0x5
#define HAL_CLK_GFM_GFMUX_SRC_SEL_HF_FMSK                              0x00000018
#define HAL_CLK_GFM_GFMUX_SRC_SEL_HF_SHFT                              0x3
#define HAL_CLK_GFM_GFMUX_SRC_SEL_LF_FMSK                              0x00000006
#define HAL_CLK_GFM_GFMUX_SRC_SEL_LF_SHFT                              0x1
#define HAL_CLK_GFM_CLK_GATE_FMSK                                      0x00000001
#define HAL_CLK_GFM_CLK_GATE_SHFT                                      0x0

#define HAL_CLK_GFM_CCI_PLL_MAIN_DIV_FMSK                              0x00000080
#define HAL_CLK_GFM_CCI_PLL_MAIN_DIV_SHFT                              0x7
#define HAL_CLK_GFM_CCI_CLK_DIV_FMSK                                   0x00000060
#define HAL_CLK_GFM_CCI_CLK_DIV_SHFT                                   0x5


/* ============================================================================
**    Typedefs
** ==========================================================================*/

/**
 * Enumeration of CPU/Clusters.
 */
typedef enum
{
  HAL_CLK_APCS_CPU_CLUSTER0,
  HAL_CLK_APCS_CPU_CLUSTER1,
  HAL_CLK_APCS_CPU_CCI,
  HAL_CLK_APCS_CPU_TOTAL,

  HAL_ENUM_32BITS(CLK_APCS_CPU)
} HAL_clk_APCSCPUType;


/*
 * APCS power modes.
 */
typedef enum
{
  HAL_CLK_POWER_GATE_MODE_UNKNOWN,
  HAL_CLK_POWER_GATE_MODE_COLLAPSE,
  HAL_CLK_POWER_GATE_MODE_LDO,
  HAL_CLK_POWER_GATE_MODE_BHS,
  HAL_CLK_POWER_GATE_MODE_DUTYCYCLE,
  HAL_CLK_POWER_GATE_MODE_RETENTION,

  HAL_ENUM_32BITS(CLK_POWER_GATE_MODE)
} HAL_clk_APCSPowerMode;


/* ============================================================================
**    Functions
** ==========================================================================*/

/* =========================================================================
**  Function : HAL_clk_APCSConfigMuxSource
** =========================================================================*/
/**
  Configure the LS and HS APCS mux selections.

  The APCS clock mux has two configurations which are used based on
  the current power mode: LDO, BHS, or duty-cycling. This function
  allows each configuration (LS and HS) to be programmed individually.
  If pmConfigLS or pmConfigHS are NULL, then nothing is programmed for that
  configuration.

  @param *eCore [in] -- CPU to configure.
  @param *pmConfigLS [in] -- Low-speed (LDO) configuration.
  @param *pmConfigHS [in] -- High-speed (BHS) configuration.
*/

void HAL_clk_APCSConfigMuxSource
(
  HAL_clk_APCSCPUType                eCore,
  const HAL_clk_ClockMuxConfigType  *pmConfigLS,
  const HAL_clk_ClockMuxConfigType  *pmConfigHS
);


/* =========================================================================
**  Function : HAL_clk_APCSSetPowerMode
** =========================================================================*/
/**
  Set the CPU power mode.

  @param *eCore [in] -- CPU to configure.
  @param *eMode [in] -- Power mode.
*/

boolean HAL_clk_APCSSetPowerMode
(
  HAL_clk_APCSCPUType   eCore,
  HAL_clk_APCSPowerMode eMode
);


/* =========================================================================
**  Function : HAL_clk_APCSDetectPowerMode
** =========================================================================*/
/**
  Detect the CPU power mode.

  @param *eCore [in] -- CPU to detect.

  @return
    The power mode being used.
*/

HAL_clk_APCSPowerMode HAL_clk_APCSDetectPowerMode
(
  HAL_clk_APCSCPUType eCore
);


/* =========================================================================
**  Function : HAL_clk_APCSSetLDOVoltage
** =========================================================================*/
/**
  Set the CPU LDO voltage.

  @param *eCore [in] -- CPU to configure.
  @param *nMillivolts [in] -- LDO voltage.
*/

void HAL_clk_APCSSetLDOVoltage
(
  HAL_clk_APCSCPUType eCore,
  uint32              nMillivolts
);

/* =========================================================================
**  Function : HAL_clk_APCSSetLDORetVoltage
** =========================================================================*/
/**
  Set the CPU LDO voltage.

  @param *eCore [in] -- CPU to configure.
  @param *nMillivolts [in] -- LDO Ret voltage.
*/

void HAL_clk_APCSSetLDORetVoltage
(
  HAL_clk_APCSCPUType eCore,
  uint32              nMillivolts
);

/* =========================================================================
**  Function : HAL_clk_APCSEnableMDD
** =========================================================================*/
/**
  Enable the CPU LDO voltage reference (MDD).

  @param *eCore [in] -- CPU to configure.
  @param bEnable[in] -- Enable/disable the MDD.
*/

void HAL_clk_APCSEnableMDD
(
  HAL_clk_APCSCPUType eCore,
  boolean bEnable
);

/* =========================================================================
**  Function : HAL_clk_APCSSetCycleCounts
** =========================================================================*/
/**
  Set the cycle counts for the hardware duty-cycler.

  @param *eCore [in] -- CPU to configure.
  @param *nLDOCount [in] -- Time to stay on the LDO.
  @param *nBHSCount [in] -- Time to stay on the BHS.
*/

void HAL_clk_APCSSetCycleCounts
(
  HAL_clk_APCSCPUType eCore,
  uint32              nLDOCount,
  uint32              nBHSCount
);

/* =========================================================================
**  Function : HAL_clk_KPSSAXISleepEnable
** =========================================================================*/
/**
  Change the state of the KPSS AXI clock sleep vote.

  @param *bEnable [in] -- New state of the vote.
*/

void HAL_clk_KPSSAXISleepEnable
(
  boolean bEnable
);

/* ===========================================================================
**  Function : HAL_clk_ApplyMemAccValue
**
** ======================================================================== */
/**
  Apply the new MEM ACC settings based on the new voltage corner.

  @param *eCore         [in] -- CPU cluster to configure.
  @param eVRegLevelPrev [in] -- Old voltage corner.
  @param eVRegLevelNext [in] -- New voltage corner.
*/

void HAL_clk_ApplyMemAccValue
(
  HAL_clk_APCSCPUType   eCore,
  HAL_clk_VRegLevelType eVRegLevelPrev,
  HAL_clk_VRegLevelType eVRegLevelNext
);


#endif

