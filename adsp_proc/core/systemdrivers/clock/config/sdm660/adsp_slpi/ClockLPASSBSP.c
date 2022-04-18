/*
==============================================================================

FILE:         ClockLPASSBSP.c

DESCRIPTION:
  This file contains clock BSP data for the DAL based driver.


==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/config/sdm660/adsp_slpi/ClockLPASSBSP.c#1 $

==============================================================================
            Copyright (c) 2016 Qualcomm Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockLPASSBSP.h"


/*=========================================================================
      Data Declarations
==========================================================================*/


/*
 * Enumeration of QDSP6SS performance levels.
 */
enum
{
  CLOCK_QDSP6SS_PERF_LEVEL_0,
  CLOCK_QDSP6SS_PERF_LEVEL_1,
  CLOCK_QDSP6SS_PERF_LEVEL_2,
  CLOCK_QDSP6SS_PERF_LEVEL_3,
  CLOCK_QDSP6SS_PERF_LEVEL_4,
  CLOCK_QDSP6SS_PERF_LEVEL_5,
  CLOCK_QDSP6SS_PERF_LEVEL_6,
  CLOCK_QDSP6SS_PERF_LEVEL_7,
  CLOCK_QDSP6SS_PERF_LEVEL_TOTAL
};


/*
 * Enumeration of QDSP6SS configurations.
 */
enum
{
  CLOCK_QDSP6SS_CONFIG_124P8MHz,
  CLOCK_QDSP6SS_CONFIG_249P6MHz,
  CLOCK_QDSP6SS_CONFIG_326P4MHz,
  CLOCK_QDSP6SS_CONFIG_499P2MHz,
  CLOCK_QDSP6SS_CONFIG_614P4MHz,
  CLOCK_QDSP6SS_CONFIG_748P8MHz,
  CLOCK_QDSP6SS_CONFIG_864P0MHz,
  CLOCK_QDSP6SS_CONFIG_998P4MHz,
  CLOCK_QDSP6SS_CONFIG_TOTAL
};


/*
 * Q6SSRCG performance levels mappings
 */
static uint32 Clock_QDSP6SSPerfLevels [] =
{
  CLOCK_QDSP6SS_CONFIG_124P8MHz,
  CLOCK_QDSP6SS_CONFIG_249P6MHz,
  CLOCK_QDSP6SS_CONFIG_326P4MHz,
  CLOCK_QDSP6SS_CONFIG_499P2MHz,
  CLOCK_QDSP6SS_CONFIG_614P4MHz,
  CLOCK_QDSP6SS_CONFIG_748P8MHz,
  CLOCK_QDSP6SS_CONFIG_864P0MHz,
  CLOCK_QDSP6SS_CONFIG_998P4MHz,
};


/*=========================================================================
      Data
==========================================================================*/


/*
 * QDSP6SS clock configurations
 */
static ClockCPUConfigType Clock_QDSP6SSConfig[] =
{
  /* NOTE: Divider value is (2*Div) due to potential use of fractional values */
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA,
    /* .Mux             = */
    {
      /* .nFreq             = */  124796928,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_SCCPLL0, 4, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_LOW_MIN,
      /* .HWVersion         = */  { {0x00, 0x00}, {0xFF, 0xFF} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_SCCPLL0[0]
    },
  },
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA,
    /* .Mux             = */
    {
      /* .nFreq             = */  249593856,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_SCCPLL0, 2, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_LOW_MINUS,
      /* .HWVersion         = */  { {0x00, 0x00}, {0xFF, 0xFF} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_SCCPLL0[0]
    },
  },
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA,
    /* .Mux             = */
    {
      /* .nFreq             = */  326400000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_LPAPLL1, 4, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_LOW_MINUS,
      /* .HWVersion         = */  { {0x00, 0x00}, {0xFF, 0xFF} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_LPAPLL1[1] // 652.8 MHz
    },
  },
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA,
    /* .Mux             = */
    {
      /* .nFreq             = */  499200000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_LPAPLL1, 4, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_LOW,
      /* .HWVersion         = */  { {0x00, 0x00}, {0xFF, 0xFF} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_LPAPLL1[5] // 998.4 MHz
    },
  },
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA,
    /* .Mux             = */
    {
      /* .nFreq             = */  614400000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_LPAPLL1, 2, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_LOW_PLUS,
      /* .HWVersion         = */  { {0x00, 0x00}, {0xFF, 0xFF} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_LPAPLL1[0] // 614.4 MHz
    },
  },
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA,
    /* .Mux             = */
    {
      /* .nFreq             = */  748800000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_LPAPLL1, 2, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_NOMINAL,
      /* .HWVersion         = */  { {0x00, 0x00}, {0xFF, 0xFF} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_LPAPLL1[2] // 748.8 MHz
    },
  },
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA,
    /* .Mux             = */
    {
      /* .nFreq             = */  864000000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_LPAPLL1, 2, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_NOMINAL_PLUS,
      /* .HWVersion         = */  { {0x00, 0x00}, {0xFF, 0xFF} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_LPAPLL1[4] // 864.0 MHz
    },
  },
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA,
    /* .Mux             = */
    {
      /* .nFreq             = */  998400000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_LPAPLL1, 2, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_TURBO,
      /* .HWVersion         = */  { {0x00, 0x00}, {0xFF, 0xFF} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_LPAPLL1[5] // 998.4 MHz
    },
  },
  { 0 }
};
