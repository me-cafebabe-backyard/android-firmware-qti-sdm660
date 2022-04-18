#ifndef __CLOCKCPUBSP_H__
#define __CLOCKCPUBSP_H__

/*=========================================================================

                    C L O C K   D E V I C E   D R I V E R
               
              C P U   B O A R D   S U P P O R T   P A C K A G E

GENERAL DESCRIPTION
  This file contains the BSP interface definitions for the
  MSM DAL Clock Device Driver CPU data structures.

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None.

      Copyright (c) 2014 by QUALCOMM Technologies, Inc.  All Rights Reserved.

==========================================================================*/

/*==========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.
 
$Header: //components/rel/core.qdsp6/1.0.c2/systemdrivers/clock/hw/msm8998/adsp/inc/ClockSSCCPU.h#1 $

when       who     what, where, why 
--------   ---     --------------------------------------------------------- 
11/07/12   dcf     Initial release.

==========================================================================*/ 

/*=========================================================================
      Includes
==========================================================================*/

#include "npa_remote_resource.h"
#include "ClockBSP.h"


/*=========================================================================
      Constants, Macros & Typedefs
==========================================================================*/


/*
 * Define aliases for the NPA resource nodes here as they may be 
 * used in multiple places within the clock code. 
*/
#define CLOCK_NPA_NODE_NAME_CPU                   "/clk/cpu"
#define CLOCK_NPA_NODE_NAME_CPU_TEST              "/clk/cpu.test"
#define CLOCK_NPA_RESOURCE_QDSS                   "/clk/qdss"
#define CLOCK_NPA_RESOURCE_PNOC                   "/clk/pnoc"
#define CLOCK_NPA_RESOURCE_SNOC                   "/clk/snoc"
#define CLOCK_NPA_RESOURCE_CNOC                   "/clk/cnoc"
#define CLOCK_NPA_RESOURCE_BIMC                   "/clk/bimc"
#define CLOCK_NPA_RESOURCE_OCMEM                  "/clk/ocmem"
#define CLOCK_NPA_RESOURCE_AGGR0                  "/clk/agr0"
#define CLOCK_NPA_RESOURCE_AGGR1                  "/clk/agr1"
#define CLOCK_NPA_RESOURCE_AGGR2                  "/clk/agr2"


/*
 * SSC Voltage level to corner map type.
 */
typedef struct
{
  VCSCornerType  eVRegLevel;
  uint32         nVoltageUS;
}Clock_VRegWarmUpType;


/*
 * ClockCPUConfigType
 *
 * Configuration parameters for a CPU performance level.
 * 
 * CoreConfig   - QDSP6 core configuration
 * Mux          - General mux configuration
 * nStrapACCVal - 4 byte value for STRAP_ACC register at this level.
 */
typedef struct
{
  HAL_clk_ClockConfigType CoreConfig;
  ClockMuxConfigType      Mux;
  uint32                  nStrapACCVal;
} ClockCPUConfigType;


/*
 * ClockCPUPerfConfigType
 *
 * Actual format for the data stored in the BSP.
 *
 *  HWVersion      - Version of the chip HW this configuration is for.
 *  nMinPerfLevel  - Minimum performance level
 *  nMaxPerfLevel  - Maximum performance level
 *  anPerfLevel    - Array of performance level indices
 *  nNumPerfLevels - Number of PerfLevels in anPerfLevel
 */
typedef struct
{
  ClockHWVersionType  HWVersion;
  uint32              nMinPerfLevel;
  uint32              nMaxPerfLevel;
  uint32             *anPerfLevel;
  uint32              nNumPerfLevels;
} ClockCPUPerfConfigType;


/*
 * LPASS PLL to actual PLL mapping 
 *  
 * nSource     - The supported PLL for this chipset. 
 * bInitialize - Specifies if the driver should initialize this during clock initialization. 
 */
typedef struct
{
  HAL_clk_SourceType nSource;
  boolean            bInitialize;
} ClockImagePLLConfigType;


/*
 * ClockImageBSPConfigType
 *
 * Image BSP data configuration.
 *
 *  bEnableDCS              - Enable boolean for dynamic clock scaling.
 *  pCPUConfig              - Array of CPU configurations.
 *  pCPUPerfConfig          - Array of CPU perf configurations.
 *  nNumCPUPerfLevelConfigs - Number of CPU perf levels
 *  nCPUBootPerfLevel       - Performance level set by boot.
 *  eCPU                    - Identifier of CPU.
 *  eRail                   - Identifier of rail powering the CPU.
 *  szRailName              - String name of NPA resource for CPU power rail.
 */
typedef struct
{
  boolean                 bEnableDCS;
  ClockCPUConfigType     *pCPUConfig;
  ClockCPUPerfConfigType *pCPUPerfConfig;
  uint32                  nNumCPUPerfLevelConfigs;
  uint32                  nCPUBootPerfLevel;
  ClockCPUType            eCPU;
  VCSRailType             eRail;
  const char             *szRailName;
} ClockImageBSPConfigType;

/*
 * ClockSourceInitType
 *  
 * eSource       - Source that needs to be initialized
 * nFreqHz       - Frequency to initialize to if applicable, otherwise 0 for default. 
 *  
 */
typedef struct
{
  HAL_clk_SourceType eSource;
  uint32             nFreqHz;
}ClockSourceInitType;


/*
 * NPA Remote Node support flags type to determine 
 * chipset specific initialization of NPA Remote Nodes. 
 *  
 * bOCMEM - Specifies if OCMEM is supported 
 *  
*/
typedef struct
{
  boolean bOCMEM;

}ClockNPARemoteNodeSupportType;


/*
 * ClockNPAResourcePubType
 *
 * BSP data for publishing NPA nodes to user domains
 *
 * nDomain           - The domain that requires the resource published.
 * ppszResourceList  - An array of string client resources to publish.
 * nTotalResources   - The number of resources to publish.
 */
typedef struct
{
   uint32 nDomain;
   const char** ppszResourceList;
   uint32 nTotalResources;
}ClockNPAResourcePubType;


#endif  /* __CLOCKCPUBSP_H__ */ 

