/*
==============================================================================

FILE:         HALclkCAMSSGP1.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CAMSSGP1 clocks.

   List of clock domains:
     - HAL_clk_mMMSSCAMSSGP1ClkDomain


   List of power domains:



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkCAMSSGP1.c#1 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControl_4;
extern HAL_clk_ClockDomainControlType  HAL_clk_mMMSSClockDomainControlRO_4;


/* ============================================================================
**    Data
** ==========================================================================*/


/*                           
 *  HAL_clk_mCAMSSGP1ClkDomainClks
 *                  
 *  List of clocks supported by this domain.
 */
static HAL_clk_ClockDescType HAL_clk_mCAMSSGP1ClkDomainClks[] =
{
  {
    /* .szClockName      = */ "mmss_camss_gp1_clk",
    /* .mRegisters       = */ { HWIO_OFFS(MMSS_CAMSS_GP1_CBCR), 0, {0, 0} },
    /* .pmControl        = */ &HAL_clk_mGenericClockControl,
    /* .nTestClock       = */ HAL_CLK_MMSS_TEST_MMSS_CAMSS_GP1_CLK
  },
};


/*
 * HAL_clk_mMMSSCAMSSGP1ClkDomain
 *
 * CAMSSGP1 clock domain.
 */
HAL_clk_ClockDomainDescType HAL_clk_mMMSSCAMSSGP1ClkDomain =
{
  /* .nCGRAddr             = */ HWIO_OFFS(MMSS_CAMSS_GP1_CMD_RCGR),
  /* .pmClocks             = */ HAL_clk_mCAMSSGP1ClkDomainClks,
  /* .nClockCount          = */ sizeof(HAL_clk_mCAMSSGP1ClkDomainClks)/sizeof(HAL_clk_mCAMSSGP1ClkDomainClks[0]),
  /* .pmControl            = */ &HAL_clk_mMMSSClockDomainControl_4,
  /* .pmNextClockDomain    = */ NULL
};

