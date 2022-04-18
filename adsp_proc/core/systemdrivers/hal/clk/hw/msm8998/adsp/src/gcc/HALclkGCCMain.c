/*
==============================================================================

FILE:         HALclkGCCMain.c

DESCRIPTION:
   The main auto-generated file for GCC.


==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/hal/clk/hw/msm8998/adsp/src/gcc/HALclkGCCMain.c#1 $

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
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP1I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP1SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP2I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP2SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP3I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP3SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP4I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP4SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP5I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP5SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP6I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1QUP6SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1UART1APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1UART2APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP1UART3APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP1I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP1SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP2I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP2SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP3I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP3SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP4I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP4SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP5I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP5SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP6I2CAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2QUP6SPIAPPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2UART1APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2UART2APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCBLSP2UART3APPSClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCCE1ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCCNOCPERIPHClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCCONFIGNOCClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCGCCSLEEPClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mGCCSYSTEMNOCClkDomain;

/*
 * Power domains
 */
#if 0 /* not present on lpass */
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
  {HAL_CLK_SOURCE_GPLL0,               1 },
  { HAL_CLK_SOURCE_GPLL5,              2 },
  { HAL_CLK_SOURCE_GPLL1_DIV2,         3 },
  { HAL_CLK_SOURCE_GPLL1,              4 },
  { HAL_CLK_SOURCE_GPLL4,              5 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         6 },
  {HAL_CLK_SOURCE_PLLTEST,     7},
  {HAL_CLK_SOURCE_NULL,        HAL_CLK_SOURCE_INDEX_INVALID}
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
  { HAL_CLK_SOURCE_GPLL2,              2 },
  { HAL_CLK_SOURCE_GPLL3,              3 },
  { HAL_CLK_SOURCE_GPLL1,              4 },
  { HAL_CLK_SOURCE_SLEEPCLK,           5 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         6 },
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
  { HAL_CLK_SOURCE_GPLL2_EVEN,         5 },
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
  { HAL_CLK_SOURCE_GPLL2,              2 },
  { HAL_CLK_SOURCE_GPLL3,              3 },
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
  &HAL_clk_mGCCBLSP1QUP1I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP1SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP2I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP2SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP3I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP3SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP4I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP4SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP5I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP5SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP6I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP1QUP6SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP1UART1APPSClkDomain,
  &HAL_clk_mGCCBLSP1UART2APPSClkDomain,
  &HAL_clk_mGCCBLSP1UART3APPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP1I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP1SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP2I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP2SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP3I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP3SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP4I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP4SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP5I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP5SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP6I2CAPPSClkDomain,
  &HAL_clk_mGCCBLSP2QUP6SPIAPPSClkDomain,
  &HAL_clk_mGCCBLSP2UART1APPSClkDomain,
  &HAL_clk_mGCCBLSP2UART2APPSClkDomain,
  &HAL_clk_mGCCBLSP2UART3APPSClkDomain,
  &HAL_clk_mGCCCE1ClkDomain,
  &HAL_clk_mGCCCNOCPERIPHClkDomain,
  &HAL_clk_mGCCCONFIGNOCClkDomain,
  &HAL_clk_mGCCGCCSLEEPClkDomain,
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
#if 0 /* not present on lpass */
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

