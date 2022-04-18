/*
==============================================================================

FILE:         HALclkBIMCSMMU.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   BIMCSMMU clocks.

   List of clock domains:


   List of power domains:
     - HAL_clk_mMMSSBIMCSMMUPowerDomain



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkBIMCSMMU.c#1 $

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
 * HAL_clk_mMMSSBIMCSMMUPowerDomain
 *
 * BIMC_SMMU power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mMMSSBIMCSMMUPowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_BIMC_SMMU",
  /* .nGDSCRAddr              = */ HWIO_OFFS(MMSS_BIMC_SMMU_GDSCR),
  /* .pmControl               = */ &HAL_clk_mGenericPowerDomainControl,
  /* .pmClockMemCore          = */ NULL,
  /* .pmClockMemPeriph        = */ NULL,
  /* .pmNextPowerDomain       = */ NULL
};

