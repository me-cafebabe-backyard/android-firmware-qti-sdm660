/*
==============================================================================

FILE:         HALclkCAMSSTOP.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   CAMSSTOP clocks.

   List of clock domains:


   List of power domains:
     - HAL_clk_mMMSSCAMSSTOPPowerDomain



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkCAMSSTOP.c#1 $

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
 * HAL_clk_mMMSSCAMSSTOPPowerDomain
 *
 * CAMSS_TOP power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mMMSSCAMSSTOPPowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_CAMSS_TOP",
  /* .nGDSCRAddr              = */ HWIO_OFFS(MMSS_CAMSS_TOP_GDSCR),
  /* .pmControl               = */ &HAL_clk_mGenericPowerDomainControl,
  /* .pmClockMemCore          = */ NULL,
  /* .pmClockMemPeriph        = */ NULL,
  /* .pmNextPowerDomain       = */ NULL
};

