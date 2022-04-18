/*
==============================================================================

FILE:         ClockBSP.c

DESCRIPTION:
  This file contains clock regime bsp data for DAL based driver.

==============================================================================

                             Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/config/sdm660/cdsp/ClockImageBSP.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------- 
04/13/15   dcf     Ported for 8996.
04/12/14   dcf     Created. 

==============================================================================
            Copyright (c) 2016 Qualcomm Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockBSP.h"
#include "ClockTURINGBSP.h"
#include "comdef.h"
#include "VCSDefs.h"

/*
 * Pull in auto-generated BSP files.
 */
#include "ClockBSP.c"


/*=========================================================================
      Data Declarations
==========================================================================*/
/*
 * Enumeration of TURINGQ6SSRCG performance levels.
 */
enum
{
  CLOCK_QDSP6SS_PERF_LEVEL_0,
  CLOCK_QDSP6SS_PERF_LEVEL_1,
  CLOCK_QDSP6SS_PERF_LEVEL_2,
  CLOCK_QDSP6SS_PERF_LEVEL_3,
  CLOCK_QDSP6SS_PERF_LEVEL_4,
  CLOCK_QDSP6SS_PERF_LEVEL_TOTAL
};


/*
 * Enumeration of TURINGQ6SSRCG configurations.
 */
enum
{
  CLOCK_QDSP6SS_CONFIG_144P0MHz,
  CLOCK_QDSP6SS_CONFIG_297P6MHz,
  CLOCK_QDSP6SS_CONFIG_480P0MHz,
  CLOCK_QDSP6SS_CONFIG_652P8MHz,
  CLOCK_QDSP6SS_CONFIG_787P2MHz,
  CLOCK_QDSP6SS_CONFIG_TOTAL
};


/*
 * TURINGQ6SSRCG performance levels mappings
 */
static uint32 CLOCK_QDSP6SSPerfLevels [] =
{
  CLOCK_QDSP6SS_CONFIG_144P0MHz,
  CLOCK_QDSP6SS_CONFIG_297P6MHz,
  CLOCK_QDSP6SS_CONFIG_480P0MHz,
  CLOCK_QDSP6SS_CONFIG_652P8MHz,
  CLOCK_QDSP6SS_CONFIG_787P2MHz,
};


/*=========================================================================
      Data
==========================================================================*/


/*
 * QDSP6SS clock configurations
 */
static ClockCPUConfigType Clock_QDSP6SSConfig[] =
{
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA, 
    /* .Mux             = */
    {
      /* .nFreq             = */  144000000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_TURINGPLL1, 8, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_LOW_MINUS,
      /* .HWVersion         = */  { {0x00, 0x00}, {0xFF, 0xFF} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_TURINGPLL1[0] // 576.0 MHz
    },
  },
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA, 
    /* .Mux             = */
    {
      /* .nFreq             = */  297600000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_TURINGPLL1, 4, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_LOW_MINUS,
      /* .HWVersion         = */  { {0x00, 0x00}, {0xFF, 0xFF} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_TURINGPLL1[1] // 595.2 MHz
    },
  },
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA, 
    /* .Mux             = */
    {
      /* .nFreq             = */  480000000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_TURINGPLL1, 4, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_LOW,
      /* .HWVersion         = */  { {0x00, 0x00}, {0xFF, 0xFF} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_TURINGPLL1[5] // 960.0 MHz
    },
  },
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA, 
    /* .Mux             = */
    {
      /* .nFreq             = */  652800000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_TURINGPLL1, 2, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_NOMINAL,
      /* .HWVersion         = */  { {0x00, 0x00}, {0xFF, 0xFF} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_TURINGPLL1[2] // 652.8 MHz
    },
  },
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA, 
    /* .Mux             = */
    {
      /* .nFreq             = */  787200000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_TURINGPLL1, 2, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_TURBO,
      /* .HWVersion         = */  { {0x00, 0x00}, {0xFF, 0xFF} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_TURINGPLL1[4] // 787.2 MHz
    },
  },
  { 0 }
};



/*
 * Performance level configuration data for the Q6 clock.
 */
static ClockCPUPerfConfigType Clock_Q6PerfConfig[] =
{
  {
    .HWVersion      = {{0, 0}, {0xFF, 0xFF}},
    .nSpeedBinFuse  = 0x4,
    .nMinPerfLevel  = CLOCK_QDSP6SS_PERF_LEVEL_0,
    .nMaxPerfLevel  = CLOCK_QDSP6SS_PERF_LEVEL_3,
    .anPerfLevel    = (uint32*)CLOCK_QDSP6SSPerfLevels,
    .nNumPerfLevels = ARR_SIZE(CLOCK_QDSP6SSPerfLevels)
  },
  {
    .HWVersion      = {{0, 0}, {0xFF, 0xFF}},
    .nSpeedBinFuse  = 0xFF,
    .nMinPerfLevel  = CLOCK_QDSP6SS_PERF_LEVEL_0,
    .nMaxPerfLevel  = CLOCK_QDSP6SS_PERF_LEVEL_4,
    .anPerfLevel    = (uint32*)CLOCK_QDSP6SSPerfLevels,
    .nNumPerfLevels = ARR_SIZE(CLOCK_QDSP6SSPerfLevels)
  },
};


/*
 * Image BSP data
 */
const ClockImageBSPConfigType ClockImageBSPConfig =
{
  .bEnableDCS              = TRUE,
  .bEnableCXiPeakLM        = TRUE,
  .pCPUConfig              = Clock_QDSP6SSConfig,
  .pCPUPerfConfig          = Clock_Q6PerfConfig,
  .nNumCPUPerfLevelConfigs = ARR_SIZE(Clock_Q6PerfConfig),
  .nCPUBootPerfLevel       = CLOCK_QDSP6SS_CONFIG_652P8MHz,
  .eCPU                    = CLOCK_CPU_TURING_Q6,
  .eRail                   = VCS_RAIL_CX,
  .szRailName              = VCS_NPA_RESOURCE_VDD_CX
};


const HAL_clk_HWIOBaseType ClockTURINGHWIOBases = 
{
   /* nPhysAddress */ 0x1A000000,
   /* nSize        */ 0x3F000
};

/*
 * Stub flags.
 */
const ClockStubType ClockStubConfig =
{
  .bRUMI   = FALSE,
  .bVirtio = FALSE,
};


/*
 *  ClockSourcesToInit
 *
 *  Array of sources and settings to initialize at runtime.
 */
const ClockSourceInitType ClockSourcesToInit[] =
{
   { HAL_CLK_SOURCE_TURINGPLL0, 307200 * 1000 },
   { HAL_CLK_SOURCE_NULL,       NULL}
};



