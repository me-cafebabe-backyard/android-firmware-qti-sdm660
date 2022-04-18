/*
==============================================================================

FILE:         HALclkCNOC.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CNOC clocks.

   List of clock domains:
     - HAL_clk_mTURINGCCTURINGQ6SMMUCFGCNOCCLKClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/cdsp/src/turing/HALclkCNOC.c#1 $

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


/* ============================================================================
**    Prototypes
** ==========================================================================*/


/* ============================================================================
**    Externs
** ==========================================================================*/

extern HAL_clk_ClockDomainControlType  HAL_clk_mTURINGClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mTURINGClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mCCTURINGQ6SMMUCFGCNOCCLKClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCCTURINGQ6SMMUCFGCNOCCLKClkDomainClks[] =
{
  {
    /* .szClockName      = */ "turing_wrapper_q6_smmu_cfg_cnoc_clk",
    /* .mRegisters       = */ { HWIO_OFFS(TURING_TURING_WRAPPER_Q6_SMMU_CFG_CNOC_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ 0
  },
};


/*
 * HAL_clk_mTURINGCCTURINGQ6SMMUCFGCNOCCLKClkDomain
 *
 * CCTURINGQ6SMMUCFGCNOCCLK clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mTURINGCCTURINGQ6SMMUCFGCNOCCLKClkDomain =
{
  /* .nCGRAddr             = */ 0, /* this domain does not have a cmd rcgr */
  /* .pmClocks             = */ HAL_clk_mCCTURINGQ6SMMUCFGCNOCCLKClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCCTURINGQ6SMMUCFGCNOCCLKClkDomainClks)/sizeof(HAL_clk_mCCTURINGQ6SMMUCFGCNOCCLKClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mTURINGClockDomainControl,
  /* .pmNextClockDomain    = */ NULL
};

