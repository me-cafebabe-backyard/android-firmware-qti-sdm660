/*
==============================================================================

FILE:         HALclkGCCMain.c

DESCRIPTION:
   The main auto-generated file for GCC.


==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/sdm660/cdsp/src/gcc/HALclkGCCMain.c#1 $

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
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCCDSPBIMCClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCCNOCPERIPHClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCCONFIGNOCClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCGCCSLEEPClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCGCCXOClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSYSTEMNOCClkDomain;

/*
 * Power domains
 */
#if 0 /* not present on turing */
extern HAL_clk_PowerDomainDescType HAL_clk_mGCCBIMCPowerDomain;
#endif


/* ============================================================================
**    Data
** ==========================================================================*/


/*
 * aGCCSourceMap
 *
 * GCC HW source mapping
 * 
 */
static HAL_clk_SourceMapType aGCCSourceMap[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_GPLL0,              1 },
  { HAL_CLK_SOURCE_GPLL5,              2 },
  { HAL_CLK_SOURCE_GROUND,             3 },
  { HAL_CLK_SOURCE_GPLL1,              4 },
  { HAL_CLK_SOURCE_SLEEPCLK,           5 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mGCCClockDomainControl
 *
 * Functions for controlling GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControl =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aGCCSourceMap
};


/*
 * HAL_clk_mGCCClockDomainControlRO
 *
 * Read-only functions for GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControlRO =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aGCCSourceMap
};


/*
 * aGCCSourceMap_1
 *
 * GCC HW source mapping
 * 
 */
static HAL_clk_SourceMapType aGCCSourceMap_1[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_GPLL0,              1 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         2 },
  { HAL_CLK_SOURCE_GROUND,             3 },
  { HAL_CLK_SOURCE_GPLL1,              4 },
  { HAL_CLK_SOURCE_GPLL4,              5 },
  { HAL_CLK_SOURCE_GROUND,             6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mGCCClockDomainControl_1
 *
 * Functions for controlling GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControl_1 =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aGCCSourceMap_1
};


/*
 * HAL_clk_mGCCClockDomainControlRO_1
 *
 * Read-only functions for GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControlRO_1 =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aGCCSourceMap_1
};


/*
 * aGCCSourceMap_2
 *
 * GCC HW source mapping
 * 
 */
static HAL_clk_SourceMapType aGCCSourceMap_2[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_GPLL0,              1 },
  { HAL_CLK_SOURCE_GPLL2,              2 },
  { HAL_CLK_SOURCE_GPLL3,              3 },
  { HAL_CLK_SOURCE_GPLL1,              4 },
  { HAL_CLK_SOURCE_GPLL4,              5 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mGCCClockDomainControl_2
 *
 * Functions for controlling GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControl_2 =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aGCCSourceMap_2
};


/*
 * HAL_clk_mGCCClockDomainControlRO_2
 *
 * Read-only functions for GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControlRO_2 =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aGCCSourceMap_2
};


/*
 * aGCCSourceMap_3
 *
 * GCC HW source mapping
 * 
 */
static HAL_clk_SourceMapType aGCCSourceMap_3[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_GPLL0,              1 },
  { HAL_CLK_SOURCE_GROUND,             2 },
  { HAL_CLK_SOURCE_GPLL1_DIV2,         3 },
  { HAL_CLK_SOURCE_GPLL1,              4 },
  { HAL_CLK_SOURCE_GPLL4,              5 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mGCCClockDomainControl_3
 *
 * Functions for controlling GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControl_3 =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aGCCSourceMap_3
};


/*
 * HAL_clk_mGCCClockDomainControlRO_3
 *
 * Read-only functions for GCC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mGCCClockDomainControlRO_3 =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aGCCSourceMap_3
};


/*
 * HAL_clk_aGCCClockDomainDesc
 *
 * List of GCC clock domains
*/
static HAL_clk_ClockDomainDescType * HAL_clk_aGCCClockDomainDesc [] =
{
  &HAL_clk_mGCCCDSPBIMCClkDomain,
  &HAL_clk_mGCCCNOCPERIPHClkDomain,
  &HAL_clk_mGCCCONFIGNOCClkDomain,
  &HAL_clk_mGCCGCCSLEEPClkDomain,
  &HAL_clk_mGCCGCCXOClkDomain,
  &HAL_clk_mGCCSYSTEMNOCClkDomain,
  NULL
};


/*
 * HAL_clk_aGCCPowerDomainDesc
 *
 * List of GCC power domains
 */
static HAL_clk_PowerDomainDescType * HAL_clk_aGCCPowerDomainDesc [] =
{
#if 0 /* not present on turing */
  &HAL_clk_mGCCBIMCPowerDomain,
#endif
  NULL
};



/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/


/* ===========================================================================
**  HAL_clk_PlatformInitGCCMain
**
** ======================================================================== */

void HAL_clk_PlatformInitGCCMain (void)
{

  /*
   * Install all clock domains
   */
  HAL_clk_InstallClockDomains(HAL_clk_aGCCClockDomainDesc, CLK_CTL_BASE);

  /*
   * Install all power domains
   */
  HAL_clk_InstallPowerDomains(HAL_clk_aGCCPowerDomainDesc, CLK_CTL_BASE);

} /* END HAL_clk_PlatformInitGCCMain */

