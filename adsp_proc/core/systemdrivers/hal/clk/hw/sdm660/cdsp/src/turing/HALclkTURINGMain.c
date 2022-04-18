/*
==============================================================================

FILE:         HALclkTURINGMain.c

DESCRIPTION:
   The main auto-generated file for TURING.


==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/cdsp/src/turing/HALclkTURINGMain.c#1 $

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
extern HAL_clk_ClockDomainDescType HAL_clk_mTURINGAONClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mTURINGCCTURINGAXIMCLKClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mTURINGCCTURINGQ6SMMUCFGCNOCCLKClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mTURINGCCTURINGSNOCSWAYCLKClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mTURINGICAMSSDSPSTREAMING0CLKClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mTURINGICAMSSDSPSTREAMING1CLKClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mTURINGQOSFIXEDLATCOUNTERSRCClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mTURINGSLEEPClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mTURINGQ6SSRCGIMAGEClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mTURINGXOClkDomain;

/*
 * Power domains
 */
extern HAL_clk_PowerDomainDescType HAL_clk_mTURINGAUDIOCOREPowerDomain;
extern HAL_clk_PowerDomainDescType HAL_clk_mTURINGQ6SMMUPowerDomain;


/* ============================================================================
**    Data
** ==========================================================================*/


/*
 * aTURINGSourceMap
 *
 * TURING HW source mapping
 * 
 */
static HAL_clk_SourceMapType aTURINGSourceMap[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_SLEEPCLK,           1 },
  { HAL_CLK_SOURCE_GROUND,             2 },
  { HAL_CLK_SOURCE_GROUND,             3 },
  { HAL_CLK_SOURCE_GROUND,             4 },
  { HAL_CLK_SOURCE_TURINGPLL0,        5 },
  { HAL_CLK_SOURCE_GROUND,             6 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mTURINGClockDomainControl
 *
 * Functions for controlling TURING clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mTURINGClockDomainControl =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aTURINGSourceMap
};


/*
 * HAL_clk_mTURINGClockDomainControlRO
 *
 * Read-only functions for TURING clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mTURINGClockDomainControlRO =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aTURINGSourceMap
};





/*
 * HAL_clk_aTURINGClockDomainDesc
 *
 * List of TURING clock domains
*/
static HAL_clk_ClockDomainDescType * HAL_clk_aTURINGClockDomainDesc [] =
{
  &HAL_clk_mTURINGAONClkDomain,
  &HAL_clk_mTURINGCCTURINGAXIMCLKClkDomain,
  &HAL_clk_mTURINGCCTURINGQ6SMMUCFGCNOCCLKClkDomain,
  &HAL_clk_mTURINGCCTURINGSNOCSWAYCLKClkDomain,
  &HAL_clk_mTURINGICAMSSDSPSTREAMING0CLKClkDomain,
  &HAL_clk_mTURINGICAMSSDSPSTREAMING1CLKClkDomain,
  &HAL_clk_mTURINGQOSFIXEDLATCOUNTERSRCClkDomain,
  &HAL_clk_mTURINGSLEEPClkDomain,
  &HAL_clk_mTURINGQ6SSRCGIMAGEClkDomain,
  &HAL_clk_mTURINGXOClkDomain,
  NULL
};


/*
 * HAL_clk_aTURINGPowerDomainDesc
 *
 * List of TURING power domains
 */
static HAL_clk_PowerDomainDescType * HAL_clk_aTURINGPowerDomainDesc [] =
{
  &HAL_clk_mTURINGQ6SMMUPowerDomain,
  NULL
};



/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/


/* ===========================================================================
**  HAL_clk_PlatformInitTURINGMain
**
** ======================================================================== */

void HAL_clk_PlatformInitTURINGMain (void)
{

  /*
   * Install all clock domains
   */
  HAL_clk_InstallClockDomains(HAL_clk_aTURINGClockDomainDesc, TURING_BASE);

  /*
   * Install all power domains
   */
  HAL_clk_InstallPowerDomains(HAL_clk_aTURINGPowerDomainDesc, TURING_BASE);

} /* END HAL_clk_PlatformInitTURINGMain */

