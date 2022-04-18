/*
==============================================================================

FILE:         HALclkSSCMain.c

DESCRIPTION:
   The main auto-generated file for SSC.


==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/adsp/src/scc/HALclkSSCMain.c#1 $

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



/*
 * Clock domains
 */
extern HAL_clk_ClockDomainDescType HAL_clk_mQ6ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mSSCSCC100MClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mSSCSCCUARTDMUART1ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mSSCSCCUARTDMUART2ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mSSCSCCUARTDMUART3ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mSSCSCCVSVDDCXClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mSSCSCCVSVDDMXClkDomain;

/*
 * Power domains
 */


/* ============================================================================
**    Data
** ==========================================================================*/


/*
 * aSSCSourceMap
 *
 * SSC HW source mapping
 * 
 */
static HAL_clk_SourceMapType aSSCSourceMap[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_SLEEPCLK,           1 },
  { HAL_CLK_SOURCE_SCCPLL0_EVEN,       2 },
  { HAL_CLK_SOURCE_GROUND,             3 },
  { HAL_CLK_SOURCE_SCCPLL0_ODD,        4 },
  { HAL_CLK_SOURCE_SCCPLL1_ODD,        5 },
  { HAL_CLK_SOURCE_SCCPLL0,            6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mSSCClockDomainControl
 *
 * Functions for controlling SSC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mSSCClockDomainControl =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aSSCSourceMap
};


/*
 * HAL_clk_mSSCClockDomainControlRO
 *
 * Read-only functions for SSC clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mSSCClockDomainControlRO =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .IsOn               = */ HAL_clk_GenericDomainIsOn,
   /* .pmSourceMap        = */ aSSCSourceMap
};


/*
 * HAL_clk_aSSCClockDomainDesc
 *
 * List of SSC clock domains
*/
static HAL_clk_ClockDomainDescType * HAL_clk_aSSCClockDomainDesc [] =
{
  &HAL_clk_mQ6ClkDomain,
  &HAL_clk_mSSCSCC100MClkDomain,
  &HAL_clk_mSSCSCCUARTDMUART1ClkDomain,
  &HAL_clk_mSSCSCCUARTDMUART2ClkDomain,
  &HAL_clk_mSSCSCCUARTDMUART3ClkDomain,
  &HAL_clk_mSSCSCCVSVDDCXClkDomain,
  &HAL_clk_mSSCSCCVSVDDMXClkDomain,
  NULL
};


/*
 * HAL_clk_aSSCPowerDomainDesc
 *
 * List of SSC power domains
 */
static HAL_clk_PowerDomainDescType * HAL_clk_aSSCPowerDomainDesc [] =
{
  NULL
};



/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/


/* ===========================================================================
**  HAL_clk_PlatformInitSSCMain
**
** ======================================================================== */

void HAL_clk_PlatformInitSSCMain (void)
{

  /*
   * Install all clock domains
   */
  HAL_clk_InstallClockDomains(HAL_clk_aSSCClockDomainDesc, SSC_BASE);

  /*
   * Install all power domains
   */
  HAL_clk_InstallPowerDomains(HAL_clk_aSSCPowerDomainDesc, SSC_BASE);

} /* END HAL_clk_PlatformInitSSCMain */

