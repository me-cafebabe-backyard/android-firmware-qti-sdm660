/*
==============================================================================

FILE:         HALclkQ6SMMU.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   Q6SMMU clocks.

   List of clock domains:


   List of power domains:
     - HAL_clk_mTURINGQ6SMMUPowerDomain



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/cdsp/src/turing/HALclkQ6SMMU.c#1 $

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



/* ============================================================================
**    Data
** ==========================================================================*/


/*
 * HAL_clk_mTURINGQ6SMMUPowerDomain
 *
 * Q6_SMMU power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mTURINGQ6SMMUPowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_Q6_SMMU",
  /* .nGDSCRAddr              = */ HWIO_OFFS(TURING_Q6_SMMU_GDSCR),
  /* .pmControl               = */ &HAL_clk_mGenericPowerDomainControl,
  /* .pmNextPowerDomain       = */ NULL
};

