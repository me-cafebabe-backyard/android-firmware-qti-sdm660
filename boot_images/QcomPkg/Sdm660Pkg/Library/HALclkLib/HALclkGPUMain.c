/*
==============================================================================

FILE:         HALclkGPUMain.c

DESCRIPTION:
   The main auto-generated file for GPU.


==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkGPUMain.c#2 $

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



/*
 * Clock domains
 */
extern HAL_clk_ClockDomainDescType HAL_clk_mGPUGFX3DClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGPURBBMTIMERClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGPURBCPRClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGPUSTANDALONEBCRClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGPUXOClkDomain;

/*
 * Power domains
 */
extern HAL_clk_PowerDomainDescType HAL_clk_mGPUGPUCXPowerDomain;
extern HAL_clk_PowerDomainDescType HAL_clk_mGPUGPUGXPowerDomain;


/* ============================================================================
**    Data
** ==========================================================================*/


/*
 * aGPUSourceMap
 *
 * GPU HW source mapping
 * 
 */
static HAL_clk_SourceMapType aGPUSourceMap[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_GPUPLL0,            1 },
  { HAL_CLK_SOURCE_GROUND,             2 },
  { HAL_CLK_SOURCE_GPUPLL1,            3 },
  { HAL_CLK_SOURCE_GROUND,             4 },
  { HAL_CLK_SOURCE_GPLL0,              5 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mGPUClockDomainControl
 *
 * Functions for controlling GPU clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGPUClockDomainControl =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aGPUSourceMap
};


/*
 * HAL_clk_mGPUClockDomainControlRO
 *
 * Read-only functions for GPU clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGPUClockDomainControlRO =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aGPUSourceMap
};


/*
 * HAL_clk_aGPUClockDomainDesc
 *
 * List of GPU clock domains
*/
static HAL_clk_ClockDomainDescType * HAL_clk_aGPUClockDomainDesc [] =
{
  &HAL_clk_mGPUGFX3DClkDomain,
  &HAL_clk_mGPURBBMTIMERClkDomain,
  &HAL_clk_mGPURBCPRClkDomain,
  &HAL_clk_mGPUSTANDALONEBCRClkDomain,
  &HAL_clk_mGPUXOClkDomain,
  NULL
};


/*
 * HAL_clk_aGPUPowerDomainDesc
 *
 * List of GPU power domains
 */
static HAL_clk_PowerDomainDescType * HAL_clk_aGPUPowerDomainDesc [] =
{
  &HAL_clk_mGPUGPUCXPowerDomain,
  &HAL_clk_mGPUGPUGXPowerDomain,
  NULL
};



/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/


/* ===========================================================================
**  HAL_clk_PlatformInitGPUMain
**
** ======================================================================== */

void HAL_clk_PlatformInitGPUMain (void)
{

  /*
   * Install all clock domains
   */
  HAL_clk_InstallClockDomains(HAL_clk_aGPUClockDomainDesc, A5X_BASE);

  /*
   * Install all power domains
   */
  HAL_clk_InstallPowerDomains(HAL_clk_aGPUPowerDomainDesc, A5X_BASE);

} /* END HAL_clk_PlatformInitGPUMain */

