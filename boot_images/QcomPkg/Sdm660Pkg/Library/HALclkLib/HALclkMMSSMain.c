/*
==============================================================================

FILE:         HALclkMMSSMain.c

DESCRIPTION:
   The main auto-generated file for MMSS.


==============================================================================

$Header: //components/rel/boot.xf/1.4/QcomPkg/Sdm660Pkg/Library/HALclkLib/HALclkMMSSMain.c#4 $

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

#define  HAL_CLK_CHIP_FAMILY_SDM630  77

/* ============================================================================
**    Prototypes
** ==========================================================================*/


/* ============================================================================
**    Externs
** ==========================================================================*/



/*
 * Clock domains
 */
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSAHBClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSAXIClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSBYTE0ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSBYTE1ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSCAMSSGP0ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSCAMSSGP1ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSCCIClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSCOREPISLEEPCLKClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSCPPClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSCSI0ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSCSI0PHYTIMERClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSCSI1ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSCSI1PHYTIMERClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSCSI2ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSCSI2PHYTIMERClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSCSI3ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSCSIPHYClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSCXOClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSDPAUXClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSDPCRYPTOClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSDPGTCClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSDPLINKClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSDPPIXELClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSESC0ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSESC1ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSJPEG0ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSMCLK0ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSMCLK1ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSMCLK2ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSMCLK3ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSMDPClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSPCLK0ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSPCLK1ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSROTClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSVFE0ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSVFE1ClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSVIDEOCOREClkDomain;
extern HAL_clk_ClockDomainDescType HAL_clk_mMMSSVSYNCClkDomain;

/*
 * Power domains
 */
extern HAL_clk_PowerDomainDescType HAL_clk_mMMSSBIMCSMMUPowerDomain;
extern HAL_clk_PowerDomainDescType HAL_clk_mMMSSCAMSSCPPPowerDomain;
extern HAL_clk_PowerDomainDescType HAL_clk_mMMSSCAMSSTOPPowerDomain;
extern HAL_clk_PowerDomainDescType HAL_clk_mMMSSCAMSSVFE0PowerDomain;
extern HAL_clk_PowerDomainDescType HAL_clk_mMMSSCAMSSVFE1PowerDomain;
extern HAL_clk_PowerDomainDescType HAL_clk_mMMSSMDSSPowerDomain;
extern HAL_clk_PowerDomainDescType HAL_clk_mMMSSVIDEOSUBCORE0PowerDomain;
extern HAL_clk_PowerDomainDescType HAL_clk_mMMSSVIDEOTOPPowerDomain;

static void HAL_clk_aMMSSClockDomainDesc_update(HAL_clk_ClockDomainDescType **pmClockDomainDesc);
static void HAL_clk_remove_domain(HAL_clk_ClockDomainDescType **pmClockDomainDesc, HAL_clk_ClockDomainDescType *pClockDomain);
/* ============================================================================
**    Data
** ==========================================================================*/


/*
 * aMMSSSourceMap
 *
 * MMSS HW source mapping
 *
 */
static HAL_clk_SourceMapType aMMSSSourceMap[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_MMPLL0,             1 },
  { HAL_CLK_SOURCE_MMPLL4,             2 },
  { HAL_CLK_SOURCE_MMPLL7,             3 },
  { HAL_CLK_SOURCE_MMPLL8,             4 },
  { HAL_CLK_SOURCE_GPLL0,              5 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mMMSSClockDomainControl
 *
 * Functions for controlling MMSS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mMMSSClockDomainControl =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aMMSSSourceMap
};


/*
 * HAL_clk_mMMSSClockDomainControlRO
 *
 * Read-only functions for MMSS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mMMSSClockDomainControlRO =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aMMSSSourceMap
};


/*
 * aMMSSSourceMap_1
 *
 * MMSS HW source mapping
 *
 */
