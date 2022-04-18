/*
==============================================================================

FILE:         HALclkVIDEOSUBCORE0.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   VIDEOSUBCORE0 clocks.

   List of clock domains:


   List of power domains:
     - HAL_clk_mMMSSVIDEOSUBCORE0PowerDomain



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkVIDEOSUBCORE0.c#2 $

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
 * HAL_clk_mMMSSVIDEOSUBCORE0PowerDomain
 *
 * VIDEO_SUBCORE0 power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mMMSSVIDEOSUBCORE0PowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_VIDEO_SUBCORE0",
  /* .nGDSCRAddr              = */ HWIO_OFFS(MMSS_VIDEO_SUBCORE0_GDSCR),
  /* .pmControl               = */ &HAL_clk_mGenericPowerDomainControl,
  /* .pmClockMemCore          = */ NULL,
  /* .pmClockMemPeriph        = */ NULL,
  /* .pmNextPowerDomain       = */ NULL
};

