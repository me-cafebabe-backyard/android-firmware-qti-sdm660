/*
==============================================================================

FILE:         HALclkMMSSMain.c

DESCRIPTION:
   The main auto-generated file for MMSS.


==============================================================================

$Header: //components/rel/rpm.bf/1.8/core/systemdrivers/hal/clk/hw/sdm660/src/MMSS/HALclkMMSSMain.c#2 $

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
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSAXIClkDomain;

/* ============================================================================
**    Data
** ==========================================================================*/


/*
 * aMMSSSourceMap_1
 *
 * MMSS HW source mapping
 * 
 */
static HAL_clk_SourceMapType aMMSSSourceMap_1[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_MMPLL0,             1 },
  { HAL_CLK_SOURCE_MMPLL1,             2 },
  { HAL_CLK_SOURCE_MMPLL6,             3 },
  { HAL_CLK_SOURCE_GPLL0,              5 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         6 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }

};


/*
 * HAL_clk_mMMSSClockDomainControl_1
 *
 * Functions for controlling MMSS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mMMSSClockDomainControl_1 =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aMMSSSourceMap_1
};


/*
 * HAL_clk_mMMSSClockDomainControlRO_1
 *
 * Read-only functions for MMSS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mMMSSClockDomainControlRO_1 =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aMMSSSourceMap_1
};

/*
 * HAL_clk_aMMSSClockDomainDesc
 *
 * List of MMSS clock domains
*/
static HAL_clk_ClockDomainDescType * HAL_clk_aMMSSClockDomainDesc [] =
{
  &HAL_clk_mMMSSAXIClkDomain,
  NULL
};

/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/


/* ===========================================================================
**  HAL_clk_PlatformInitMMSSMain
**
** ======================================================================== */

void HAL_clk_PlatformInitMMSSMain (void)
{

  /*
   * Install all clock domains
   */
  HAL_clk_InstallClockDomains(HAL_clk_aMMSSClockDomainDesc, MMSS_BASE);

} /* END HAL_clk_PlatformInitMMSSMain */


/* ===========================================================================
**  HAL_clk_HMSSPowerDomainRestore
** ======================================================================== */
#if 0
void HAL_clk_MMSSPowerDomainRestore
(
  boolean   bRestore
)
{

  HWIO_OUTF(GCC_MMSS_GDSCR, SW_COLLAPSE, !bRestore);

} /* END HAL_clk_HMSSPowerDomainRestore*/
#endif
/* ===========================================================================
**  HAL_clk_ConfigMMSSMISC
** ======================================================================== */

void HAL_clk_ConfigMMSSMISC( boolean bEnable )
{

  HWIO_OUTF(GCC_MMSS_MISC, GPLL0_DIV_SRC_DISABLE, !bEnable);
  HWIO_OUTF(GCC_MMSS_MISC, GPLL0_SRC_DISABLE, !bEnable);

}




