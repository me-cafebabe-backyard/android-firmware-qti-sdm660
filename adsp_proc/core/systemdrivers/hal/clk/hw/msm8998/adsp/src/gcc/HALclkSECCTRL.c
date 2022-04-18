/*
==============================================================================

FILE:         HALclkSECCTRL.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   SECCTRL clocks.

   List of clock domains:
     - HAL_clk_mGCCSECCTRLClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/adsp/src/gcc/HALclkSECCTRL.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mSECCTRLClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mSECCTRLClkDomainClks[] =
{
#if 0 /* not present on ssc */

  {
    /* .szClockName      = */ "gcc_sec_ctrl_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SEC_CTRL_CBCR), HWIO_OFFS(GCC_SEC_CTRL_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SEC_CTRL_CLK
  },
#endif

#if 0 /* not present on ssc */

  {
    /* .szClockName      = */ "gcc_sec_ctrl_sense_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SEC_CTRL_SENSE_CBCR), HWIO_OFFS(GCC_SEC_CTRL_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SEC_CTRL_SENSE_CLK
  },
#endif

  {
    /* .szClockName      = */ "gcc_spss_sec_ctrl_clk",
    /* .mRegisters       = */ { HWIO_OFFS(GCC_SPSS_SEC_CTRL_CBCR), HWIO_OFFS(GCC_SPSS_BCR), {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_GCC_TEST_GCC_SPSS_SEC_CTRL_CLK
  },
};


/*
 * HAL_clk_mGCCSECCTRLClkDomain
 *
 * SECCTRL clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mGCCSECCTRLClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(GCC_SEC_CTRL_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mSECCTRLClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mSECCTRLClkDomainClks)/sizeof(HAL_clk_mSECCTRLClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mGCCClockDomainControlRO,
  /* .pmNextClockDomain    = */ NULL
};

