/*
==============================================================================

FILE:         HALclkMMSS.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   MMSS clocks.

   List of clock domains:
     - HAL_clk_mGCCMMSSQMCOREClkDomain


   List of power domains:
     - HAL_clk_mGCCMMSSPowerDomain



==============================================================================

$Header: //components/rel/rpm.bf/1.8/core/systemdrivers/hal/clk/hw/sdm660/src/GCC/HALclkMMSS.c#2 $

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

extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControl;
extern HAL_clk_ClockDomainControlType  HAL_clk_mGCCClockDomainControlRO;


/* ============================================================================
**    Data
** ==========================================================================*/



/*
 * HAL_clk_mGCCMMSSPowerDomain
 *
 * MMSS power domain.
 */
 #if 0
HAL_clk_PowerDomainDescType HAL_clk_mGCCMMSSPowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_MMSS",
  /* .nGDSCRAddr              = */ HWIO_OFFS(GCC_MMSS_GDSCR),
  /* .pmControl               = */ &HAL_clk_mGenericPowerDomainControl,
  /* .pmNextPowerDomain       = */ NULL
};
#endif
