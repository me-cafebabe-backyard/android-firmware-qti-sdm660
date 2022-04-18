/*
==============================================================================

FILE:         HALclkSCCQ6SPM.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SCCQ6SPM clocks.

   List of clock domains:
     - HAL_clk_mLPASSQ6SPMClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/adsp_slpi/src/lpass/HALclkSCCQ6SPM.c#1 $

==============================================================================
            Copyright (c) 2016 Qualcomm Technologies Incorporated.
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

extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControl_1;
extern HAL_clk_ClockDomainControlType  HAL_clk_mLPASSClockDomainControlRO_1;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mQ6SPMClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mQ6SPMClkDomainClks[] =
{
  {
    /* .szClockName      = */ "island_scc_q6_spm_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_ISLAND_SCC_Q6_SPM_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_ISLAND_SCC_Q6_SPM_CLK
  },
  {
    /* .szClockName      = */ "island_scc_sensor_core_bcr_xo_clk",
    /* .mRegisters       = */ { HWIO_OFFS(LPASS_ISLAND_SCC_SENSOR_CORE_BCR_XO_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_LPASS_TEST_ISLAND_SCC_SENSOR_CORE_BCR_XO_CLK
  },
};


/*
 * HAL_clk_mLPASSQ6SPMClkDomain
 *
 * Q6SPM clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mLPASSQ6SPMClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(LPASS_Q6_SPM_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mQ6SPMClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mQ6SPMClkDomainClks)/sizeof(HAL_clk_mQ6SPMClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mLPASSClockDomainControl_1,
  /* .pmNextClockDomain    = */ NULL
};

