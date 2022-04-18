/*
==============================================================================

FILE:         ClockLPASSBSP.c 

DESCRIPTION:
  This file contains clock bsp data for the DAL based driver.


==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/config/msm8998/slpi/ClockLPASSBSP.c#1 $

==============================================================================
            Copyright (c) 2016 QUALCOMM Technologies Incorporated.
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
 * Enumeration of QDSP6SSCORE performance levels.
 */
enum
{
  CLOCK_QDSP6SSCORE_PERF_LEVEL_0,
  CLOCK_QDSP6SSCORE_PERF_LEVEL_1,
  CLOCK_QDSP6SSCORE_PERF_LEVEL_2,
  CLOCK_QDSP6SSCORE_PERF_LEVEL_3,
  CLOCK_QDSP6SSCORE_PERF_LEVEL_4,
  CLOCK_QDSP6SSCORE_PERF_LEVEL_5,
  CLOCK_QDSP6SSCORE_PERF_LEVEL_6,
  CLOCK_QDSP6SSCORE_PERF_LEVEL_7,
  CLOCK_QDSP6SSCORE_PERF_LEVEL_8,
  CLOCK_QDSP6SSCORE_PERF_LEVEL_9,
  CLOCK_QDSP6SSCORE_PERF_LEVEL_10,
  CLOCK_QDSP6SSCORE_PERF_LEVEL_TOTAL
};


/*
 * Enumeration of QDSP6SSCORE configurations.
 */
enum
{
  CLOCK_QDSP6SSCORE_CONFIG_19P2MHz,
  CLOCK_QDSP6SSCORE_CONFIG_144P0MHz,
  CLOCK_QDSP6SSCORE_CONFIG_192P0MHz,
  CLOCK_QDSP6SSCORE_CONFIG_307P2MHz,
  CLOCK_QDSP6SSCORE_CONFIG_384P0MHz,
  CLOCK_QDSP6SSCORE_CONFIG_499P2MHz,
  CLOCK_QDSP6SSCORE_CONFIG_595P2MHz,
  CLOCK_QDSP6SSCORE_CONFIG_672P0MHz,
  CLOCK_QDSP6SSCORE_CONFIG_787P2MHz,
  CLOCK_QDSP6SSCORE_CONFIG_844P8MHz,
  CLOCK_QDSP6SSCORE_CONFIG_998P4MHz,
  CLOCK_QDSP6SSCORE_CONFIG_TOTAL
};


/*
 * QDSP6SSCORE performance levels mappings
 */
static uint32 Clock_QDSP6SSCOREPerfLevels [] =
{
  CLOCK_QDSP6SSCORE_CONFIG_19P2MHz,
  CLOCK_QDSP6SSCORE_CONFIG_144P0MHz,
  CLOCK_QDSP6SSCORE_CONFIG_192P0MHz,
  CLOCK_QDSP6SSCORE_CONFIG_307P2MHz,
  CLOCK_QDSP6SSCORE_CONFIG_384P0MHz,
  CLOCK_QDSP6SSCORE_CONFIG_499P2MHz,
  CLOCK_QDSP6SSCORE_CONFIG_595P2MHz,
  CLOCK_QDSP6SSCORE_CONFIG_672P0MHz,
  CLOCK_QDSP6SSCORE_CONFIG_787P2MHz,
  CLOCK_QDSP6SSCORE_CONFIG_844P8MHz,
  CLOCK_QDSP6SSCORE_CONFIG_998P4MHz,
};


/*=========================================================================
      Data
==========================================================================*/


/*
 * The LPAPLL1 source frequency configurations are defined in ClockBSP.c
 */
extern ClockSourceFreqConfigType SourceFreqConfig_LPAPLL1[10];


/*
 * QDSP6SSCORE clock configurations
 */
