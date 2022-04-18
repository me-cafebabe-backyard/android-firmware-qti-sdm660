/*
==============================================================================

FILE:         HALclkCOREBUS.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   COREBUS clocks.

   List of clock domains:
     - HAL_clk_mLPASSCOREClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/slpi/src/lpass/HALclkCOREBUS.c#1 $

==============================================================================
            Copyright (c) 2015 QUALCOMM Technologies Incorporated.
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


/* ============================================================================
**    Prototypes
** ==========================================================================*/


/* ============================================================================
**    Externs
** ==========================================================================*/

extern HAL_clk_ClockControlType        HAL_clk_mLpassClockControl_1;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl_1;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControlRO_1;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mCOREClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCOREClkDomainClks[] =
{
  {
    /* .szClockName      = */ "lpass_audio_core_aud_slimbus_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mLpassClockControl_1,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_AUD_SLIMBUS_CORE_CLK
  },
  {
    /* .szClockName      = */ "lpass_audio_core_bus_timeout_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mLpassClockControl_1,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_BUS_TIMEOUT_CORE_CLK
  },
  {
    /* .szClockName      = */ "lpass_audio_core_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mLpassClockControl_1,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_CORE_CLK
  },
  {
    /* .szClockName      = */ "lpass_audio_core_lpm_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPM_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mLpassClockControl_1,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_LPM_CORE_CLK
  },
  {
    /* .szClockName      = */ "lpass_audio_core_lpm_mem0_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPM_MEM0_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mLpassClockControl_1,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_LPM_MEM0_CORE_CLK
  },
  {
    /* .szClockName      = */ "lpass_audio_core_lpm_mem1_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPM_MEM1_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mLpassClockControl_1,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_LPM_MEM1_CORE_CLK
  },
  {
    /* .szClockName      = */ "lpass_audio_core_lpm_mem2_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPM_MEM2_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mLpassClockControl_1,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_LPM_MEM2_CORE_CLK
  },
  {
    /* .szClockName      = */ "lpass_audio_core_lpm_mem3_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_LPM_MEM3_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mLpassClockControl_1,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_LPM_MEM3_CORE_CLK
  },
  {
    /* .szClockName      = */ "lpass_audio_core_qca_slimbus_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mLpassClockControl_1,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_QCA_SLIMBUS_CORE_CLK
  },
  {
    /* .szClockName      = */ "lpass_audio_core_sysnoc_mport_core_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_LPASS_AUDIO_CORE_SYSNOC_MPORT_CORE_CLK
  },
};


/*
 * HAL_clk_mLPASSCOREClkDomain
 *
 * CORE clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSCOREClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_CORE_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mCOREClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCOREClkDomainClks)/sizeof(HAL_clk_mCOREClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl_1,
  /* .pmNextClockDomain    = */ NULL
};


