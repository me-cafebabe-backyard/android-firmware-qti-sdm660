/*
==============================================================================

FILE:         HALclkQ6SMMU.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   Q6SMMU clocks.

   List of clock domains:


   List of power domains:
     - HAL_clk_mLPASSQ6SMMUPowerDomain



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/adsp/src/lpass/HALclkQ6SMMU.c#1 $

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

extern void HAL_clk_Q6SMMUCorePowerDomainEnable(HAL_clk_PowerDomainDescType *pmPowerDomainDesc);
extern void HAL_clk_Q6SMMUCorePowerDomainDisable(HAL_clk_PowerDomainDescType *pmPowerDomainDesc);
extern boolean HAL_clk_GenericPowerDomainIsEnabled(HAL_clk_PowerDomainDescType *pmPowerDomainDesc);
extern boolean HAL_clk_GenericPowerDomainIsOn(HAL_clk_PowerDomainDescType *pmPowerDomainDesc);


/* ============================================================================
**    Data
** ==========================================================================*/

/*
 * HAL_clk_mGenericPowerDomainControl
 *
 * Functions for controlling common power domain functions.
 */
HAL_clk_PowerDomainControlType HAL_clk_mQ6SMMUPowerDomainControl =
{
   /* .Enable     = */ HAL_clk_Q6SMMUCorePowerDomainEnable,
   /* .Disable    = */ HAL_clk_Q6SMMUCorePowerDomainDisable,
   /* .IsEnabled  = */ HAL_clk_GenericPowerDomainIsEnabled,
   /* .IsOn       = */ HAL_clk_GenericPowerDomainIsOn
};




/* ============================================================================
**    Data
** ==========================================================================*/


/*
 * HAL_clk_mLPASSQ6SMMUPowerDomain
 *
 * Q6_SMMU power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mLPASSQ6SMMUPowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_Q6_SMMU",
  /* .nGDSCRAddr              = */ HWIO_OFFS(LPASS_Q6_SMMU_GDSCR),
  /* .pmControl               = */ &HAL_clk_mQ6SMMUPowerDomainControl,
  /* .pmNextPowerDomain       = */ NULL
};