static ClockQDSP6SSCOREConfigType Clock_QDSP6SSCOREConfig[] =
{
  /* NOTE: Divider value is (2*Div) due to potential use of fractional values */
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_MUX, /* TODO */
    /* .Mux             = */
    {
      /* .nFreq             = */  19200000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_XO, 2, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_LOW_MINUS,
      /* .HWVersion         = */  { {0x00, 0x00}, {0x00, 0x00} },
      /* .pSourceFreqConfig = */  NULL
    },
  },
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_MUX, /* TODO */
    /* .Mux             = */
    {
      /* .nFreq             = */  144000000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_LPAPLL1, 4, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_LOW_MINUS,
      /* .HWVersion         = */  { {0x00, 0x00}, {0x02, 0x00} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_LPAPLL1[0] // 288.0 MHz
    },
  },
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_MUX, /* TODO */
    /* .Mux             = */
    {
      /* .nFreq             = */  192000000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_LPAPLL1, 4, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_LOW_MINUS,
      /* .HWVersion         = */  { {0x02, 0x00}, {0xFF, 0xFF} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_LPAPLL1[2] // 384.0 MHz
    },
  },
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_MUX, /* TODO */
    /* .Mux             = */
    {
      /* .nFreq             = */  307200000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_LPAPLL1, 2, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_LOW_MINUS,
      /* .HWVersion         = */  { {0x00, 0x00}, {0x02, 0x00} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_LPAPLL1[1] // 307.2 MHz
    },
  },
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_MUX, /* TODO */
    /* .Mux             = */
    {
      /* .nFreq             = */  384000000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_LPAPLL1, 2, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_LOW_MINUS,
      /* .HWVersion         = */  { {0x02, 0x00}, {0xFF, 0xFF} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_LPAPLL1[2] // 384.0 MHz
    },
  },
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_MUX, /* TODO */
    /* .Mux             = */
    {
      /* .nFreq             = */  499200000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_LPAPLL1, 2, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_LOW,
      /* .HWVersion         = */  { {0x00, 0x00}, {0x02, 0x00} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_LPAPLL1[3] // 499.2 MHz
    },
  },
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_MUX, /* TODO */
    /* .Mux             = */
    {
      /* .nFreq             = */  595200000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_LPAPLL1, 2, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_LOW,
      /* .HWVersion         = */  { {0x02, 0x00}, {0xFF, 0xFF} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_LPAPLL1[4] // 595.2 MHz
    },
  },
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_MUX, /* TODO */
    /* .Mux             = */
    {
      /* .nFreq             = */  672000000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_LPAPLL1, 2, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_NOMINAL,
      /* .HWVersion         = */  { {0x00, 0x00}, {0x02, 0x00} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_LPAPLL1[5] // 672.0 MHz
    },
  },
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_MUX, /* TODO */
    /* .Mux             = */
    {
      /* .nFreq             = */  787200000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_LPAPLL1, 2, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_NOMINAL,
      /* .HWVersion         = */  { {0x02, 0x00}, {0xFF, 0xFF} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_LPAPLL1[6] // 787.2 MHz
    },
  },
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_MUX, /* TODO */
    /* .Mux             = */
    {
      /* .nFreq             = */  844800000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_LPAPLL1, 2, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_TURBO,
      /* .HWVersion         = */  { {0x00, 0x00}, {0x02, 0x00} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_LPAPLL1[7] // 844.8 MHz
    },
  },
  {
    /* .CoreConfig      = */  HAL_CLK_CONFIG_MUX, /* TODO */
    /* .Mux             = */
    {
      /* .nFreq             = */  998400000,
      /* .HALConfig         = */  { HAL_CLK_SOURCE_LPAPLL1, 2, 0, 0, 0 },
      /* .eVRegLevel        = */  VCS_CORNER_TURBO,
      /* .HWVersion         = */  { {0x02, 0x00}, {0xFF, 0xFF} },
      /* .pSourceFreqConfig = */  &SourceFreqConfig_LPAPLL1[8] // 998.4 MHz
    },
  },
  { 0 }
};

