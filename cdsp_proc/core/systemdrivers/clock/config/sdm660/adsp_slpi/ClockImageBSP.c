/*
==============================================================================

FILE:         ClockImageBSP.c

DESCRIPTION:
  This file contains clock regime BSP data for DAL based driver.

==============================================================================

                             Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/config/sdm660/adsp_slpi/ClockImageBSP.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------- 
11/12/16   shm     Removing SCCPLL from ClockSourcesToInit as it is being
                   enabled in __hexagon_bsp_init.
11/11/16   shm     Updating Q6 perf config.
10/04/15   shm     First version for SDM660.

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
#include "ClockLPASSBSP.h"
#include "comdef.h"
#include "VCSDefs.h"

/*
 * Pull in auto-generated BSP files.
 */
#include "ClockBSP.c"
#include "ClockLPASSBSP.c"

/*=========================================================================
      Externally defined structures
==========================================================================*/


/*=========================================================================
      Data declarations
==========================================================================*/

/*
 * Resources that need to be published to domains outside GuestOS.
 */
static const char *ClockPubResource[] =
{
   CLOCK_NPA_RESOURCE_QDSS
};

ClockNPAResourcePubType ClockResourcePub = 
{
   SENSOR_PD,
   ClockPubResource,
   1
};


/*
 * Performance level configuration data for the Q6 clock.
 */
static ClockCPUPerfConfigType Clock_Q6PerfConfig[] =
{
  {
    .HWVersion      = {{0x00, 0x00}, {0xFF, 0xFF}},
    .nMinPerfLevel  = CLOCK_QDSP6SS_PERF_LEVEL_0,
    .nMaxPerfLevel  = CLOCK_QDSP6SS_PERF_LEVEL_7,
    .anPerfLevel    = (uint32*)Clock_QDSP6SSPerfLevels,
    .nNumPerfLevels = ARR_SIZE(Clock_QDSP6SSPerfLevels)
  },
};

/*
 * Image BSP data
 */
const ClockImageBSPConfigType ClockImageBSPConfig =
{
  .bEnableDCS              = TRUE,
  .pCPUConfig              = Clock_QDSP6SSConfig,
  .pCPUPerfConfig          = Clock_Q6PerfConfig,
  .nNumCPUPerfLevelConfigs = ARR_SIZE(Clock_Q6PerfConfig),
  .nCPUBootPerfLevel       = CLOCK_QDSP6SS_CONFIG_748P8MHz,
  .eCPU                    = CLOCK_CPU_LPASS_Q6,
  .eRail                   = VCS_RAIL_LPI_CX,
  .szRailName              = VCS_NPA_RESOURCE_VDD_LPI_CX
};


const HAL_clk_HWIOBaseType ClockLPASSHWIOBases = 
{
  /* nPhysAddress */ 0x15000000,
  /* nSize        */ 0x58000
};


/*
 * Voltage warmup table mapping used for coming out of retention.
 */
const Clock_VRegWarmUpType Clock_VRegWarmupTable[VCS_CORNER_NUM_OF_CORNERS] =
{
  {VCS_CORNER_OFF,            0      },
  {VCS_CORNER_RETENTION,      400000 },
  {VCS_CORNER_RETENTION_PLUS, 400000 },
  {VCS_CORNER_LOW_MIN,        584000 },
  {VCS_CORNER_LOW_MINUS,      648000 },
  {VCS_CORNER_LOW,            720000 },
  {VCS_CORNER_LOW_PLUS,       792000 },
  {VCS_CORNER_NOMINAL,        864000 },
  {VCS_CORNER_NOMINAL_PLUS,   920000 },
  {VCS_CORNER_TURBO,          992000 }
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
   { HAL_CLK_SOURCE_LPAPLL0, 564480000 },
   { HAL_CLK_SOURCE_LPAPLL2, 307200000 },
   { HAL_CLK_SOURCE_NULL,    NULL}
};
