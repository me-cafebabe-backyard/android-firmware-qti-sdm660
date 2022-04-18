/*
==============================================================================

FILE:         ClockLPASSBSP.c 

DESCRIPTION:
  This file contains clock bsp data for the DAL based driver.


==============================================================================

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/config/msm8998/slpi/ClockCPUBSP.c#1 $

==============================================================================
            Copyright (c) 2016 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockSSCCPU.h"


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
  CLOCK_QDSP6SSCORE_PERF_LEVEL_TOTAL
};


/*
 * Enumeration of QDSP6SSCORE configurations.
 */
enum
{
  CLOCK_QDSP6SSCORE_CONFIG_100P0MHz,
  CLOCK_QDSP6SSCORE_CONFIG_200P0MHz,
  CLOCK_QDSP6SSCORE_CONFIG_300P0MHz,
  CLOCK_QDSP6SSCORE_CONFIG_500P0MHz,
  CLOCK_QDSP6SSCORE_CONFIG_700P0MHz,
  CLOCK_QDSP6SSCORE_CONFIG_TOTAL
};


/*
 * QDSP6SSCORE performance levels mappings
 */
static uint32 Clock_QDSP6SSCOREPerfLevels [] =
{
  CLOCK_QDSP6SSCORE_CONFIG_100P0MHz,
  CLOCK_QDSP6SSCORE_CONFIG_200P0MHz,
  CLOCK_QDSP6SSCORE_CONFIG_300P0MHz,
  CLOCK_QDSP6SSCORE_CONFIG_500P0MHz,
  CLOCK_QDSP6SSCORE_CONFIG_700P0MHz,
};


/*=========================================================================
      Data
==========================================================================*/

/*
 * Mux configuration for different CPU frequencies. 
 */
static ClockCPUConfigType Clock_QDSP6SSCOREConfig [] =
{
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCD,
    /* .Mux               */ {
    /* .nFreq             */   100000000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_SCCPLL0, 12, 0, 0, 0 },
    /* .eVRegLevel        */   VCS_CORNER_LOW_MINUS,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_SCC_PLL[0]
                             },
    /* .nStrapACCVal      */ 0x00000020
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCD,
    /* .Mux               */ {
    /* .nFreq             */   200000000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_SCCPLL0, 6, 0, 0, 0 },
    /* .eVRegLevel        */   VCS_CORNER_LOW_MINUS,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_SCC_PLL[0]
                             },
    /* .nStrapACCVal      */ 0x00000020
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCD,
    /* .Mux               */ {
    /* .nFreq             */   300000000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_SCCPLL0, 4, 0, 0, 0 },
    /* .eVRegLevel        */   VCS_CORNER_LOW,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_SCC_PLL[0]
                             },
    /* .nStrapACCVal      */ 0x00000020
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA,
    /* .Mux               */ {
    /* .nFreq             */   550000000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_SCCPLL1, 2, 0, 0, 0 },
    /* .eVRegLevel        */   VCS_CORNER_NOMINAL,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_SSCPLL1[0]
                             },
    /* .nStrapACCVal      */ 0x00000020
  },
  {
    /* .CoreConfig        */ HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA,
    /* .Mux               */ {
    /* .nFreq             */   700000000,
    /* .HALConfig         */   { HAL_CLK_SOURCE_SCCPLL1, 2, 0, 0, 0 },
    /* .eVRegLevel        */   VCS_CORNER_TURBO,
    /* .HWVersion         */   { {0x0, 0x0}, {0xFF, 0xFF} },
    /* .pSourceFreqConfig */   &SourceFreqConfig_SSCPLL1[1]
                             },
    /* .nStrapACCVal      */ 0x00000020
  }
};



