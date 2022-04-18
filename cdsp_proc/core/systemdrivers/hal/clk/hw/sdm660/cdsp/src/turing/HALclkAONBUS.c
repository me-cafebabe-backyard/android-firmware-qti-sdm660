/*
==============================================================================

FILE:         HALclkAONBUS.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   AONBUS clocks.

   List of clock domains:
     - HAL_clk_mTURINGAONClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/cdsp/src/turing/HALclkAONBUS.c#1 $

==============================================================================
            Copyright (c) 2016 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/


#include <HALhwio.h>

#include "HALclkInternal.h"
#include "HALclkTest.h"
#include "HALclkGeneric.h"
#include "HALclkHWIO.h"


/*============================================================================

             DEFINITIONS AND DECLARATIONS FOR MODULE

=============================================================================*/

/*
 * aTURINGSourceMap_2
 *
 * TURING HW source mapping
 * 
 */
static HAL_clk_SourceMapType aTURINGAONSourceMap[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_TURINGPLL0,         1 },
  { HAL_CLK_SOURCE_TURINGPLL0_DIV2,    2 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mTURINGAONClockDomainControl
 *
 * Functions for controlling TURING clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mTURINGAONClockDomainControl =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
    /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aTURINGAONSourceMap
};



/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mAONClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mAONClkDomainClks[] =
{
  {
    /* .szClockName      = */ "q6ss_ahbm_aon_clk",
    /* .mRegisters       = */ { HWIO_OFFS(TURING_Q6SS_AHBM_AON_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_TURING_TEST_Q6SS_AHBM_AON_CLK
  },
  {
    /* .szClockName      = */ "q6ss_ahbs_aon_clk",
    /* .mRegisters       = */ { HWIO_OFFS(TURING_Q6SS_AHBS_AON_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_TURING_TEST_Q6SS_AHBS_AON_CLK
  },
  {
    /* .szClockName      = */ "turing_wrapper_aon_clk",
    /* .mRegisters       = */ { HWIO_OFFS(TURING_TURING_WRAPPER_AON_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_TURING_TEST_TURING_WRAPPER_AON_CLK
  },
  {
    /* .szClockName      = */ "turing_wrapper_bus_timeout_aon_clk",
    /* .mRegisters       = */ { HWIO_OFFS(TURING_TURING_WRAPPER_BUS_TIMEOUT_AON_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_TURING_TEST_TURING_WRAPPER_BUS_TIMEOUT_AON_CLK
  },
  {
    /* .szClockName      = */ "turing_wrapper_mpu_cfg_aon_clk",
    /* .mRegisters       = */ { HWIO_OFFS(TURING_TURING_WRAPPER_MPU_CFG_AON_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_TURING_TEST_TURING_WRAPPER_MPU_CFG_AON_CLK
  },
  {
    /* .szClockName      = */ "turing_wrapper_q6_ahbm_mpu_aon_clk",
    /* .mRegisters       = */ { HWIO_OFFS(TURING_TURING_WRAPPER_Q6_AHBM_MPU_AON_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_TURING_TEST_TURING_WRAPPER_Q6_AHBM_MPU_AON_CLK
  },
  {
    /* .szClockName      = */ "turing_wrapper_qos_ahbs_aon_clk",
    /* .mRegisters       = */ { HWIO_OFFS(TURING_TURING_WRAPPER_QOS_AHBS_AON_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_TURING_TEST_TURING_WRAPPER_QOS_AHBS_AON_CLK
  },
  {
    /* .szClockName      = */ "turing_wrapper_sysnoc_sway_aon_clk",
    /* .mRegisters       = */ { HWIO_OFFS(TURING_TURING_WRAPPER_SYSNOC_SWAY_AON_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_TURING_TEST_TURING_WRAPPER_SYSNOC_SWAY_AON_CLK
  },
};


/*
 * HAL_clk_mTURINGAONClkDomain
 *
 * AON clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mTURINGAONClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(TURING_AON_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mAONClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mAONClkDomainClks)/sizeof(HAL_clk_mAONClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mTURINGAONClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

