/*
==============================================================================

FILE:         HALclkGPUCX.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   GPUCX clocks.

   List of clock domains:


   List of power domains:
     - HAL_clk_mGPUGPUCXPowerDomain



==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkGPUCX.c#1 $

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
 * HAL_clk_mGPUGPUCXPowerDomain
 *
 * GPU_CX power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mGPUGPUCXPowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_GPU_CX",
  /* .nGDSCRAddr              = */ HWIO_OFFS(GPUCC_GPU_CX_GDSCR),
  /* .pmControl               = */ &HAL_clk_mGenericPowerDomainControl,
  /* .pmClockMemCore          = */ NULL,
  /* .pmClockMemPeriph        = */ NULL,
  /* .pmNextPowerDomain       = */ NULL
};