static HAL_clk_SourceMapType aMMSSSourceMap_1[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_EXTERNAL1,          1 },
  { HAL_CLK_SOURCE_EXTERNAL2,          2 },
  { HAL_CLK_SOURCE_GROUND,             3 },
  { HAL_CLK_SOURCE_GROUND,             4 },
  { HAL_CLK_SOURCE_GROUND,             5 },
  { HAL_CLK_SOURCE_GROUND,             6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
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
 * aMMSSSourceMap_2
 *
 * MMSS HW source mapping
 *
 */
static HAL_clk_SourceMapType aMMSSSourceMap_2[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_MMPLL4,             1 },
  { HAL_CLK_SOURCE_MMPLL7,             2 },
  { HAL_CLK_SOURCE_MMPLL10,            3 },
  { HAL_CLK_SOURCE_SLEEPCLK,           4 },
  { HAL_CLK_SOURCE_GPLL0,              5 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mMMSSClockDomainControl_2
 *
 * Functions for controlling MMSS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mMMSSClockDomainControl_2 =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aMMSSSourceMap_2
};


/*
 * HAL_clk_mMMSSClockDomainControlRO_2
 *
 * Read-only functions for MMSS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mMMSSClockDomainControlRO_2 =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aMMSSSourceMap_2
};


/*
 * aMMSSSourceMap_3
 *
 * MMSS HW source mapping
 *
 */
static HAL_clk_SourceMapType aMMSSSourceMap_3[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_MMPLL0,             1 },
  { HAL_CLK_SOURCE_MMPLL4,             2 },
  { HAL_CLK_SOURCE_MMPLL7,             3 },
  { HAL_CLK_SOURCE_MMPLL10,            4 },
  { HAL_CLK_SOURCE_GPLL0,              5 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mMMSSClockDomainControl_3
 *
 * Functions for controlling MMSS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mMMSSClockDomainControl_3 =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aMMSSSourceMap_3
};


/*
 * HAL_clk_mMMSSClockDomainControlRO_3
 *
 * Read-only functions for MMSS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mMMSSClockDomainControlRO_3 =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aMMSSSourceMap_3
};


/*
 * aMMSSSourceMap_4
 *
 * MMSS HW source mapping
 *
 */
static HAL_clk_SourceMapType aMMSSSourceMap_4[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_MMPLL0,             1 },
  { HAL_CLK_SOURCE_MMPLL7,             2 },
  { HAL_CLK_SOURCE_MMPLL10,            3 },
  { HAL_CLK_SOURCE_SLEEPCLK,           4 },
  { HAL_CLK_SOURCE_GPLL0,              5 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mMMSSClockDomainControl_4
 *
 * Functions for controlling MMSS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mMMSSClockDomainControl_4 =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aMMSSSourceMap_4
};


/*
 * HAL_clk_mMMSSClockDomainControlRO_4
 *
 * Read-only functions for MMSS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mMMSSClockDomainControlRO_4 =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aMMSSSourceMap_4
};


/*
 * aMMSSSourceMap_5
 *
 * MMSS HW source mapping
 *
 */
static HAL_clk_SourceMapType aMMSSSourceMap_5[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_MMPLL0,             1 },
  { HAL_CLK_SOURCE_MMPLL4,             2 },
  { HAL_CLK_SOURCE_MMPLL7,             3 },
  { HAL_CLK_SOURCE_MMPLL10,            4 },
  { HAL_CLK_SOURCE_MMPLL6,             5 },
  { HAL_CLK_SOURCE_GPLL0,              6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mMMSSClockDomainControl_5
 *
 * Functions for controlling MMSS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mMMSSClockDomainControl_5 =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aMMSSSourceMap_5
};


/*
 * HAL_clk_mMMSSClockDomainControlRO_5
 *
 * Read-only functions for MMSS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mMMSSClockDomainControlRO_5 =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aMMSSSourceMap_5
};


/*
 * aMMSSSourceMap_6
 *
 * MMSS HW source mapping
 * 
 */
static HAL_clk_SourceMapType aMMSSSourceMap_6[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_MMPLL0,             1 },
  { HAL_CLK_SOURCE_MMPLL5,             2 },
  { HAL_CLK_SOURCE_MMPLL7,             3 },
  { HAL_CLK_SOURCE_GROUND,             4 },
  { HAL_CLK_SOURCE_GPLL0,              5 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mMMSSClockDomainControl_6
 *
 * Functions for controlling MMSS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mMMSSClockDomainControl_6 =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aMMSSSourceMap_6
};


/*
 * HAL_clk_mMMSSClockDomainControlRO_6
 *
 * Read-only functions for MMSS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mMMSSClockDomainControlRO_6 =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aMMSSSourceMap_6
};


/*
 * aMMSSSourceMap_7
 *
 * MMSS HW source mapping
 * 
 */
static HAL_clk_SourceMapType aMMSSSourceMap_7[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_MMPLL0,             1 },
  { HAL_CLK_SOURCE_MMPLL4,             2 },
  { HAL_CLK_SOURCE_MMPLL7,             3 },
  { HAL_CLK_SOURCE_MMPLL10,            4 },
  { HAL_CLK_SOURCE_GPLL0,              5 },
  { HAL_CLK_SOURCE_MMPLL6,             6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mMMSSClockDomainControl_7
 *
 * Functions for controlling MMSS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mMMSSClockDomainControl_7 =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aMMSSSourceMap_7
};


/*
 * HAL_clk_mMMSSClockDomainControlRO_7
 *
 * Read-only functions for MMSS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mMMSSClockDomainControlRO_7 =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aMMSSSourceMap_7
};


/*
 * aMMSSSourceMap_8
 *
 * MMSS HW source mapping
 * 
 */
static HAL_clk_SourceMapType aMMSSSourceMap_8[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_MMPLL0,             1 },
  { HAL_CLK_SOURCE_MMPLL1,             2 },
  { HAL_CLK_SOURCE_MMPLL6,             3 },
  { HAL_CLK_SOURCE_GROUND,             4 },
  { HAL_CLK_SOURCE_GPLL0,              5 },
  { HAL_CLK_SOURCE_GPLL0_DIV2,         6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mMMSSClockDomainControl_8
 *
 * Functions for controlling MMSS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mMMSSClockDomainControl_8 =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aMMSSSourceMap_8
};


/*
 * HAL_clk_mMMSSClockDomainControlRO_8
 *
 * Read-only functions for MMSS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mMMSSClockDomainControlRO_8 =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aMMSSSourceMap_8
};


/*
 * aMMSSSourceMap_9
 *
 * MMSS HW source mapping
 * 
 */
static HAL_clk_SourceMapType aMMSSSourceMap_9[] =
{
  { HAL_CLK_SOURCE_XO,                 0 },
  { HAL_CLK_SOURCE_MMPLL0,             1 },
  { HAL_CLK_SOURCE_MMPLL8,             2 },
  { HAL_CLK_SOURCE_MMPLL3,             3 },
  { HAL_CLK_SOURCE_MMPLL6,             4 },
  { HAL_CLK_SOURCE_GPLL0,              5 },
  { HAL_CLK_SOURCE_MMPLL7,             6 },
  { HAL_CLK_SOURCE_PLLTEST,            7 },
  { HAL_CLK_SOURCE_NULL,               HAL_CLK_SOURCE_INDEX_INVALID }
};


/*
 * HAL_clk_mMMSSClockDomainControl_9
 *
 * Functions for controlling MMSS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mMMSSClockDomainControl_9 =
{
   /* .ConfigMux          = */ HAL_clk_GenericConfigMux,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aMMSSSourceMap_9
};


