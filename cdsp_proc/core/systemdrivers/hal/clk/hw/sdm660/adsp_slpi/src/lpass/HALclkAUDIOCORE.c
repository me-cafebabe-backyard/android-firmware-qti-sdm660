/*
==============================================================================

FILE:         HALclkAUDIOCORE.c

DESCRIPTION:
   This auto-generated file contains the clock HAL code for the 
   AUDIOCORE clocks.

   List of clock domains:


   List of power domains:
     - HAL_clk_mLPASSAUDIOCOREPowerDomain



==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/adsp_slpi/src/lpass/HALclkAUDIOCORE.c#1 $

==============================================================================
            Copyright (c) 2016 Qualcomm Technologies Incorporated.
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

extern void    HAL_clk_AudioCorePowerDomainEnable  (HAL_clk_PowerDomainDescType *pmPowerDomainDesc);
extern void    HAL_clk_GenericPowerDomainDisable   (HAL_clk_PowerDomainDescType *pmPowerDomainDesc);
extern boolean HAL_clk_GenericPowerDomainIsEnabled (HAL_clk_PowerDomainDescType *pmPowerDomainDesc);
extern boolean HAL_clk_GenericPowerDomainIsOn      (HAL_clk_PowerDomainDescType *pmPowerDomainDesc);


/* ============================================================================
**    Externs
** ==========================================================================*/



/* ============================================================================
**    Data
** ==========================================================================*/

/*
 * HAL_clk_mGenericPowerDomainControl
 *
 * Functions for controlling common power domain functions.
 */
HAL_clk_PowerDomainControlType HAL_clk_mAudioCorePowerDomainControl =
{
   /* .Enable     = */ HAL_clk_AudioCorePowerDomainEnable,
   /* .Disable    = */ HAL_clk_GenericPowerDomainDisable,
   /* .IsEnabled  = */ HAL_clk_GenericPowerDomainIsEnabled,
   /* .IsOn       = */ HAL_clk_GenericPowerDomainIsOn
};



/*
 * HAL_clk_mLPASSAUDIOCOREPowerDomain
 *
 * AUDIO_CORE power domain.
 */
HAL_clk_PowerDomainDescType HAL_clk_mLPASSAUDIOCOREPowerDomain =
{
  /* .szPowerDomainName       = */ "VDD_AUDIO_CORE",
  /* .nGDSCRAddr              = */ HWIO_OFFS(LPASS_AUDIO_CORE_GDSCR),
  /* .pmControl               = */ &HAL_clk_mAudioCorePowerDomainControl,
  /* .pmNextPowerDomain       = */ NULL
};

