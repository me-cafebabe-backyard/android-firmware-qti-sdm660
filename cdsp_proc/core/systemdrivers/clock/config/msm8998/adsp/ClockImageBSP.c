/*
==============================================================================

FILE:         ClockBSP.c

DESCRIPTION:
  This file contains clock regime bsp data for DAL based driver.

==============================================================================

                             Edit History

$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/config/msm8998/adsp/ClockImageBSP.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------- 
04/13/15   dcf     Ported for 8996.
04/12/14   dcf     Created. 

==============================================================================
            Copyright (c) 2014 - 2016 QUALCOMM Technologies Incorporated.
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

#define ClockQDSP6SSCOREConfigType ClockCPUConfigType

/*
 * Autogen naming convention
 */
#define HAL_CLK_CONFIG_MUX HAL_CLK_CONFIG_Q6SS_CORE_CLOCK_MUX_SRCA

/*
 * Pull in auto-generated BSP files.
 */
#include "ClockBSP.c"
#include "ClockLPASSBSP.c"

/*=========================================================================
      Externally defined structures
==========================================================================*/


/*=========================================================================
      Data Declarations
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
    .HWVersion      = {{0, 0}, {0xFF, 0xFF}},
    .nMinPerfLevel  = CLOCK_QDSP6SSCORE_PERF_LEVEL_1,
    .nMaxPerfLevel  = CLOCK_QDSP6SSCORE_PERF_LEVEL_10,
    .anPerfLevel    = (uint32*)Clock_QDSP6SSCOREPerfLevels,
    .nNumPerfLevels = ARR_SIZE(Clock_QDSP6SSCOREPerfLevels)
  },
};


/*
 * Image BSP data
 */
const ClockImageBSPConfigType ClockImageBSPConfig =
{
  .bEnableDCS              = TRUE,
  .pCPUConfig              = Clock_QDSP6SSCOREConfig,
  .pCPUPerfConfig          = Clock_Q6PerfConfig,
  .nNumCPUPerfLevelConfigs = ARR_SIZE(Clock_Q6PerfConfig),
  .nCPUBootPerfLevel       = CLOCK_QDSP6SSCORE_CONFIG_672P0MHz,
  .eCPU                    = CLOCK_CPU_LPASS_Q6,
  .eRail                   = VCS_RAIL_CX,
  .szRailName              = VCS_NPA_RESOURCE_VDD_CX
};


const HAL_clk_HWIOBaseType ClockLPASSHWIOBases = 
{
   /* nPhysAddress */ 0x17000000,
   /* nSize        */ 0x00400000
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
   { HAL_CLK_SOURCE_LPAPLL0, 564480 * 1000 },
   { HAL_CLK_SOURCE_LPAPLL2, 614400 * 1000 },
   { HAL_CLK_SOURCE_NULL,    NULL}
};