/*
 * HAL_clk_mMMSSClockDomainControlRO_9
 *
 * Read-only functions for MMSS clock domains
 */
HAL_clk_ClockDomainControlType HAL_clk_mMMSSClockDomainControlRO_9 =
{
   /* .ConfigMux          = */ NULL,
   /* .DetectMuxConfig    = */ HAL_clk_GenericDetectMuxConfig,
   /* .pmSourceMap        = */ aMMSSSourceMap_9
};


/*
 * HAL_clk_aMMSSClockDomainDesc
 *
 * List of MMSS clock domains
*/
static HAL_clk_ClockDomainDescType * HAL_clk_aMMSSClockDomainDesc [] =
{
  &HAL_clk_mMMSSAHBClkDomain,
  &HAL_clk_mMMSSAXIClkDomain,
  &HAL_clk_mMMSSBYTE0ClkDomain, 
  &HAL_clk_mMMSSBYTE1ClkDomain,
  &HAL_clk_mMMSSCAMSSGP0ClkDomain,
  &HAL_clk_mMMSSCAMSSGP1ClkDomain,
  &HAL_clk_mMMSSCCIClkDomain,
  &HAL_clk_mMMSSCOREPISLEEPCLKClkDomain,
  &HAL_clk_mMMSSCPPClkDomain,
  &HAL_clk_mMMSSCSI0ClkDomain,
  &HAL_clk_mMMSSCSI0PHYTIMERClkDomain,
  &HAL_clk_mMMSSCSI1ClkDomain,
  &HAL_clk_mMMSSCSI1PHYTIMERClkDomain,
  &HAL_clk_mMMSSCSI2ClkDomain,
  &HAL_clk_mMMSSCSI2PHYTIMERClkDomain,
  &HAL_clk_mMMSSCSI3ClkDomain,
  &HAL_clk_mMMSSCSIPHYClkDomain,
  &HAL_clk_mMMSSCXOClkDomain,
  &HAL_clk_mMMSSDPAUXClkDomain,
  &HAL_clk_mMMSSDPCRYPTOClkDomain,
  &HAL_clk_mMMSSDPGTCClkDomain,
  &HAL_clk_mMMSSDPLINKClkDomain,
  &HAL_clk_mMMSSDPPIXELClkDomain,
  &HAL_clk_mMMSSESC0ClkDomain,
  &HAL_clk_mMMSSESC1ClkDomain,
  &HAL_clk_mMMSSJPEG0ClkDomain,
  &HAL_clk_mMMSSMCLK0ClkDomain,
  &HAL_clk_mMMSSMCLK1ClkDomain,
  &HAL_clk_mMMSSMCLK2ClkDomain,
  &HAL_clk_mMMSSMCLK3ClkDomain,
  &HAL_clk_mMMSSMDPClkDomain,
  &HAL_clk_mMMSSPCLK0ClkDomain,
  &HAL_clk_mMMSSPCLK1ClkDomain,
  &HAL_clk_mMMSSROTClkDomain,
  &HAL_clk_mMMSSVFE0ClkDomain,
  &HAL_clk_mMMSSVFE1ClkDomain,
  &HAL_clk_mMMSSVIDEOCOREClkDomain,
  &HAL_clk_mMMSSVSYNCClkDomain,
  NULL
};


/*
 * HAL_clk_aMMSSPowerDomainDesc
 *
 * List of MMSS power domains
 */
static HAL_clk_PowerDomainDescType * HAL_clk_aMMSSPowerDomainDesc [] =
{
  &HAL_clk_mMMSSBIMCSMMUPowerDomain,
  &HAL_clk_mMMSSCAMSSCPPPowerDomain,
  &HAL_clk_mMMSSCAMSSTOPPowerDomain,
  &HAL_clk_mMMSSCAMSSVFE0PowerDomain,
  &HAL_clk_mMMSSCAMSSVFE1PowerDomain,
  &HAL_clk_mMMSSMDSSPowerDomain,
  &HAL_clk_mMMSSVIDEOSUBCORE0PowerDomain,
  &HAL_clk_mMMSSVIDEOTOPPowerDomain,
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
   * Update clock domain if any specific
   */	
  HAL_clk_aMMSSClockDomainDesc_update(HAL_clk_aMMSSClockDomainDesc);

  /*
   * Install all clock domains
   */
  HAL_clk_InstallClockDomains(HAL_clk_aMMSSClockDomainDesc, MMSS_BASE);

  /*
   * Install all power domains
   */
  HAL_clk_InstallPowerDomains(HAL_clk_aMMSSPowerDomainDesc, MMSS_BASE);

} /* END HAL_clk_PlatformInitMMSSMain */


/* ===========================================================================
**  HAL_clk_aGCCClockDomainDesc_update
**
** ======================================================================== */
void HAL_clk_aMMSSClockDomainDesc_update(HAL_clk_ClockDomainDescType **pmClockDomainDesc)
{
  if(HAL_clk_GetChipFamily() == HAL_CLK_CHIP_FAMILY_SDM630)
  {
    HAL_clk_remove_domain(pmClockDomainDesc, &HAL_clk_mMMSSPCLK1ClkDomain);
    HAL_clk_remove_domain(pmClockDomainDesc, &HAL_clk_mMMSSESC1ClkDomain);
    HAL_clk_remove_domain(pmClockDomainDesc, &HAL_clk_mMMSSBYTE1ClkDomain);
  } 
} /* END HAL_clk_aMMSSClockDomainDesc_update */

/* ===========================================================================
**  HAL_clk_remove_domain
**
** ======================================================================== */
void HAL_clk_remove_domain(HAL_clk_ClockDomainDescType **pmClockDomainDesc, HAL_clk_ClockDomainDescType *pClockDomain)
{
    while(*pmClockDomainDesc != pClockDomain)
    {
       pmClockDomainDesc++;
    }
    while(*pmClockDomainDesc != NULL)
    {
       *pmClockDomainDesc  =  *(pmClockDomainDesc + 1);
       pmClockDomainDesc++;
    }
}  /* END HAL_clk_remove_domain */
